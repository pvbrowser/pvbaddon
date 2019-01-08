/****************************************************************************
**
** Copyright (C) 2000-2012 Lehrig Software Engineering.
**
** This file is part of the pvbrowser project.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** This is a template for a pvbrowser communication plugin
** This example communicates the same way as the original communication is done
** But you may modify this
** For example you might use a tty instead of TCP
** You may compress the communication with libzip
** You may encrypt the communication with openSSL
**
****************************************************************************/
static const int debug = 0;
static const int trace = 0;

//#define CertFile "mycert.pem"
//#define KeyFile  "mycert.pem"
// ca.pem  client.key  client.pem  client.req  file.srl  privkey.pem  server.key  server.pem  server.req

const char *client_CertFile = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/client.pem";
const char *client_KeyFile  = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/client.key";
const char *server_CertFile = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/server.pem";
const char *server_KeyFile  = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/server.key";

#include "openssl/ssl.h"
#include "openssl/err.h"

#define MAX_TABS 32
typedef struct
{
  int     s;
  SSL     *ssl;
}AConnection;
AConnection connection[MAX_TABS+1];

#ifndef IS_OLD_MSVCPP
#define AF_INET6_IS_AVAILABLE
#endif

#define _QTSOCK_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __FreeBSD__
#define MSG_NOSIGNAL 0
#endif

#ifdef __VMS
#define MSG_NOSIGNAL 0
#endif

#ifndef PVWIN32
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#define closesocket close
#endif

#ifdef PVWIN32
#ifdef IS_OLD_MSVCPP
#include "winsock.h"
#else
#if (_WIN32_WINNT < 0x0501)
#warning mingw does not have ipv6 helpers modify mingw header in ws2tcpip.h
#endif
#include "winsock2.h"
#include <ws2tcpip.h>
void WSAAPI freeaddrinfo(struct addrinfo*);
int  WSAAPI getaddrinfo(const char*,const char*,const struct addrinfo*, struct addrinfo**);
int  WSAAPI getnameinfo(const struct sockaddr*,socklen_t,char*,DWORD, char*,DWORD,int);
//#undef AF_INET6_IS_AVAILABLE
//#endif
#endif
#define MSG_NOSIGNAL 0
//#include <qapplication.h>
#endif

#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

#ifdef AF_INET6_IS_AVAILABLE
static int rl_ipversion = 6; // default: use ip6. client will try ipv4 if server does not support ipv6
#else
static int rl_ipversion = 4; // only necessary because of MSVSCPP 6.0
#endif

//--- Helper functions begin -----------------------------------------------------
int ShowCerts(SSL* ssl)
{
  X509 *cert;
  char *line;

  cert = SSL_get_peer_certificate(ssl); // get the server's certificate
  if(cert != NULL)
  {
    printf("Server certificates:\n");
    line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
    printf("Subject: %s\n", line);
    free(line);       // free the malloc'ed string
    line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
    printf("Issuer: %s\n", line);
    free(line);       // free the malloc'ed string
    X509_free(cert);  // free the malloc'ed certificate copy
    return 1;
  }
  else
  {
    printf("No certificates.\n");
    return 0;
  }
}

int clientLoadCertificates(SSL_CTX *ctx, const char *CertFile, const char *KeyFile)
{
  if(trace) printf("clientLoadCertificates begin ctx=%ld CertFile=%s KeyFile=%s\n", (long) ctx, CertFile, KeyFile);
  // murx begin
  /*
  if(SSL_CTX_load_verify_locations(ctx, CertFile, KeyFile) != 1)
  {
    printf("clientLoadCertificates: ERROR_print load_verify_locations cert=%s key=%s\n", CertFile, KeyFile);
  }
  if(SSL_CTX_set_default_verify_paths(ctx) != 1)
  {
    printf("clientLoadCertificates: ERROR_print set_default_verify_paths\n");
  }
  */
  // murx end

  // set the local certificate from CertFile
  if(SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 )
  {
    printf("clientLoadCertificates: ERROR use_certificate_file %s\n", CertFile);
    return -1;
  }
  // set the private key from KeyFile (may be the same as CertFile)
  if( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 )
  {
    printf("clientLoadCertificates: ERROR use_private_key_file %s\n", KeyFile);
    return -2;
  }
  // verify private key
  if( !SSL_CTX_check_private_key(ctx) )
  {
    printf("Private key does not match the public certificate\n");
    return -3;
  }
  if(trace) printf("clientLoadCertificates end\n");

  //rlmurx SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);

  return 0;
}

SSL_CTX *InitCTX(void)
{
  //if(trace) printf("InitCTX SSLv23_client_method()\n");
  //SSL_CTX *ctx = SSL_CTX_new(SSLv23_client_method()); // Create new context
  if(trace) printf("InitCTX TLSv1_2_method()\n");
  SSL_CTX *ctx = SSL_CTX_new(TLSv1_2_method()); // Create new context
  if(ctx == NULL)
  {
    printf("InitCTX: ERROR\n");
    return NULL;
  }
  return ctx;
}

//--- Helper functions end -----------------------------------------------------

