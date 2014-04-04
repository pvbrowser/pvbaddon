#include "mywidget.h"
#include <stdio.h>

#ifdef _WIN32
#define WTREAD_GNUC_MY ( __GNUC__ * 1000 ) + __GNUC_MINOR__
#if WTREAD_GNUC_MY >= 4008
// we need a stupid workaround (lehrig 2013 when porting to qt5.1.0)
int CALLBACK WinMain(
  _In_  HINSTANCE hInstance,
  _In_  HINSTANCE hPrevInstance,
  _In_  LPSTR lpCmdLine,
  _In_  int nCmdShow
  )
{
  if(hInstance) return 0;
  if(hPrevInstance) return 0;
  if(lpCmdLine) return 0;
  if(nCmdShow) return 0;
  return 0;
}
#endif
#endif

//extern "C" int tcp_send(int *s, const char *msg, int len);

int dummy_tcp_send(int *s, const char *msg, int len){
    qDebug("dummy_tcp_send: sock=%d [%s] sz=%d\n",*s,msg,len);
    return 0;
}

//pointer to tcp_send function
int (*tcp_send)(int *s, const char *msg, int len) = dummy_tcp_send;

//temp buffer used with tcp_send
char tmp[80];

// send this event to the custom widget to call methods within custom widget
PvbEvent::PvbEvent(const char *_command, QString _param, QEvent::Type _event) 
         : QEvent(_event)
{
  command = _command;
  param = _param;
}

PvbEvent::~PvbEvent()
{
}

// Example custom widget
myButton::myButton(const char *name, int *_sock, int _ident, QWidget *parent)
         :QPushButton(parent)
{
  sock = _sock;
  ident = _ident;

  connect(this, SIGNAL(clicked()), SLOT(slotClicked()));
  if(name == NULL) return;
}

myButton::~myButton()
{

}

void myButton::slotClicked()
{
  printf("myButton was clicked TODO: send this event via TCP to the pvserver\n");
}

bool myButton::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
    PvbEvent *e = (PvbEvent *) event;
    printf("TODO: interpret (command,param) and call the method\n");
    printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
    if(strcmp(e->command,"setText") == 0)
    {
      setText(e->param);
    }
    return true;
  }
  else 
  {
    return QPushButton::event(event);
  }  
}



// TODO: add more custom widgets



myQtSvgDialGauge::myQtSvgDialGauge(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtSvgDialGauge(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);
    //set a default look
    setSkin("Tachometer");
    setNeedleOrigin(0.486, 0.466);
    setMinimum(0);//value min
    setMaximum(120);//value max
    setStartAngle(-130);
    setEndAngle(133);
}

myQtSvgDialGauge::~myQtSvgDialGauge()
{

}


