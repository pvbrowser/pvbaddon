//###############################################################
//# mask1_slots.h for ProcessViewServer created: So. Juni 8 09:08:14 2014
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
#include "rlwebcam.h"
#include "rlspreadsheet.h"
#include "rlcutil.h"
#include "rlfileload.h"

typedef struct // (todo: define your data structure here)
{
  int rowIndex, maxRowIndex, progress;
  rlSpreadsheetRow row;
  rlWebcam webcam;
}
DATA;

static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //memset(d,0,sizeof(DATA));
  d->progress = 0;
  d->rowIndex = d->maxRowIndex = -1;
  p->sleep = 1000 / 35; // frames per second
  p->force_null_event = 0;
  d->webcam.debug = 0;
  d->webcam.filename.printf("%swebcam.jpg", p->file_prefix);
  //d->webcam.setUrl("http://192.168.1.200/cgi-bin/Stream?Video Authorization: Basic YWRtaW46cGFzc3dvcmQ=?webcamPWD=RootCookie00000");
  //d->webcam.setUrl("http://192.168.1.32:80/snapshot.cgi?user=admin&pwd=");
  d->webcam.setUrl("http://192.168.1.32:80/videostream.cgi?user=admin&pwd=");
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;

  unsigned char buffer[256*1024];
  int size;
  if(d->rowIndex < 0) // online mode
  {
    if(1)
    {
      if((size = d->webcam.getFrameBuffer(buffer, (int) sizeof(buffer)),1000) > 0)
      {
        printf("Version with:: pvSetBufferedJpgImage:: size=%d\n", size);
        pvSetBufferedJpgImage(p,webcam,buffer,size);
      }
    }
    else
    {
      //if(const char *fname = d->webcam.getFrame()) // OR if(const char *fname = d->webcam.getSnapshot()) 
      if(const char *fname = d->webcam.getSnapshot()) // OR if(const char *fname = d->webcam.getSnapshot()) 
      {
        printf("Version with:: pvDownloadFileAs(webcam.jpg) and pvSetImage()\n");
        pvDownloadFileAs(p,fname,"webcam.jpg");
        pvSetImage(p,webcam,"webcam.jpg"); // webcam is a pvQImage object that accepts jpeg images
      }
    }
    switch(d->progress)
    {
      case 0:
        pvPrintf(p,lbCam1,"%s -","cam1");
        d->progress = 1;
        break;  
      case 1:
        pvPrintf(p,lbCam1,"%s \\","cam1");
        d->progress = 2;
        break;  
      case 2:
        pvPrintf(p,lbCam1,"%s |","cam1");
        d->progress = 3;
        break;  
      default:
        pvPrintf(p,lbCam1,"%s /","cam1");
        d->progress = 0;
        break;  
    }
  }
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonPressedEvent(PARAM *p, int id, DATA *d)
{
  const char *fname, *cptr;
  char cmd[80];
  if(p == NULL || id == 0 || d == NULL) return -1;
  switch(id)
  {
    case pbStart:
      if(d->rowIndex < 0)
      {
        pvBeep(p);
        break;
      }
      d->rowIndex = 1;
      fname = d->row.text(d->rowIndex);
      pvDownloadFileAs(p,fname,"webcam.jpg");
      pvSetImage(p,webcam,"webcam.jpg"); // webcam is a pvQImage object that accepts jpeg images       
      pvPrintf(p,lbCam1,"%s",d->row.text(d->rowIndex));
      pvPrintf(p,lbCam1,"%s (%d of %d snapshots)",d->row.text(d->rowIndex), d->rowIndex, d->maxRowIndex);
      break;
    case pbBack:
      if(d->rowIndex < 0)
      {
        pvBeep(p);
        break;
      }
      if(d->rowIndex == 1)
      {
        pvBeep(p);
        break;
      }
      d->rowIndex--;
      fname = d->row.text(d->rowIndex);
      pvDownloadFileAs(p,fname,"webcam.jpg");
      pvSetImage(p,webcam,"webcam.jpg"); // webcam is a pvQImage object that accepts jpeg images       
      pvPrintf(p,lbCam1,"%s",d->row.text(d->rowIndex));
      pvPrintf(p,lbCam1,"%s (%d of %d snapshots)",d->row.text(d->rowIndex), d->rowIndex, d->maxRowIndex);
      break;
    case pbPause:
      if(d->rowIndex < 0)
      {
        sprintf(cmd,"ls -al cam1_*.jpg > %s_cam1.dir", p->file_prefix);
        printf("cmd=%s\n",cmd);
        system(cmd);
        sprintf(cmd,"%s_cam1.dir", p->file_prefix);
        rlFileLoad fl;
        fl.load(cmd);
        unlink(cmd);

        d->rowIndex = 1;
        d->row.clear();

        cptr = fl.firstLine();
        while(1) // find cam1_*.jpg files
        {
          if(cptr == NULL) break;
          fname = strstr(cptr,"cam1_");
          if(fname == NULL) break;
          printf("fname=%s\n", fname);
          d->row.printf(d->rowIndex++,"%s",fname);
          cptr = fl.nextLine();
        }
        if(d->rowIndex == 1)
        {
          d->rowIndex = -1;
          d->maxRowIndex = -1;
          break;
        }
        d->maxRowIndex = d->rowIndex - 1;
        d->rowIndex = 1;  
        pvPrintfStyleSheet(p,pbPause,"background-color: grey;");
        pvPrintf(p,lbCam1,"%s (%d of %d snapshots)",d->row.text(d->rowIndex), d->rowIndex, d->maxRowIndex);
      }
      else
      {
        d->rowIndex = -1;
        d->row.clear();
        pvPrintfStyleSheet(p,pbPause,"background-color: #eeeeee;");
        pvPrintf(p,lbCam1,"%s","cam1");
      }
      break;
    case pbForward:
      if(d->rowIndex < 0)
      {
        pvBeep(p);
        break;
      }
      if(d->rowIndex >= d->maxRowIndex)
      {
        pvBeep(p);
        break;
      }
      fname = d->row.text(d->rowIndex + 1);
      printf("fname=%s\n", fname);
      if(strlen(fname) == 0) break;
      d->rowIndex += 1;
      pvPrintf(p,lbCam1,"%s",d->row.text(d->rowIndex));
      pvDownloadFileAs(p,fname,"webcam.jpg");
      pvSetImage(p,webcam,"webcam.jpg"); // webcam is a pvQImage object that accepts jpeg images       
      pvPrintf(p,lbCam1,"%s (%d of %d snapshots)",d->row.text(d->rowIndex), d->rowIndex, d->maxRowIndex);
      break;
    case pbEnd:
      if(d->rowIndex < 0)
      {
        pvBeep(p);
        break;
      }
      d->rowIndex = d->maxRowIndex;
      fname = d->row.text(d->rowIndex);
      printf("fname=%s\n", fname);
      if(strlen(fname) == 0) break;
      pvPrintf(p,lbCam1,"%s",d->row.text(d->rowIndex));
      pvDownloadFileAs(p,fname,"webcam.jpg");
      pvSetImage(p,webcam,"webcam.jpg"); // webcam is a pvQImage object that accepts jpeg images       
      pvPrintf(p,lbCam1,"%s (%d of %d snapshots)",d->row.text(d->rowIndex), d->rowIndex, d->maxRowIndex);
      break;
    default:
      break;
  }
  return 0;
}

static int slotButtonReleasedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotGlInitializeEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlPaintEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlResizeEvent(PARAM *p, int id, DATA *d, int width, int height)
{
  if(p == NULL || id == 0 || d == NULL || width < 0 || height < 0) return -1;
  return 0;
}

static int slotGlIdleEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTabEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotTableTextEvent(PARAM *p, int id, DATA *d, int x, int y, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || text == NULL) return -1;
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  return 0;
}

static int slotSelectionEvent(PARAM *p, int id, DATA *d, int val, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || text == NULL) return -1;
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotRightMouseEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  //pvPopupMenu(p,-1,"Menu1,Menu2,,Menu3");
  return 0;
}

static int slotKeyboardEvent(PARAM *p, int id, DATA *d, int val, int modifier)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || modifier < -1000) return -1;
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseOverEvent(PARAM *p, int id, DATA *d, int enter)
{
  if(p == NULL || id == 0 || d == NULL || enter < -1000) return -1;
  return 0;
}

static int slotUserEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}
