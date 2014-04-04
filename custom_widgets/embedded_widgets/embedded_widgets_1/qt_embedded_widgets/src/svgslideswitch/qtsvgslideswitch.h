/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

// Button implemented as a switch
// Compared to a QPushButton it's less likely that this button
// will be pressed accidently
//
#ifndef QT_SVG_SLIDE_SWITCH_H
#define QT_SVG_SLIDE_SWITCH_H

#include <QtCore/QRect>
#include <QtCore/QSharedData>
#include <QtCore/QUrl>
#include <QtCore/QString>
#include <QAbstractButton>

#include "qtsvgpixmapcache.h"

class QTimeLine;

class QtSvgSlideSwitch : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
public:
    explicit QtSvgSlideSwitch(QWidget * parent = 0);
    explicit QtSvgSlideSwitch(const QString & text, QWidget * parent = 0);
    explicit QtSvgSlideSwitch(const QIcon & icon, const QString & text, QWidget * parent = 0);
    virtual ~QtSvgSlideSwitch();

    void setSkin(const QString& skin);
    QString skin() const;

private Q_SLOTS:
    void setSwitchPosition(int position);
    void updateSwitchPosition(bool checked);

private:
    void init();
    QRectF buttonRect() const;
    QRectF knobRect() const;

    virtual void paintEvent(QPaintEvent * event);
    virtual QSize sizeHint() const;

    // Mouse position related events:
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    bool hitButton(const QPoint & pos) const;

    /** needed for anmiation **/
    QTimeLine *m_timeLine;

    QtSvgPixmapCache m_rendererBase;
    QtSvgPixmapCache m_rendererBaseHover;
    QtSvgPixmapCache m_rendererKnobOn;
    QtSvgPixmapCache m_rendererKnobOff;

    QtSvgPixmapCache m_rendererKnob;

    /** Point of the started drag. **/
    QPoint m_dragStartPosition;
    /** Actual drag distance from m_dragStartPosition. **/
    int m_dragDistanceX;
    /** Drag is still in progress (true).**/
    bool m_dragInProgress;

    /** actual position of knob **/
    int   m_position;
    
    /** name of actual skin **/
    QString m_skin;
};

#endif // QT_SVG_SLIDE_SWITCH_H