bool myQtSvgDialGauge::event(QEvent *event)
{
    if(event->type() == pvbEventNumber)
    {

        int i, val;
        PvbEvent *e=(PvbEvent *)event;
        //printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
        if(strncmp(e->command,"setValue(",9) == 0)
        {
            sscanf(e->command, "setValue(%d,%d)", &i, &val);
            //printf("%s\n", e->command);
            setValue(val);
        }
        else if(strncmp(e->command, "setMinValue(", 12) == 0)
        {
          sscanf(e->command, "setMinValue(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setMinimum(val);
        }
        else if(strncmp(e->command, "setMaxValue(", 12) == 0)
        {
          sscanf(e->command, "setMaxValue(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setMaximum(val);
        }
        else
        {
            printf("TODO: interpret (command,param) and call the method\n");
            printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
        }
        return true;

    }
    else
    {
      return QtSvgDialGauge::event(event);
    }
}


//tachometer

myQtSvgDialGaugeTachometer::myQtSvgDialGaugeTachometer(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :myQtSvgDialGauge(name, _sock,  _ident,  parent, arg)//:QtSvgDialGauge(parent)
{
    //set look
    setSkin("Tachometer");
    setNeedleOrigin(0.486, 0.466);
    setMinimum(0);//value min
    setMaximum(120);//value max
    setStartAngle(-130);
    setEndAngle(133);

}

myQtSvgDialGaugeTachometer::~myQtSvgDialGaugeTachometer()
{

}

//thermometer

myQtSvgDialGaugeThermometer::myQtSvgDialGaugeThermometer(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
     :myQtSvgDialGauge(name, _sock,  _ident,  parent, arg)//:QtSvgDialGauge(parent)
{

    //set look
    setSkin("Thermometer");
    setNeedleOrigin(0.456, 0.459);
    setMinimum(-30);
    setMaximum(50);
    setStartAngle(-90);
    setEndAngle(150);

}

myQtSvgDialGaugeThermometer::~myQtSvgDialGaugeThermometer()
{

}

//amperemeter
myQtSvgDialGaugeAmperemeter::myQtSvgDialGaugeAmperemeter(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :myQtSvgDialGauge(name, _sock,  _ident,  parent, arg)
{

    //set a default look
    setSkin("Amperemeter");
    setNeedleOrigin(0.5, .83596590);
    setMinimum(0);
    setMaximum(100);
    setStartAngle(-42);
    setEndAngle(42);
}

myQtSvgDialGaugeAmperemeter::~myQtSvgDialGaugeAmperemeter()
{

}



myQt5WayButton::myQt5WayButton(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :Qt5WayButton(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);

    setSkin("Beryl");
    //connect signals and slots
    connect(upButton(), SIGNAL(clicked()), this, SLOT(onUp()));
    connect(downButton(), SIGNAL(clicked()), this, SLOT(onDown()));
    connect(leftButton(), SIGNAL(clicked()), this, SLOT(onLeft()));
    connect(rightButton(), SIGNAL(clicked()), this, SLOT(onRight()));
    connect(centerButton(), SIGNAL(clicked()), this, SLOT(onCenter()));

}

myQt5WayButton::~myQt5WayButton()
{

}

bool myQt5WayButton::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
    PvbEvent *e = (PvbEvent *) event;
    printf("TODO: interpret (command,param) and call the method\n");
    printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
    return true;
  }
  else
  {
    return Qt5WayButton::event(event);
  }
}



void myQt5WayButton::onUp(){
    sprintf(tmp,"user(%d,\"%s\")\n",ident,"UP");
    tcp_send(sock,tmp,strlen(tmp));
}

void myQt5WayButton::onDown(){
    sprintf(tmp,"user(%d,\"%s\")\n",ident,"DOWN");
    tcp_send(sock,tmp,strlen(tmp));
}
void myQt5WayButton::onLeft(){
    sprintf(tmp,"user(%d,\"%s\")\n",ident,"LEFT");
    tcp_send(sock,tmp,strlen(tmp));
}
void myQt5WayButton::onRight(){
    sprintf(tmp,"user(%d,\"%s\")\n",ident,"RIGHT");
    tcp_send(sock,tmp,strlen(tmp));
}
void myQt5WayButton::onCenter(){
    sprintf(tmp,"user(%d,\"%s\")\n",ident,"CENTER");
    tcp_send(sock,tmp,strlen(tmp));
}

myQtBasicDialGauge::myQtBasicDialGauge(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtBasicDialGauge(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValuChanged(int)));

}

myQtBasicDialGauge::~myQtBasicDialGauge()
{

}

bool myQtBasicDialGauge::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
    PvbEvent *e = (PvbEvent *) event;
    printf("TODO: interpret (command,param) and call the method\n");
    printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
    return true;
  }
  else
  {
    return QtBasicDialGauge::event(event);
  }
}



myQtBasicGraph::myQtBasicGraph(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtBasicGraph(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);

     //WARNING: Not tested!
}

myQtBasicGraph::~myQtBasicGraph()
{

}

bool myQtBasicGraph::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
    PvbEvent *e = (PvbEvent *) event;
    printf("TODO: interpret (command,param) and call the method\n");
    printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
    if(strcmp(e->command,"setText") == 0)
    {
      //setText(e->param);
    }
    return true;
  }
  else
  {
    return QtBasicGraph::event(event);
  }
}


