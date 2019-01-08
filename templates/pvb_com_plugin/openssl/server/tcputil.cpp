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
static const int trace = 1;
static const int rl_ipversion = 4;

#define AF_INET6_IS_AVAILABLE

//#define CertFile "mycert.pem"
//#define KeyFile  "mycert.pem"
// ca.pem  client.key  client.pem  client.req  file.srl  privkey.pem  server.key  server.pem  server.req
const char *client_CertFile = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/client.pem";
const char *client_KeyFile  = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/client.key";
const char *server_CertFile = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/server.pem";
const char *server_KeyFile  = "/home/lehrig/cc/priv/pvbaddon/rlproxy/murx/client_cert/server.key";

#include "openssl/ssl.h"
#include "openssl/err.h"

#ifdef RLWIN32
//#if (_WIN32_WINNT < 0x0501)
//#warning mingw does not have helpers modify mingw header in ws2tcpip.h
#include <winsock2.h>
#include <ws2tcpip.h>

#define WTREAD_GNUC5 ( __GNUC__ * 1000 ) + __GNUC_MINOR__
#if WTREAD_GNUC5 < 4008
void WSAAPI freeaddrinfo(struct addrinfo*);
int  WSAAPI getaddrinfo(const char*,const char*,const struct addrinfo*, struct addrinfo**);
int  WSAAPI getnameinfo(const struct sockaddr*,socklen_t,char*,DWORD, char*,DWORD,int);
#endif

//#undef AF_INET6_IS_AVAILABLE
//#endif
#include <windows.h>
#include <io.h>
#include <direct.h>
#define  MSG_NOSIGNAL 0
#else
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "unistd.h"
#endif

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

typedef struct
{
  SSL_CTX *ctx;
  SSL     *ssl;
}AConnection;

//--- Helper functions begin -----------------------------------------------------
void ShowCerts(SSL* ssl)
{
  X509 *cert;
  char *line;

  cert = SSL_get_peer_certificate(ssl); // get the client's (not server's) certificate
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
  }
  else
  {
    printf("No certificates.\n");
  }
}

int serverLoadCertificates(SSL_CTX *ctx, const char *CertFile, const char *KeyFile)
{
  if(trace) printf("serverLoadCertificates begin ctx=%ld CertFile=%s KeyFile=%s\n", (long) ctx, CertFile, KeyFile);
  //if(SSL_CTX_load_verify_locations(ctx, CertFile, KeyFile) != 1)
  /*
  if(trace) printf("step1\n");
  if(SSL_CTX_load_verify_locations(ctx, CertFile, NULL) != 1)
  {
    ERR_print_errors_fp(stderr);
    printf("serverLoadCertificates: ERROR_print load_verify_locations cert=%s key=%s\n", CertFile, KeyFile);
  }
  if(trace) printf("step2\n");
  if(SSL_CTX_set_default_verify_paths(ctx) != 1)
  {
    ERR_print_errors_fp(stderr);
    printf("serverLoadCertificates: ERROR_print set_default_verify_paths\n");
  }
  */

  if(trace) printf("step3\n");
  // set the local certificate from CertFile
  //if(SSL_CTX_use_certificate_chain_file(ctx, CertFile) <= 0)
  if(SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0)
  {
    ERR_print_errors_fp(stderr);
    printf("serverLoadCertificates: ERROR use_certificate_file %s\n", CertFile);
    return -1;
  }
  if(trace) printf("step4\n");
  // set the private key from KeyFile (may be the same as CertFile)
  if(SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)
  {
    printf("serverLoadCertificates: ERROR use_private_key_file %s\n", KeyFile);
    return -2;
  }
  if(trace) printf("step5\n");
  // verify private key
  if (!SSL_CTX_check_private_key(ctx))
  {
    printf("Private key does not match the public certificate\n");
    return -3;
  }

  if(trace) printf("step6\n");
  // murx begin
  //SSL_CTX_set_client_CA_list(ctx, SSL_load_client_CA_file("murx/client_cert/ca.pem"));
  // murx end

  //New lines - Force the client-side have a certificate
  //SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
  //SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_CLIENT_ONCE , NULL);
  //ERR_print_errors_fp(stderr);
  //SSL_CTX_set_verify_depth(ctx, 4);
  //ERR_print_errors_fp(stderr);
  //End new lines

  if(trace) printf("serverLoadCertificates end\n");
  return 0;
}

