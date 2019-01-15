/***************************************************************************
                          util.cpp  -  description
                             -------------------
    begin                : Mon May 14 2012
    copyright            : (C) 2012 pvbrowser
    email                : lehrig@t-online.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as        *
 *   published by the Free Software Foundation                             *
 *                                                                         *
 ***************************************************************************/
#include "processviewserver.h"
#include <nettle/base64.h>
#include <nettle/sha.h>
//#include <fcntl.h>
int debug = 0;

#ifdef PVWIN32
#include <windows.h>
#define MSG_NOSIGNAL 0

int pvMain(PARAM *p)
{
  if(p == NULL) return -1;
  return 0;
}

#else
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

int is_first_call = 1;
const char *ctxptr[MAX_CLIENTS];
/*
opcode :=
0 denotes a continuation frame
1 denotes a text frame
2 denotes a binary frame
3-7 are reserved for further non-control frames
8 denotes a connection close
9 denotes a ping
A denotes a pong
B-F are reserved for further control frames
*/
int ws_pvtcpsend_binary(PARAM *p, const char *buf, int len, int opcode);
int ws_pvtcpreceive(PARAM *p, char *buf, int maxlen, int *fin, int *opcode);
int ws_pvtcpreceive_binary(PARAM *p, char *buf, int maxlen, int *fin, int *opcode);
int my_pvtcpsend_binary(PARAM *p, const char *buf, int len);
int my_pvtcpreceive(PARAM *p, char *buf, int maxlen);
int my_pvtcpreceive_binary(PARAM *p, char *buf, int maxlen);

/*
 * Makes file descriptor *fd* non-blocking mode.
 * This function returns 0, or returns -1.
int make_non_block(int fd)
{
  int flags, r;
  while((flags = fcntl(fd, F_GETFL, 0)) == -1 && errno == EINTR);
  if(flags == -1) {
    perror("fcntl");
    return -1;
  }
  while((r = fcntl(fd, F_SETFL, flags | O_NONBLOCK)) == -1 && errno == EINTR);
  if(r == -1) {
    perror("fcntl");
    return -1;
  }
  return 0;
}
 */

/*
 * Calculates SHA-1 hash of *src*. The size of *src* is *src_length* bytes.
 * *dst* must be at least SHA1_DIGEST_SIZE.
 */
void sha1(uint8_t *dst, const uint8_t *src, size_t src_length)
{
  struct sha1_ctx ctx;
  sha1_init(&ctx);
  sha1_update(&ctx, src_length, src);
  sha1_digest(&ctx, SHA1_DIGEST_SIZE, dst);
}

/*
 * Base64-encode *src* and stores it in *dst*.
 * The size of *src* is *src_length*.
 * *dst* must be at least BASE64_ENCODE_RAW_LENGTH(src_length).
 */
void base64(uint8_t *dst, const uint8_t *src, size_t src_length)
{
  struct base64_encode_ctx ctx;
  base64_encode_init(&ctx);
  base64_encode_raw((char *) dst, src_length, src);
  //base64_encode_raw(dst, src_length, src);
}

#define WS_GUID "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

/*
 * Create Server's accept key in *dst*.
 * *client_key* is the value of |Sec-WebSocket-Key| header field in
 * client's handshake and it must be length of 24.
 * *dst* must be at least BASE64_ENCODE_RAW_LENGTH(20)+1.
 */
void create_accept_key(char *dst, const char *client_key)
{
  uint8_t sha1buf[20], key_src[60];
  memcpy(key_src, client_key, 24);
  memcpy(key_src+24, WS_GUID, 36);
  sha1(sha1buf, key_src, sizeof(key_src));
  base64((uint8_t*)dst, sha1buf, 20);
  dst[BASE64_ENCODE_RAW_LENGTH(20)] = '\0';
}