myQtMultiSlider::myQtMultiSlider(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtMultiSlider(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);

    //default skin
    setSkin("Beryl");
    connect(topSlider(),SIGNAL(sliderMoved(int)),this,SLOT(onTopChanged(int)));
    connect(bottomSlider(),SIGNAL(sliderMoved(int)),this,SLOT(onBottomChanged(int)));

}

myQtMultiSlider::~myQtMultiSlider()
{

}

bool myQtMultiSlider::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
      int i, val;
      PvbEvent *e=(PvbEvent *)event;
      //printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      if(strncmp(e->command,"setValue(",9) == 0)
      {
          sscanf(e->command, "setValue(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setValue(val);
      }
      else if(strncmp(e->command, "setMinValue(", 12) == 0)
      {
        sscanf(e->command, "setMinValue(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setMinimum(val);
      }
      else if(strncmp(e->command, "setMaxValue(", 12) == 0)
      {
        sscanf(e->command, "setMaxValue(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setMaximum(val);
      }
      else
      {
          printf("TODO: interpret (command,param) and call the method\n");
          printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      }
      return true;
  }
  else
  {
    return QtMultiSlider::event(event);
  }
}

void myQtMultiSlider::onTopChanged(int v){
    sprintf(tmp,"user(%d,\"%d;%s\")\n",ident,v,"TOP");
    tcp_send(sock,tmp,strlen(tmp));
}

void myQtMultiSlider::onBottomChanged(int v){
    sprintf(tmp,"user(%d,\"%d;%s\")\n",ident,v,"BOTTOM");
    tcp_send(sock,tmp,strlen(tmp));
}


myQtScrollDial::myQtScrollDial(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtScrollDial(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);

    //default skin
    //set a default look

    setSkin("Beryl");

    connect(this, SIGNAL(valueChanged(int)), this,  SLOT(onValueChanged(int)));

}

void myQtScrollDial::onValueChanged(int v){
    //send new value
    sprintf(tmp,"slider(%d,%d)\n",ident,v);
    //qDebug(msg);
    tcp_send(sock,tmp,strlen(tmp));

}

myQtScrollDial::~myQtScrollDial()
{

}

bool myQtScrollDial::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
      int i, val;
      PvbEvent *e=(PvbEvent *)event;
      //printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      if(strncmp(e->command,"setValue(",9) == 0)
      {
          sscanf(e->command, "setValue(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setValue(val);
      }
      else if(strncmp(e->command, "setMinValue(", 12) == 0)
      {
        sscanf(e->command, "setMinValue(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setMinimum(val);
      }
      else if(strncmp(e->command, "setMaxValue(", 12) == 0)
      {
        sscanf(e->command, "setMaxValue(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setMaximum(val);
      }
      else
      {
          printf("TODO: interpret (command,param) and call the method\n");
          printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      }
      return true;
  }
  else
  {
    return QtScrollDial::event(event);
  }
}


myQtScrollWheel::myQtScrollWheel(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtScrollWheel(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);

    //default skin
    //set a default look

    setSkin("Beryl");
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
}

myQtScrollWheel::~myQtScrollWheel()
{

}


bool myQtScrollWheel::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
      int i, val;
      PvbEvent *e=(PvbEvent *)event;
      //printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      if(strncmp(e->command,"setValue(",9) == 0)
      {
          sscanf(e->command, "setValue(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setValue(val);
      }
      else if(strncmp(e->command, "setMinValue(", 12) == 0)
      {
        sscanf(e->command, "setMinValue(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setMinimum(val);
      }
      else if(strncmp(e->command, "setMaxValue(", 12) == 0)
      {
        sscanf(e->command, "setMaxValue(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setMaximum(val);
      }
      else
      {
          printf("TODO: interpret (command,param) and call the method\n");
          printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      }
      return true;
  }
  else
  {
    return QtScrollWheel::event(event);
  }
}

void myQtScrollWheel::onValueChanged(int v){
    //slider event
    sprintf(tmp,"slider(%d,%d)\n",ident,v);
    tcp_send(sock,tmp,strlen(tmp));
}


myQtSvgButton::myQtSvgButton(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtSvgButton(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);

    // Usually switches are checkable
    setCheckable(true);
    setChecked(false);
    //setSkin("BerylSquare");
    connect(this,SIGNAL(clicked()),this,SLOT(onClicked()));

}

myQtSvgButton::~myQtSvgButton()
{

}

bool myQtSvgButton::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
    int i,val;
    //char buf[80];
    PvbEvent *e = (PvbEvent *) event;
    if(strncmp(e->command,"setChecked(",11) == 0)
    {
        sscanf(e->command, "setChecked(%d,%d)", &i, &val);
        //printf("%s\n", e->command);
        setChecked(val);
    }
    else if(strncmp(e->command,"setText(",8) == 0)
    {
        printf("myQtSvgButton cmd: %s  param: %s\n", e->command, (const char *)e->param.toUtf8());
        setText(e->param);
    }
    else
    {
        printf("TODO: interpret (command,param) and call the method\n");
        printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
    }
    return true;
  }
  else
  {
    return QtSvgButton::event(event);
  }
}

void myQtSvgButton::onClicked(){
    sprintf(tmp,"QPushButton(%d)\n",ident);
    tcp_send(sock,tmp,strlen(tmp));
}


myQtSvgButtonBerylSquare::myQtSvgButtonBerylSquare(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg)
    :myQtSvgButton(name,_sock,_ident,parent,arg)
{
    setSkin("BerylSquare");
}

myQtSvgButtonBerylSquare::~myQtSvgButtonBerylSquare()
{

}

myQtSvgButtonBeryl::myQtSvgButtonBeryl(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg)
    :myQtSvgButton(name,_sock,_ident,parent,arg)
{
    setSkin("Beryl");
}

myQtSvgButtonBeryl::~myQtSvgButtonBeryl()
{

}

myQtSvgButtonMetallicBrush::myQtSvgButtonMetallicBrush(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg)
    :myQtSvgButton(name,_sock,_ident,parent,arg)
{
    setSkin("MetallicBrush");
}

myQtSvgButtonMetallicBrush::~myQtSvgButtonMetallicBrush()
{

}


myQtSvgSlideSwitch::myQtSvgSlideSwitch(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtSvgSlideSwitch(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);
    setSkin("Beryl");
    connect(this,SIGNAL(toggled(bool)),this,SLOT(onToggled(bool)));

}

myQtSvgSlideSwitch::~myQtSvgSlideSwitch()
{

}

bool myQtSvgSlideSwitch::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
      int i,val;
      //char buf[80];
      PvbEvent *e = (PvbEvent *) event;
      if(strncmp(e->command,"setChecked(",11) == 0)
      {
          sscanf(e->command, "setChecked(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setChecked(val);
      }
      else
      {
          printf("TODO: interpret (command,param) and call the method\n");
          printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      }
      return true;

  }
  else
  {
    return QtSvgSlideSwitch::event(event);
  }
}