SSL_CTX *InitCTX(void)
{
  //if(trace) printf("InitCTX SSLv23_server_method()\n");
  //SSL_CTX *ctx = SSL_CTX_new(SSLv23_server_method()); // Create new context
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


SSL_CTX *ctx = NULL;
int is_first_call = 1;
extern "C" int plug_pvAccept(PARAM *p)
{
  int option;
  int ret;
#ifdef __VMS
  size_t    socklen = sizeof(struct sockaddr);
#else
  socklen_t socklen = sizeof(struct sockaddr);
#endif
  struct sockaddr_in     localAddr;
#ifdef AF_INET6_IS_AVAILABLE
  struct addrinfo        hints0;
  struct addrinfo       *res, *ressave;
  int n;
  char portstr[32];
#endif
  
  printf("In plugin pvAccept() begin p->s=%d\n", p->s);
  if(is_first_call)
  {
    is_first_call = 0;
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();
  
    ctx = InitCTX();
    serverLoadCertificates(ctx, server_CertFile, server_KeyFile);

    if(rl_ipversion == 4)
    {    
      // create a socket
      p->os = socket(AF_INET,SOCK_STREAM,0);
      if(p->os == -1) return -1;
      // set socket options
      option = 1;
#ifdef RLWIN32
      setsockopt(p->os,SOL_SOCKET,SO_REUSEADDR,(const char *) &option,sizeof(option));
#else
      setsockopt(p->os,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
#endif
      // Bind our server to the agreed upon port number.
      memset(&localAddr,0,sizeof(localAddr));
      localAddr.sin_port = htons((short) p->port);
      localAddr.sin_family = AF_INET;
bind:
      ret = bind(p->os, (struct sockaddr *) &localAddr, sizeof(localAddr));
      if(ret == -1)
      {
        ::printf("warning: could not bind to port=%d\n", p->port);
        sleep(1);
        goto bind;
      }
      // Prepare to accept client connections.  Allow up to 5 pending
      // connections.
      ret = listen(p->os, 5);
      if(ret == -1) return -3;
    }
    else if(rl_ipversion == 6)
    { 
      char adr[132] = "localhost"; 
      memset(&hints0,0,sizeof(hints0));
      hints0.ai_flags = AI_PASSIVE;
      //hints0.ai_family = AF_UNSPEC;
      hints0.ai_family = AF_INET6;
      hints0.ai_socktype = SOCK_STREAM;
      sprintf(portstr,"%d",p->port);
      //::printf("server getaddrinfo(%s,%s)\n", adr, portstr);
      n = getaddrinfo(adr, portstr, &hints0, &res);
      if(n != 0)
      {
#ifndef RLWIN32
        ::printf("rlSocket:tcp_listen error for %s port=%s : %s\n", adr, portstr, gai_strerror(n));
#endif
        return -1;
      }
      //::printf("done\n");
      ressave = res;
bindv6:
      do
      {
        p->os = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if(p->os < 0)                                            continue; // error, try next one
        option = 1;
#ifdef RLWIN32
        setsockopt(p->os,SOL_SOCKET,SO_REUSEADDR,(const char *) &option,sizeof(option));
#else
        setsockopt(p->os,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
#endif
        if(bind(p->os, res->ai_addr, res->ai_addrlen) == 0)      break;    // success
        // bind error, close and try next one
#ifdef RLWIN32
        closesocket(p->os);
#else
        close(p->os);
#endif
      }
      while((res = res->ai_next) != NULL);
      if(res == NULL)                                                   // errno from final socket() or bind()
      {
        ::printf("warning: could not bind to port=%d\n", p->port);
        sleep(1);
        goto bindv6;
      }
      // Prepare to accept client connections.  Allow up to 5 pending
      // connections
      ret = listen(p->os, 5);
      freeaddrinfo(ressave);
      if(ret == -1) return -4;
    }
  }

  if(p->os < 0) return -5;
  unsigned char sockaddr[16+48];
  p->s = accept(p->os, (struct sockaddr *) &sockaddr[0], &socklen);
  if(p->s == -1) return -6;

  SSL *ssl = SSL_new(ctx);
  AConnection *connection = new AConnection;
  connection->ctx = ctx;
  connection->ssl = ssl;
  SSL_set_fd(ssl,p->s);
  if(SSL_accept(ssl) == -1)
  {
    ERR_print_errors_fp(stderr);
    SSL_free(ssl);
    delete connection;
#ifdef PVWIN32
    closesocket(p->s);
#else
    close(p->s);
#endif
    return -5;
  }
  ShowCerts(ssl);
  p->communication_plugin = (const char *) connection;
  p->use_communication_plugin = 1;
  printf("In plugin pvAccept() end p->s=%d\n", p->s);
  return p->s;
}

extern "C" int plug_closesocket(int s, PARAM *p)
{
  printf("plug_closesocket begin s=%d\n", s);
  if(p == NULL) return 0;
  AConnection *connection = (AConnection *) p->communication_plugin;
  if(connection->ssl != NULL) SSL_free(connection->ssl);
  connection->ssl = NULL;
  delete connection;
  p->communication_plugin = NULL;
  if(s > 0)
  {
#ifdef PVWIN32
    closesocket(s);
#else
    close(s);
#endif
    p->s = -1;
  }
  printf("plug_closesocket end\n");
  return 0;
}


/* send a packet to tcp or a file */
extern "C" int plug_pvtcpsend_binary(PARAM *p, const char *buf, int len)
{
  int ret,bytes_left,first_byte;

  //printf("plug_pvtcpsend_binary p->s=%d %20s\n", p->s, buf);
  AConnection *connection;
  connection = (AConnection *) p->communication_plugin;
  if(p->s == -1 && p->os != -2) pvThreadFatal(p,"exit");;
  bytes_left = len;
  first_byte = 0;
  while(bytes_left > 0)
  {
#if defined(USE_INETD) && !defined(__VMS)
    //ret = write(pv_STDOUT,&buf[first_byte],bytes_left);
    ret = SSL_write(connection->ssl,&buf[first_byte],bytes_left);
    if(ret <= 0 && p->os != -2) pvMainFatal(p,"exit");
    if(ret <= 0)                p->os = -2;
#else
    //ret = send(p->s,&buf[first_byte],bytes_left,MSG_NOSIGNAL);
    ret = SSL_write(connection->ssl,&buf[first_byte],bytes_left);
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
  const AConnection *connection;
  connection = (AConnection *) p->communication_plugin;

  //printf("plug_pvtcpreceive p->s=%d\n", p->s);
  i = 0;
  while(i < maxlen-1)
  {
#if defined(USE_INETD) && !defined(__VMS)
    //ret = read(pv_STDIN,&buf[i],1);
    ret = SSL_read(connection->ssl,&buf[i],1);
    if(ret <= 0) pvMainFatal(p,"exit");
#else
    //ret = recv(p->s,&buf[i],1,0);
    ret = SSL_read(connection->ssl,&buf[i],1);
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
  const AConnection *connection;
  connection = (AConnection *) p->communication_plugin;

  //printf("plug_pvtcpreceive_binary p->s=%d\n", p->s);
  i = 0;
  while(i < maxlen)
  {
#if defined(USE_INETD) && !defined(__VMS)
    //ret = read(pv_STDIN,&buf[i],1);
    ret = SSL_read(connection->ssl,&buf[i],1);
    if(ret <= 0) pvMainFatal(p,"exit");
#else
    //ret = recv(p->s,&buf[i],1,0);
    ret = SSL_read(connection->ssl,&buf[i],1);
    if(ret <= 0) pvThreadFatal(p,"exit");
#endif
    i += ret;
  }
  return i;
}

