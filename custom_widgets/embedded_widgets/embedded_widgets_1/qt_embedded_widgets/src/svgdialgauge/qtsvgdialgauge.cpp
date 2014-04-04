/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

//#include <QPainter>
#include <QtGui/qpainter.h>
#include <QtSvg/QSvgRenderer>

#include "qtsvgdialgauge.h"

#include "qtsvgpixmapcache.h"

/*!

    \class QtSvgDialGauge qtsvgdialgauge.h

    The description of the QtSvgDialGauge.

    \brief The QtSvgDialGauge class provides a dial gauge with SVG graphics.

    The QtSvgDialGauge is an example to show the capabilities of the Qt Framework
    related to customized controls.

    Here is a possible implementation shown

    \code

        // Create a QtSvgDialGauge
        QWidget * widget = new QWidget(this)
        QtSvgDialGauge * gauge = new QtSvgDialGauge(widget);
        gauge->setSkin("Beryl");
        gauge->setNeedleOrigin(0.486, 0.466);
        gauge->setMinimum(0);
        gauge->setMaximum(360);
        gauge->setStartAngle(-130);
        gauge->setEndAngle(133);
        gauge->setValue(0);
        gauge->setMaximumSize(64, 64);

        widget->addWidget(gauge);
        widget->show();

    \endcode

    It is important to call the function \a setSkin() to load a skin. If
    \a setSkin() is not called the Button will not have any visible content.
    The parameter \p skin has the skin name. The skins are in the resource
    file defined in the project file.
    The name scheme in the resource file is "Skin Name"/"unique picture name.svg".

    The \a setSkin() function loads the diffrent skins over the "Skin name".
    The needed realised graphics for this control are "normal.svg", "hovered.svg"
    and "pressed.svg". If you want to add new skins, they have to follow the name
    scheme to work.

    The actual skin can be read over the \a skin() function.

    \sa skin(), setSkin()

    The function \a setNeedleOrigin() sets the origin position of the needle.
    With \a setMinimum() the smallest possible value can be set. With
    \a setMaximum() the biggest possible value can be set. The possible angle can be
    set over the start angle \a setStartAngle() to the end angle \a setEndAngle().
    The actual value is set over \a setValue(). The maximum size of the widget is set
    with the function \a setMaximumSize().

    No Signals are defined.

    Slots
    \fn setValue(int value)

*/