int my_http_handshake(PARAM *p)
{
  char buf[1024];
  char accept_key[29], res_header[256];
  int res_header_length;
  if(debug) printf("my_http_handshake\n");
  accept_key[0] = '\0';
  while(1)
  {
    my_pvtcpreceive(p, buf, sizeof(buf)-1);
    if(debug) printf("my_http_header got=%s", buf);
    if(strlen(buf) < 3) break;
    char *cptr = strstr(buf,"Sec-WebSocket-Key:");
    if(cptr != NULL)
    {
      while(*cptr != ' ') cptr++;
      while(*cptr == ' ') cptr++;
      if(debug) printf("create_accept_key for %s\n", cptr);
      create_accept_key(accept_key, cptr);
    }
  }
  if(accept_key[0] == '\0')
  {
    printf("ERROR No accept_key\n");
    return -1;
  }
  snprintf(res_header, sizeof(res_header),
           "HTTP/1.1 101 Switching Protocols\r\n"
           "Upgrade: websocket\r\n"
           "Connection: Upgrade\r\n"
           "Sec-WebSocket-Accept: %s\r\n"
           "\r\n", accept_key);
  res_header_length = strlen(res_header);
  if(debug) printf("write res_header=%s\n", res_header);
  my_pvtcpsend_binary(p, res_header, res_header_length);
  static char Context[] = "Context";
  ctxptr[p->iclientsocket] = Context;    
  return 0;
}

extern "C" int plug_pvAccept(PARAM *p)
{
  if(is_first_call)
  {
    is_first_call = 0;
    for(int i=0; i<MAX_CLIENTS; i++) ctxptr[i] = NULL;
  }
  if(p == NULL) return 0;
  if(debug) printf("In plugin pvAccept() p->s=%d\n", p->s);
  return -1;
}

extern "C" int plug_closesocket(int s, PARAM *p)
{
  if(p != NULL && ctxptr[p->iclientsocket] != NULL) 
  {
    if(debug) printf("INFO plug_closesocket s=%d p->iclientsocket=%d\n", s, p->iclientsocket);
    ctxptr[p->iclientsocket] = NULL;
  }
#ifdef PVWIN32
  closesocket(s);
#else
  close(s);
#endif
  return 0;
}

int ws_send_helper(PARAM *p, const char *buf, int len)
{
  int ret,bytes_left,first_byte;

  if(p->s == -1 && p->os != -2) pvThreadFatal(p,"exit");;
  bytes_left = len;
  first_byte = 0;
  while(bytes_left > 0)
  {
#if defined(USE_INETD) && !defined(__VMS)
    ret = write(pv_STDOUT,&buf[first_byte],bytes_left);
    if(ret <= 0 && p->os != -2) pvMainFatal(p,"exit");
    if(ret <= 0)                p->os = -2;
#else
    ret = send(p->s,&buf[first_byte],bytes_left,MSG_NOSIGNAL);
    if(ret <= 0 && p->os != -2) pvThreadFatal(p,"exit");
    if(ret <= 0)                p->os = -2;
#endif
    bytes_left -= ret;
    first_byte += ret;
  }
  return 0;
}

/* send a packet to tcp or a file */
int ws_pvtcpsend_binary(PARAM *p, const char *buf, int len, int opcode)
{
  opcode = 1;
  if(p->is_binary)
  {
    opcode = 2;
  }
  if(debug) printf("in ws_pvtcpsend_binary p->is_binary=%d opcode=%d len=%d buf=%s\n", p->is_binary, opcode, len, buf);

  int imask = 0;
  unsigned char hbuf[32];
  hbuf[0] = 128 | opcode;
  if(len < 126)
  {
    hbuf[1] = imask | len;
    if(debug) printf("send1 hbuf=%x %x\n", hbuf[0], hbuf[1]);
    ws_send_helper(p, (const char *) hbuf, 2);
  }
  else if(len <= 256*256)
  {
    hbuf[1] = imask | 126;
    hbuf[2] = len / 256;
    hbuf[3] = len & 0x0ff;
    if(debug) printf("send2 hbuf=%x %x %x %x\n", hbuf[0], hbuf[1], hbuf[2], hbuf[3]);
    ws_send_helper(p, (const char *) hbuf, 4);
  }
  else
  {
    int xlen = len;
    hbuf[1] = imask | 127;
    hbuf[9] = xlen & 0x0ff; xlen /= 256;
    hbuf[8] = xlen & 0x0ff; xlen /= 256;
    hbuf[7] = xlen & 0x0ff; xlen /= 256;
    hbuf[6] = xlen & 0x0ff; xlen /= 256;
    hbuf[5] = xlen & 0x0ff; xlen /= 256;
    hbuf[4] = xlen & 0x0ff; xlen /= 256;
    hbuf[3] = xlen & 0x0ff; xlen /= 256;
    hbuf[2] = xlen & 0x0ff; xlen /= 256;
    if(debug) printf("send3a hbuf=%x %x %x %x\n", hbuf[0], hbuf[1], hbuf[2], hbuf[3]);
    if(debug) printf("send3b hbuf=%x %x %x %x\n", hbuf[4], hbuf[5], hbuf[6], hbuf[7]);
    if(debug) printf("send3c hbuf=%x %x\n", hbuf[8], hbuf[9]);
    ws_send_helper(p, (const char *) hbuf, 10);
  }
  
  if(debug) printf("send payload len=%d buf=%s\n", len, buf);
  ws_send_helper(p, (const char *) buf, len);
  return len;
}

