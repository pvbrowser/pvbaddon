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

extern "C" int plug_pvAccept(PARAM *p)
{
  printf("In plugin pvAccept() p->s=%d\n", p->s);
  if(p == NULL) return 0;
  return -1;
}

extern "C" int plug_closesocket(int s, PARAM *p)
{
#ifdef PVWIN32
  closesocket(s);
#else
  close(s);
#endif
  if(p == NULL) return 0;
  return 0;
}


/* send a packet to tcp or a file */
extern "C" int plug_pvtcpsend_binary(PARAM *p, const char *buf, int len)
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

/* receive a packet from tcp */
extern "C" int plug_pvtcpreceive(PARAM *p, char *buf, int maxlen)
{
  int i,ret;

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
  return i;
}

/* receive a packet from tcp */
extern "C" int plug_pvtcpreceive_binary(PARAM *p, char *buf, int maxlen)
{
  int i,ret;

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

