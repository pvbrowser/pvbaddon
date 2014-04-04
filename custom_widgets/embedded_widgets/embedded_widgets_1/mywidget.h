#include <qpushbutton.h>
#include <qevent.h>

//no need to declare this on mywidget.h
//extern "C" QWidget *new_pvbCustomWidget(const char *name, int *_sock,int _ident, int (*_tcp_send)(int *s, const char *msg, int len), QWidget *parent);
//extern "C" QWidget *new_pvbCustomWidget(const char *name, int *_sock,int _ident,  QWidget *parent);
//for pvdevelop
//extern "C" const char *listWidgets();


const QEvent::Type pvbEventNumber = (QEvent::Type) (QEvent::User + 1);

class PvbEvent : public QEvent
{
public:
  PvbEvent(const char *_command, QString _param, QEvent::Type _event=pvbEventNumber); 
  virtual ~PvbEvent();
  const char *command;
  QString    param;  
};

class myButton : public QPushButton
{
  Q_OBJECT
public:
  myButton(const char *name=NULL, int *_sock=NULL, int _ident=0, QWidget *parent=0);
  ~myButton();
  virtual bool event(QEvent *event);
public slots:
  void slotClicked();
private:
  int *sock;
  int ident;
};

#include "qt_embedded_widgets/src/common/qtsvgpixmapcache.h"
#include "qt_embedded_widgets/src/scrolldial/scrolldialpopup.h"
#include "qt_embedded_widgets/src/scrolldial/qtscrolldial.h"
#include "qt_embedded_widgets/src/svgtoggleswitch/qtsvgtoggleswitch.h"
#include "qt_embedded_widgets/src/5waybutton/qt5waybutton.h"
#include "qt_embedded_widgets/src/svgdialgauge/qtsvgdialgauge.h"
#include "qt_embedded_widgets/src/svgslideswitch/qtsvgslideswitch.h"
#include "qt_embedded_widgets/src/svgbutton/qtsvgbutton.h"
#include "qt_embedded_widgets/src/basicgraph/qtbasicgraph.h"
#include "qt_embedded_widgets/src/multislider/qtmultislider.h"
#include "qt_embedded_widgets/src/basicdialgauge/qtbasicdialgauge.h"
#include "qt_embedded_widgets/src/scrollwheel/qtscrollwheel.h"
#include "qt_embedded_widgets/src/scrolldialpopup/scrolldialpopup.h"


//#include <QtSvgDialGauge>
//base class for gauges
class  myQtSvgDialGauge: public QtSvgDialGauge{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    myQtSvgDialGauge(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgDialGauge();
    virtual bool event(QEvent *event);
protected:
  int *sock;
  int ident;};

class  myQtSvgDialGaugeTachometer: public myQtSvgDialGauge{
public:
    myQtSvgDialGaugeTachometer(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgDialGaugeTachometer();
};

class  myQtSvgDialGaugeThermometer: public myQtSvgDialGauge{
public:
    myQtSvgDialGaugeThermometer(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgDialGaugeThermometer();

};

class  myQtSvgDialGaugeAmperemeter: public myQtSvgDialGauge{
public:
    myQtSvgDialGaugeAmperemeter(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgDialGaugeAmperemeter();
};


//#include <Qt5WayButton>
class  myQt5WayButton: public Qt5WayButton{
Q_OBJECT
public:
    myQt5WayButton(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQt5WayButton();
    virtual bool event(QEvent *event);

public slots:
    void onUp();
    void onDown();
    void onLeft();
    void onRight();
    void onCenter();

protected:
  int *sock;
  int ident;
};


//#include <QtBasicDialGauge>
class  myQtBasicDialGauge: public QtBasicDialGauge{
Q_OBJECT
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue)

public:
    myQtBasicDialGauge(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtBasicDialGauge();
    virtual bool event(QEvent *event);

public slots:
    //void onValueChanged(int newval);
protected:
  int *sock;
  int ident;
};


//#include <QtBasicGraph>
class  myQtBasicGraph: public QtBasicGraph{
public:
    myQtBasicGraph(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtBasicGraph();
    virtual bool event(QEvent *event);
protected:
  int *sock;
  int ident;
};


//#include <QtMultiSlider>
class  myQtMultiSlider: public QtMultiSlider{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    myQtMultiSlider(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtMultiSlider();
    virtual bool event(QEvent *event);
public slots:
    void onTopChanged(int newval);
    void onBottomChanged(int newval);
protected:
  int *sock;
  int ident;
};


//#include <QtScrollDial>
class  myQtScrollDial: public QtScrollDial{
    Q_OBJECT
public:
    myQtScrollDial(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtScrollDial();
    virtual bool event(QEvent *event);
public slots:
    void onValueChanged(int newval);
protected:
  int *sock;
  int ident;
};


//#include <QtScrollWheel>
class  myQtScrollWheel: public QtScrollWheel{
    Q_OBJECT
public:
    myQtScrollWheel(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtScrollWheel();
    virtual bool event(QEvent *event);
public slots:
    void onValueChanged(int newval);
protected:
  int *sock;
  int ident;
};

//#include <QtSvgButton>
class  myQtSvgButton: public QtSvgButton{
    Q_OBJECT
public:
    myQtSvgButton(const char * name, int *_sock, int _ident, QWidget * parent , const char *arg);
    ~myQtSvgButton();
    virtual bool event(QEvent *event);
public slots:
    void onClicked();
protected:
  int *sock;
  int ident;
};

class  myQtSvgButtonBerylSquare: public myQtSvgButton{
public:
    myQtSvgButtonBerylSquare(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgButtonBerylSquare();
};

class  myQtSvgButtonBeryl: public myQtSvgButton{
public:
    myQtSvgButtonBeryl(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgButtonBeryl();
};

class  myQtSvgButtonMetallicBrush: public myQtSvgButton{
public:
    myQtSvgButtonMetallicBrush(const char * name, int *_sock, int _ident, QWidget * parent, const char *arg);
    ~myQtSvgButtonMetallicBrush();
};


//#include <QtSvgSlideSwitch>
class  myQtSvgSlideSwitch: public QtSvgSlideSwitch{
    Q_OBJECT
public:
    myQtSvgSlideSwitch(const char * name, int *_sock, int _ident, QWidget * parent , const char *arg);
    ~myQtSvgSlideSwitch();
    virtual bool event(QEvent *event);

public slots:
    //void onClicked(bool checked);
    void onToggled(bool checked);

protected:
  int *sock;
  int ident;
};

//#include <QtSvgToggleSwitch>
class  myQtSvgToggleSwitch: public QtSvgToggleSwitch{
    Q_OBJECT
public:
    myQtSvgToggleSwitch(const char * name, int *_sock, int _ident, QWidget * parent , const char *arg);
    ~myQtSvgToggleSwitch();
    virtual bool event(QEvent *event);

public slots:
    //void onClicked(bool checked);
    void onToggled(bool checked);

protected:
  int *sock;
  int ident;
};