/* receive a packet from tcp */
int ws_receive_helper(PARAM *p, char *buf, int len)
{
  int i,ret;

  i = 0;
  while(i < len)
  {
#if defined(USE_INETD) && !defined(__VMS)
    ret = read(pv_STDIN,&buf[i],1);
    if(ret <= 0) pvMainFatal(p,"exit");
#else
    ret = recv(p->s,&buf[i],1,0);
    if(ret <= 0) pvThreadFatal(p,"exit");
#endif
    //if(buf[i] == '\n') break;
    i += ret;
  }
  return i;
}

int ws_pvtcpreceive(PARAM *p, char *buf, int maxlen, int *fin, int *opcode)
{
  int i;
  unsigned char hbuf[32], maskbuf[4];
  *fin = 0;
  *opcode = 0;
  int mask = 0;
  int payload_len = 0;

  if(debug) printf("in ws_pvtcpreceive maxlen=%d\n", maxlen);
  ws_receive_helper(p, (char *) hbuf, 2);
  if(debug) printf("hbuf=%x %x (hex) / %d %d (dec)\n",hbuf[0],hbuf[1],hbuf[0],hbuf[1]);
  if(hbuf[0] & 128) *fin = 1;
  *opcode = hbuf[0] & 0x0f;
  if(hbuf[1] & 128) mask = 1;
  payload_len = hbuf[1] & 0x07f;
  if(debug) printf("fin=%d opcode=%d mask=%d payload_len=%d\n", *fin, *opcode, mask, payload_len);
  
  if(payload_len == 126)
  {
    ws_receive_helper(p, (char *) buf, 2);
    payload_len = hbuf[0]*256 + hbuf[1];
  }
  else if(payload_len == 127)
  {
    ws_receive_helper(p, (char *) buf, 8);
    payload_len = ((((((hbuf[0]&0x7f)*256 + hbuf[1])*256 + hbuf[3])*256 + hbuf[4])*256 + hbuf[5]) + hbuf[6]) + hbuf[7];
  }
  if(debug) printf("final_payload_len=%d\n", payload_len);

  if(mask == 1)
  {
    ws_receive_helper(p, (char *) maskbuf, 4);
    if(debug) printf("maskbuf=%x %x %x %x\n", maskbuf[0], maskbuf[1], maskbuf[2], maskbuf[3]);
  }

  if(payload_len > maxlen)
  {
    printf("ERROR ws_pvtcpreceive payload_len=%d maxlen=%d\n", payload_len, maxlen);
    return -1;
  }

  int ret = ws_receive_helper(p, (char *) buf, payload_len);
  if(debug) printf("ws_receive_helper ret=%d\n", ret);
  for(i=0; i<payload_len; i++)
  {
    buf[i] = buf[i] ^ maskbuf[i%4];
  }

  if(*opcode == 8)
  {
    pvThreadFatal(p,"exit websocket denotes a connection close");
  }

  if(debug) printf("end ws_pvtcpreceive buf=%s\n",buf);
  return payload_len;
}

/* receive a packet from tcp */
int ws_pvtcpreceive_binary(PARAM *p, char *buf, int maxlen, int *fin, int *opcode)
{
  return ws_pvtcpreceive(p,buf,maxlen,fin,opcode);
}