//#################################################################
// pvb communication switch on:
//
// if tcp_rec() in pvbrowser is active and receives a
// "@plugin("
// msg then pvb_com_plugin_on() is called
// we may further interpret msg in here
//
// our return value does not care
//
// ind := index in socket_array[] and use_pvb_com_plugin[]
//#################################################################
extern "C" int pvb_com_plugin_on(int ind, char *msg)
{
  if(ind < 0) return -1;
  if(msg == 0) return -1;
  return 0;
}

int is_first_call = 1;
SSL_CTX *ctx = NULL;
//#################################################################
// pvb communication close:
//
// if use_pvb_com_plugin[s_ind] then
// close the connection
// 
// if return == 1 then do not call closesocket(stemp) in pvbrowser
// else                       call closesocket(stemp) in pvbrowser
//
// s     := index in socket_array[] and use_pvb_com_plugin[]
// stemp := socket descriptor
//#################################################################
extern "C" int pvb_com_close(int s, int stemp, int *use_pvb_com_plugin)
{
  printf("pvb_com_close begin s=%d stemp=%d\n", s, stemp);
  if(s < 0) return 0;
  for(int ind=1; ind<=MAX_TABS; ind++)
  { // ssl was remembered for pvb_com_close 
    if(connection[ind].s == stemp)
    {
      if(debug) printf("pvb_com_close found s=%d to close\n", stemp);
      SSL_free(connection[ind].ssl);
      closesocket(connection[ind].s);
      connection[ind].s   = -1;
      connection[ind].ssl = NULL;
      break;
    }
  }
  if(use_pvb_com_plugin == NULL) return -1;
  printf("pvb_com_close end\n");
  return 0;
}

//#################################################################
// pvb communication connect:
//
// if pvb_com_con return < 0 then use standard tcp_con(adr,port) 
// if pvb_com_con return > 0 then connection is done in here
// For example we could open a serial port in here when
// adr = "@tty.baudrate"
//#################################################################
extern "C" int pvb_com_con(const char *adr, int port, int *use_plugin)
{
  printf("PLUGIN: 1 pvb_com_con(%s,%d)\n", adr, port);
  static int                s = -1;
  static struct sockaddr_in remoteAddr;
  static struct hostent     *host;
  static struct in_addr     RemoteIpAddress;
  int                       ret;
#ifdef AF_INET6_IS_AVAILABLE
  static struct addrinfo    hints, *res, *ressave;
  int                       n;
  char                      portstr[32];
#endif

  if(is_first_call)
  {
    is_first_call = 0;
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
    for(int i=0; i<=MAX_TABS; i++) 
    {
      connection[i].s   = -1;
      connection[i].ssl = NULL;
    }  
    ctx = InitCTX();
  }

  *use_plugin = 0;
  if(rl_ipversion == 4)
  {
    s = socket(AF_INET,SOCK_STREAM,0);
    if(s == -1) return -1;

    /* fill destblk structure */
    host = gethostbyname(adr);
    if(host == NULL)
    {
      /* See if the host is specified in "dot address" form */
      if(strchr(adr,'.') == NULL) return -1;
      RemoteIpAddress.s_addr = inet_addr(adr);
      if(RemoteIpAddress.s_addr == 0x0ffffffff) return -1;
    }
    else
    {
      memcpy(&RemoteIpAddress,host->h_addr,host->h_length);
    }

    memset(&remoteAddr,0,sizeof(remoteAddr));
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(port);
    remoteAddr.sin_addr = RemoteIpAddress;

    ret = connect(s, (struct sockaddr *) &remoteAddr, sizeof(remoteAddr));
    //if(ret == -1)
    if(ret < 0)
    {
      closesocket(s);
      return -1;
    }
  }
  else if(rl_ipversion == 6)
  {
#ifdef AF_INET6_IS_AVAILABLE
    sprintf(portstr,"%d",port);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    n = getaddrinfo(adr, portstr, &hints, &res);
    if(n != 0)
    {
#ifndef PVWIN32
      ::printf("tcp_con 1: error for %s port=%s : %s\n", adr, portstr, gai_strerror(n));
#endif
      return -1;
    }
    ressave = res;
    do
    {
      s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
      if(s < 0)                                            continue; // ignore this one
      if(::connect(s, res->ai_addr, res->ai_addrlen) == 0) break;    // success
      closesocket(s);
      s = -1;
    }
    while((res = res->ai_next) != NULL);
    if(res == NULL) ::printf("tcp_con 2: error for %s port=%s\n", adr, portstr);
    freeaddrinfo(ressave);
#else
    ::printf("tcp_con 3:ERROR IPV6 not available on this platform\n");
#endif
  }
  else
  {
    printf("tcp_con 4: ipversion=%d is not supported\n", rl_ipversion);
  }
  //return s;
  if(s < 0) return s;
  SSL     *ssl = SSL_new(ctx);
  SSL_set_fd(ssl,s);
  if(clientLoadCertificates(ctx, client_CertFile, client_KeyFile) < 0)
  {
    printf("Failed to load certificates\n");
    SSL_free(ssl);
    closesocket(s);
    return s;
  }  
  if(SSL_connect(ssl) == -1)
  {
    ERR_print_errors_fp(stderr);
    printf("communicate without ssl\n");
    SSL_free(ssl);
    *use_plugin = 0;
    return s;
  }
  ShowCerts(ssl); // show certificate

  printf("communicate with ssl\n");
  for(int ind=1; ind<=MAX_TABS; ind++)
  { // remember ssl for pvb_com_close 
    if(connection[ind].s == -1)
    {
      connection[ind].s   = s;
      connection[ind].ssl = ssl;
      break;
    }
  }
  *use_plugin = 1;
  printf("PLUGIN: 1 pvb_com_con return s=%d\n", s);
  return s;
}

