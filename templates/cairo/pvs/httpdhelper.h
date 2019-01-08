//###############################################################
//# loop.cpp for ProcessViewServer created: Mi. Okt. 25 12:37:48 2017
//# Yours: Lehrig Software Engineering
//###############################################################
#ifndef PVSERVER_HTTPD_HELPER_
#define PVSERVER_HTTPD_HELPER_
#include "processviewserver.h"
        
int helperFilecopy(const char *sfilename, const char *dfilename)
{
  char buf[1024];
  FILE *fin = fopen(sfilename,"rb");
  if(fin == NULL)
  {
    printf("could not open %s for reading\n", sfilename);
    return -1;
  }
  FILE *fout = fopen(dfilename,"wb");
  if(fout == NULL)
  {
    fclose(fin);
    printf("could not open %s for writeing\n", dfilename);
    return -1;
  }

  int len;
  while((len = fread(buf,1,sizeof(buf),fin)) > 0)
  {
    fwrite(buf,1,len,fout);
  }

  fclose(fout);
  fclose(fin);
  return 0;
}

static void helperParseUrl(char *url, rlString *filename, rlString *parameters = NULL)
{
  char *end;
  rlString fname, params;
  //printf("Begin: parseUrl(%s)\n",url);
  if(url == NULL) return;
  end = strchr(url, 0x0d);
  if(end != NULL) *end = '\0';
  end = strchr(url, 0x0a);
  if(end != NULL) *end = '\0';
  if(trace) printf("Begin: parseUrl(%s) filename=%s parameters=%s\n",url,filename->text(),parameters->text());
  if(strncmp(url,"GET ",4) != 0) return;
  if(filename == NULL) return;
  const char *cptr = &url[4];
  while(*cptr == ' ') cptr++;
  if(*cptr == '/') cptr++;

  fname.setText(cptr);
  if(parameters != NULL)
  {
    const char *par = strchr(fname.text(),'?');
    if(par != NULL)
    {
      par++;
      params.setText(par);
      char *end = strchr(params.text(),' ');
      if(end != NULL)
      {
        *end = '\0';
        *parameters = params;
      }
    }
  }
  end = strchr(fname.text(),'?');
  if(end != NULL)
  {
    *end = '\0';
  }
  end = strchr(fname.text(),' ');
  if(end != NULL)
  {
    *end = '\0';
  }
  *filename = fname;
  if(trace) printf("Return: parseUrl(%s) filename=%s parameters=%s\n",url,filename->text(),parameters->text());
}

static int helperSendAccepted(PARAM *p)
{
  char tbuf[80];
  sprintf(tbuf,"HTTP/1.1 202 Accepted\n");
  pvtcpsendstring(p,tbuf);
  sprintf(tbuf,"Server: pvserver-%s\n", pvserver_version);
  pvtcpsendstring(p,tbuf);
  sprintf(tbuf,"Keep-Alive: timeout=15, max=100\n");
  pvtcpsendstring(p,tbuf);
  sprintf(tbuf,"Connection: Keep-Alive\n");
  pvtcpsendstring(p,tbuf);
  sprintf(tbuf,"\n\n");
  pvtcpsendstring(p,tbuf);
  return 0;
}

static int helperPerhapsSendHttpResponseFile(PARAM *p, const char *cfilename, rlTime *t)
{
  // respond with requested file if(fileModificationTime has changed)
  rlTime ftime;
  rlString tempfile;
  tempfile.printf("PVTMP%d-%s",p->s,cfilename);
  
  tloop.lock();   // lock/unlock the file operation
  ftime.getFileModificationTime(cfilename);
  if(ftime == *t)
  {
    tloop.unlock();
    if(trace) printf("Accepted\n");
    helperSendAccepted(p);
  }
  else
  {
    helperFilecopy(cfilename,tempfile.text());
    if(trace) printf("http update %s\n",tempfile.text());
    tloop.unlock(); // the following transfer might be broken but we do not want to get locked.
                    // thus we made the above filecopy
    if     (strstr(cfilename,"svg") != NULL) pvSendHttpResponseFile(p, tempfile.text(), "Content-Type: image/svg+xml");
    else if(strstr(cfilename,"png") != NULL) pvSendHttpResponseFile(p, tempfile.text(), "Content-Type: image/png");
    else if(strstr(cfilename,"jpg") != NULL) pvSendHttpResponseFile(p, tempfile.text(), "Content-Type: image/jpeg");
    else if(strstr(cfilename,"css") != NULL) pvSendHttpResponseFile(p, tempfile.text(), "Content-Type: text/css");
    else                                     pvSendHttpResponseFile(p, tempfile.text());
    unlink(tempfile.text());
    *t = ftime;
  }
  return 0;
}

#endif