/* send a packet to tcp or a file */
int my_pvtcpsend_binary(PARAM *p, const char *buf, int len)
{
  int ret,bytes_left,first_byte;

  if(debug) printf("in my_pvtcpsend_binary len=%d buf=%s\n", len, buf);
  if(p->s == -1 && p->os != -2) pvThreadFatal(p,"exit");;
  bytes_left = len;
  first_byte = 0;
  while(bytes_left > 0)
  {
#if defined(USE_INETD) && !defined(__VMS)
    ret = write(pv_STDOUT,&buf[first_byte],bytes_left);
    if(ret <= 0 && p->os != -2) pvMainFatal(p,"exit");
    if(ret <= 0)                p->os = -2;
#else
    ret = send(p->s,&buf[first_byte],bytes_left,MSG_NOSIGNAL);
    if(ret <= 0 && p->os != -2) pvThreadFatal(p,"exit");
    if(ret <= 0)                p->os = -2;
#endif
    bytes_left -= ret;
    first_byte += ret;
  }
  return 0;
}

/* receive a packet from tcp */
int my_pvtcpreceive(PARAM *p, char *buf, int maxlen)
{
  int i,ret;

  if(debug) printf("in my_pvtcpreceive maxlen=%d\n", maxlen);
  i = 0;
  while(i < maxlen-1)
  {
#if defined(USE_INETD) && !defined(__VMS)
    ret = read(pv_STDIN,&buf[i],1);
    if(ret <= 0) pvMainFatal(p,"exit");
#else
    ret = recv(p->s,&buf[i],1,0);
    if(ret <= 0) pvThreadFatal(p,"exit");
#endif
    if(buf[i] == '\n') break;
    i += ret;
  }
  i++;
  buf[i] = '\0';
  if(debug) printf("end my_pvtcpreceive=%s",buf);
  return i;
}

/* receive a packet from tcp */
int my_pvtcpreceive_binary(PARAM *p, char *buf, int maxlen)
{
  int i,ret;

  if(debug) printf("in my_pvtcpreceive_binary maxlen=%d\n", maxlen);
  i = 0;
  while(i < maxlen)
  {
#if defined(USE_INETD) && !defined(__VMS)
    ret = read(pv_STDIN,&buf[i],1);
    if(ret <= 0) pvMainFatal(p,"exit");
#else
    ret = recv(p->s,&buf[i],1,0);
    if(ret <= 0) pvThreadFatal(p,"exit");
#endif
    i += ret;
  }
  return i;
}

/* send a packet to tcp or a file */
extern "C" int plug_pvtcpsend_binary(PARAM *p, const char *buf, int len)
{
  //sleep(1);
  int opcode = 1; // 1 TEXT // 2 BINARY
  if(p->is_binary) 
  {
    opcode = 1; // 2;
    //return len;
  }
  //if(buf[len-1] == '\n') opcode = 1; // TEXT
  if(debug) printf("in plug_pvtcpsend_binary len=%d buf=%s p->s=%d p->iclientsocket=%d\n", len, buf, p->s, p->iclientsocket);
  if     (ctxptr[p->iclientsocket] == NULL) return my_pvtcpsend_binary(p,buf,len);
  return ws_pvtcpsend_binary(p,buf,len,opcode);
}

/* receive a packet from tcp */
extern "C" int plug_pvtcpreceive(PARAM *p, char *buf, int maxlen)
{
  int fin, opcode;
  if(debug) printf("in plug_pvtcpreceive maxlen=%d p->iclientsocket=%d\n", maxlen, p->iclientsocket);
  if     (ctxptr[p->iclientsocket] == NULL)
  {
    int len = my_pvtcpreceive(p,buf,maxlen);
    if(p->s > 0 && p->s < MAX_CLIENTS && strncmp(buf,"GET / ",6) == 0)
    {
      if(debug) printf("call2 my_http_handshake\n");
      my_http_handshake(p);
      strcpy(buf,"ws://");
      len = strlen(buf);
      strcpy(p->url,buf);
    }
    return len;
  }
  else
  {
    int len = ws_pvtcpreceive(p,buf,maxlen,&fin,&opcode);
    return len;
  }
}

/* receive a packet from tcp */
extern "C" int plug_pvtcpreceive_binary(PARAM *p, char *buf, int maxlen)
{
  int fin, opcode;
  if(debug) printf("in plug_pvtcpreceive_binary maxlen=%d p->iclientsocket=%d\n", maxlen, p->iclientsocket);
  if     (ctxptr[p->iclientsocket] == NULL) return my_pvtcpreceive_binary(p,buf,maxlen);
  return ws_pvtcpreceive_binary(p,buf,maxlen,&fin,&opcode);
}

