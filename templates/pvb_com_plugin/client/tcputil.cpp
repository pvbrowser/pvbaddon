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
  printf("PLUGIN: pvb_com_con(%s,%d)\n", adr, port);
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
  if(debug) printf("pvb_com_rec\n");
  int ret,i;
  if(s_ind == -1)  { msg[0] = '\n'; msg[1] = '\0'; return -1; }
  if(use_pvb_com_plugin == NULL) return -1;

  i = 0;
  while(i < len-1)
  {
#ifdef PVWIN32
tryagain:
#endif
    ret = recv(s,&msg[i],1,0);
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
      if(s != -1) closesocket(s);
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
  if(debug) printf("pvb_com_rec_binary\n");
  int ret,i;
  if(s_ind == -1) return -1;
  if(use_pvb_com_plugin == NULL) return -1;

  i = 0;
  while(i < len)
  {
#ifdef PVWIN32
tryagain:
#endif
    ret = recv(s,&msg[i],len-i,0);
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
      if(s != -1) closesocket(s);
      return -1;
    }
    i += ret;
  }
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
  if(debug) printf("pvb_com_send\n");

  ret = 0;
  if(s_ind == -1) return -1;
  if(use_pvb_com_plugin == NULL) return -1;

  bytes_left = len;
  first_byte = 0;

  while(bytes_left > 0)
  {
    ret = send(s,&msg[first_byte],bytes_left,MSG_NOSIGNAL);
    if(ret <= 0) 
    { 
      closesocket(s); 
      return -1; 
    }
    bytes_left -= ret;
    first_byte += ret;
  }
  return ret;
}

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
  if(debug) printf("pvb_com_close\n");
  if(s == -1) return -1;
  if(stemp == -1) return -1;
  if(use_pvb_com_plugin == NULL) return -1;
  return 0;
}