void myQtSvgSlideSwitch::onToggled(bool checked){
    sprintf(tmp,"check(%d,%d)\n",ident,checked);
    tcp_send(sock,tmp,strlen(tmp));
}


myQtSvgToggleSwitch::myQtSvgToggleSwitch(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg )
    :QtSvgToggleSwitch(parent)
{
    Q_UNUSED(arg);
    sock = _sock;
    ident = _ident;
    if(name)
        setObjectName(name);
    //set a default look
    setSkin("Beryl");
    connect(this,SIGNAL(toggled(bool)),this,SLOT(onToggled(bool)));


}

myQtSvgToggleSwitch::~myQtSvgToggleSwitch()
{

}


bool myQtSvgToggleSwitch::event(QEvent *event)
{
  if(event->type() == pvbEventNumber)
  {
      int i,val;
      //char buf[80];
      PvbEvent *e = (PvbEvent *) event;
      if(strncmp(e->command,"setChecked(",11) == 0)
      {
          sscanf(e->command, "setChecked(%d,%d)", &i, &val);
          //printf("%s\n", e->command);
          setChecked(val);
      }
      else
      {
          printf("TODO: interpret (command,param) and call the method\n");
          printf("event->command=%s event->param=%s\n", e->command, (const char *) e->param.toUtf8());
      }
      return true;
  }
  else
  {
    return QtSvgToggleSwitch::event(event);
  }
}