//#################################################################
// pvb communication receive:
//
// if use_pvb_com_plugin[s_ind] then
// receive a '\n' terminated line of text with maximum len length
// return length of msg + 1
//
// s_ind := index in socket_array[] and use_pvb_com_plugin[]
// s     := socket descriptor
//
// if tcp_rec() in pvbrowser is active and receives a
// "@plugin("
// msg then pvb_com_plugin_on() is called
//#################################################################
extern "C" int pvb_com_rec(int s_ind, int s, char *msg, int len, int *use_pvb_com_plugin)
{
  if(debug) printf("pvb_com_rec s_ind=%d s=%d\n", s_ind, s);
  int ret,i;
  if(s_ind == -1)  { msg[0] = '\n'; msg[1] = '\0'; return -1; }
  if(use_pvb_com_plugin == NULL) return -1;

  i = 0;
  while(i < len-1)
  {
#ifdef PVWIN32
tryagain:
#endif
    //ret = recv(s,&msg[i],1,0);
    ret = SSL_read(connection[s_ind].ssl,&msg[i],1);
    if(ret <= 0)
    {
#ifdef PVWIN32
      if(WSAEWOULDBLOCK == WSAGetLastError())
      {
        if(i==0)
        {
          msg[0] = '\0';
          return -2;
        }  
        //qApp->processEvents();
        if(s != -1)
        {
          goto tryagain;
        }  
      }
#endif
      if(s != -1) pvb_com_close(s_ind, s, use_pvb_com_plugin); 
      msg[0] = '\n';
      msg[1] = '\0';
      return -1;
    }
    if(msg[i] == '\n')
    {
      i++;
      msg[i] = '\0';
      return i;
    }
    i++;
  }
  msg[i] = '\0';
  printf("msg=%s\n", msg);
  return i;
}

//#################################################################
// pvb communication receive binary:
//
// if use_pvb_com_plugin[s_ind] then
// receive msg with len length
// return length of msg
//
// s_ind := index in socket_array[] and use_pvb_com_plugin[]
// s     := socket descriptor
//#################################################################
extern "C" int pvb_com_rec_binary(int s_ind, int s, char *msg, int len, int *use_pvb_com_plugin)
{
  if(debug) printf("pvb_com_rec_binary s_ind=%d s=%d\n", s_ind, s);
  int ret,i;
  if(s_ind == -1) return -1;
  if(use_pvb_com_plugin == NULL) return -1;

  i = 0;
  while(i < len)
  {
#ifdef PVWIN32
tryagain:
#endif
    //ret = recv(s,&msg[i],len-i,0);
    ret = SSL_read(connection[s_ind].ssl,&msg[i],len-i);
    if(ret <= 0)
    {
#ifdef PVWIN32
      if(WSAEWOULDBLOCK == WSAGetLastError())
      {
        if(s != -1)
        {
          goto tryagain;
        }  
      }
#endif
      if(s != -1) pvb_com_close(s_ind, s, use_pvb_com_plugin); 
      return -1;
    }
    i += ret;
  }
  printf("msg=%20s\n", msg);
  return i;
}

//#################################################################
// pvb communication send:
//
// if use_pvb_com_plugin[s_ind] then
// send msg with len length
// return number of bytes send
//
// s_ind := index in socket_array[] and use_pvb_com_plugin[]
// s     := socket descriptor
//#################################################################
extern "C" int pvb_com_send(int s_ind, int s, const char *msg, int len, int *use_pvb_com_plugin)
{
  int ret,bytes_left,first_byte;
  if(debug) printf("pvb_com_send s_ind=%d s=%d connection[]=%d msg=%s\n", s_ind, s, connection[s-1].s, msg);

  ret = 0;
  if(s_ind == -1) return -1;
  if(use_pvb_com_plugin == NULL) return -1;

  bytes_left = len;
  first_byte = 0;

  while(bytes_left > 0)
  {
    //ret = send(s,&msg[first_byte],bytes_left,MSG_NOSIGNAL);
    ret = SSL_write(connection[s_ind].ssl,&msg[first_byte],bytes_left);
    if(ret <= 0) 
    { 
      pvb_com_close(s_ind, s, use_pvb_com_plugin); 
      return -1; 
    }
    bytes_left -= ret;
    first_byte += ret;
  }
  return ret;
}