/*!
    Constructor of the widget with \p parent as
    Parent.
*/
QtSvgDialGauge::QtSvgDialGauge(QWidget * parent)
        : QWidget(parent),
        m_minimum(0),
        m_maximum(100),
        m_value(0),
        m_startAngle(0),
        m_endAngle(100),
        m_originX(0.5),
        m_originY(0.5),
        m_showOverlay(true)
{
    init();
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

/*!
    Destructor
*/
QtSvgDialGauge::~QtSvgDialGauge()
{
}

/*!
    \internal
    Private initialization function
*/
void QtSvgDialGauge::init()
{
    m_backgroundRenderer = new QtSvgPixmapCache(this);
    m_needleShadowRenderer = new QtSvgPixmapCache(this);
    m_needleRenderer = new QSvgRenderer(this);
    m_overlayRenderer = new QtSvgPixmapCache(this);
}

/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        QtSvgDialGauge * gauge = new QtSvgDialGauge(this);
        gauge->setSkin("Beryl");
    \endcode

    This function has to be called before using the QtSvgDialGauge.

    \sa skin()

*/
void QtSvgDialGauge::setSkin(const QString& skin)
{
    m_skin = skin;

    const QString base = ":/svgdialgauge/" + skin + '/';

    m_backgroundRenderer->load(base + "background.svg");
    m_needleShadowRenderer->load(base + "needle_shadow.svg");
    m_needleRenderer->load(base + "needle.svg");
    m_overlayRenderer->load(base + "overlay.svg");

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

/*!

    This function returns the actual skin name. If no skin has been set the
    return value is empty.

    \code
        QtSvgDialGauge * gauge = new QtSvgDialGauge(this);
        gauge->setSkin("Beryl");
        qDebug() << gauge->skin();
    \endcode

    \sa setSkin()

*/
QString QtSvgDialGauge::skin() const
{
    return m_skin;
}

/*!
    With the parameter \p value the actual value is set.
*/
void QtSvgDialGauge::setValue(int value)
{
    if (value < m_minimum) {
        value = m_minimum;
    } else if (value > m_maximum) {
        value = m_maximum;
    }
    m_value = value;
    update();
}

/*!
    The function sets the smallest possible value.
*/
void QtSvgDialGauge::setMinimum(int minimum)
{
    m_minimum = minimum;
    if (m_value < m_minimum) {
        m_value = m_minimum;
    }
    update();
}

/*!
    The function sets the bigest possible value.
*/
void QtSvgDialGauge::setMaximum(int maximum)
{
    m_maximum = maximum;
    if (m_value > m_maximum) {
        m_value = m_maximum;
    }
    update();
}

/*!
    The function sets the needle origin in the widget.
*/
void QtSvgDialGauge::setNeedleOrigin(qreal x, qreal y)
{
    m_originX = qMin(static_cast<qreal>(1.0), qMax(static_cast<qreal>(0.0), x));
    m_originY = qMin(static_cast<qreal>(1.0), qMax(static_cast<qreal>(0.0), y));
}

/*!
    The function sets the start angle, the smallest possible angle.
*/
void QtSvgDialGauge::setStartAngle(qreal angle)
{
    m_startAngle = angle;
}

/*!
    The function sets the end angle, the highest possible angle.
*/
void QtSvgDialGauge::setEndAngle(qreal angle)
{
    m_endAngle = angle;
}

/*!
    The function returns the actual set value.
*/
int QtSvgDialGauge::value() const
{
    return m_value;
}

/*!
    The function returns the current minimum value.
*/
int QtSvgDialGauge::minimum() const
{
    return m_minimum;
}

/*!
    The function returns the current maximum value.
*/
int QtSvgDialGauge::maximum() const
{
    return m_maximum;
}

/*!
    The function returns the needle origin x.
*/
qreal QtSvgDialGauge::needleOriginX() const
{
    return m_originX;
}

/*!
    The function returns the needle origin y.
*/
qreal QtSvgDialGauge::needleOriginY() const
{
    return m_originY;
}

/*!
    The function returns the start angle.
*/
qreal QtSvgDialGauge::startAngle() const
{
    return m_startAngle;
}

/*!
    The function returns the end angle.
*/
qreal QtSvgDialGauge::endAngle() const
{
    return m_endAngle;
}


/*!
    \internal
    Calculates the possible QRect for each render object. Needed
    to hold apect ratio of the objects.
*/
QRectF QtSvgDialGauge::availableRect(QtSvgPixmapCache * renderObject) const
{
    // Calculating the layout:
    QSizeF svgSize = renderObject->defaultSize();
    svgSize.scale(size(), Qt::KeepAspectRatio);
    return QRectF(QPointF(0.0, 0.0), svgSize);
}

/*!
    \internal
    \overload
    Overloaded paint event to draw the QtSvgDialGauge components
*/
void QtSvgDialGauge::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    QRectF targetRect;

    qreal angleSpan = m_endAngle - m_startAngle;
    qreal valueSpan = m_maximum - m_minimum;
    qreal rotate = (m_value - m_minimum) / valueSpan * angleSpan + m_startAngle;

    // draw background
    targetRect = availableRect(m_backgroundRenderer);
    painter.translate((width() - targetRect.width()) / 2.0, (height() - targetRect.height()) / 2.0);
    painter.save();

    m_backgroundRenderer->render(&painter, targetRect);

    targetRect = availableRect(m_needleRenderer);
    targetRect.moveTopLeft(QPoint(-targetRect.width() * m_originX,
                                  -targetRect.height() * m_originY));

    // move origin to center of widget and rotate for the needle
    painter.translate(targetRect.width() * m_originX,
                      targetRect.height() * m_originY);

    // draw needle shadow with offset x=2, y=4
    painter.save();
    painter.translate(2, 4);
    painter.rotate(rotate);
    m_needleShadowRenderer->render(&painter, targetRect);

    // draw needle
    painter.restore();
    painter.rotate(rotate);
    m_needleRenderer->render(&painter, targetRect);

    painter.restore();
    if (m_showOverlay) {
        // draw overlay
        targetRect = availableRect(m_overlayRenderer);
        m_overlayRenderer->render(&painter, targetRect);
    }
}

/*!
    \internal
    \overload
    Set default minimum size hint. Can be changed at runtime.
*/
QSize QtSvgDialGauge::minimumSizeHint() const
{
    return QSize(100, 100);
}

/*!
    \internal
    \overload
    Set default size hint. Can be changed at runtime.
*/
QSize QtSvgDialGauge::sizeHint() const
{
    return QSize(400, 400);
}

QRectF QtSvgDialGauge::availableRect(QSvgRenderer * renderObject) const
{
    // Calculating the layout:
    QSizeF svgSize = renderObject->defaultSize();
    svgSize.scale(size(), Qt::KeepAspectRatio);
    return QRectF(QPointF(0.0, 0.0), svgSize);
}

void QtSvgDialGauge::setShowOverlay(bool show) {
    m_showOverlay = show;
    update();
}