void myQtSvgToggleSwitch::onToggled(bool checked){
    sprintf(tmp,"check(%d,%d)\n",ident,checked);
    tcp_send(sock,tmp,strlen(tmp));
}

#ifdef _WIN32
#define MY_EXPORT __declspec(dllexport)
#else
#define MY_EXPORT
#endif

//for pvdevelop, when load this library
// TODO: add icons, info, link
extern "C" MY_EXPORT const char *listWidgets(){
    return "myButton"
            ",myQt5WayButton"
            ",myQtBasicDialGauge"
            ",myQtSvgDialGaugeTachometer"
            ",myQtSvgDialGaugeAmperemeter"
            ",myQtSvgDialGaugeThermometer"
            ",myQtBasicGraph"
            ",myQtMultiSlider"
            ",myQtScrollDial"
            ",myQtScrollWheel"
            ",myQtSvgButtonBeryl"
            ",myQtSvgButtonBerylSquare"
            ",myQtSvgSlideSwitch"
            ",myQtSvgToggleSwitch";
}

//for pvbrowser
//set tcp send pointer to app function
//when load library
extern "C" MY_EXPORT void setTcpSend(int (*_tcp_send)(int *s, const char *msg, int len)){
    //printf("begin try setTcpSend\n");
    if(_tcp_send)
        tcp_send=_tcp_send;
    //printf("end   try setTcpSend\n");
}

//for pvbrowser and pvdevelop
// This our export function
extern "C" MY_EXPORT QWidget *new_pvbCustomWidget(const char *name, int *_sock,int _ident, QWidget *parent, const char *arg)
{
  //widget name is class_name + '_' + ident
  char wname[40];
  sprintf(wname,"%s_%d",name,_ident);

  if(strcmp(name,"myButton") == 0){
      return new myButton(wname, _sock,_ident, parent);
  }
  // TODO: add more custom widgets
  else if(strcmp(name,"myQtSvgDialGauge") == 0)
      return new myQtSvgDialGauge(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtSvgDialGaugeTachometer") == 0)
      return new myQtSvgDialGaugeTachometer(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtSvgDialGaugeAmperemeter") == 0)
      return new myQtSvgDialGaugeAmperemeter(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtSvgDialGaugeThermometer") == 0)
      return new myQtSvgDialGaugeThermometer(wname, _sock,_ident, parent, arg);

  else if(strcmp(name,"myQt5WayButton") == 0)
      return new myQt5WayButton(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtBasicDialGauge") == 0)
      return new myQtBasicDialGauge(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtBasicGraph") == 0)
      return new myQtBasicGraph(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtMultiSlider") == 0)
      return new myQtMultiSlider(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtScrollDial") == 0)
      return new myQtScrollDial(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtScrollWheel") == 0)
      return new myQtScrollWheel(wname, _sock,_ident, parent, arg);

  //removed and added 2 inherited
  //else if(strcmp(name,"myQtSvgButton") == 0)
  //    return new myQtSvgButton(wname, _sock,_ident, parent, arg);

  else if(strcmp(name,"myQtSvgButtonBeryl") == 0)
      return new myQtSvgButtonBeryl(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtSvgButtonBerylSquare") == 0)
      return new myQtSvgButtonBerylSquare(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtSvgButtonMetallicBrush") == 0)
      return new myQtSvgButtonMetallicBrush(wname, _sock,_ident, parent, arg);

  else if(strcmp(name,"myQtSvgSlideSwitch") == 0)
      return new myQtSvgSlideSwitch(wname, _sock,_ident, parent, arg);
  else if(strcmp(name,"myQtSvgToggleSwitch") == 0)
      return new myQtSvgToggleSwitch(wname, _sock,_ident, parent, arg);
  else
    return NULL;

}
/*
extern "C"  int getvinfo(char *dst){
    qDebug()<<"getvinfo";
    strcpy(dst,"v0.2");
    return 1;
}
*/
