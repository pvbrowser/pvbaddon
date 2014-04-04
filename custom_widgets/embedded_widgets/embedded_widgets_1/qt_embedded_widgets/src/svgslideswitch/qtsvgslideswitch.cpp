/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include <QtCore/QResource>
#include <QtCore/QTimeLine>
#include <QMouseEvent>
#include <QPainter>

#include "qtsvgslideswitch.h"

/*!
    
    \class QtSvgSlideSwitch qtsvgslideswitch.h

    The description of the QtSvgSlideSwitch.

    \brief The QtSvgSlideSwitch class provides a slide switch with SVG graphics.

    The QtSvgSlideSwitch is an example to show the capabilities of the Qt Framework
    related to customized controls.

    Here is a possible implementation shown

    \code

        // Create a QtSvgSlideSwitch
        QWidget * widget = new QWidget(this)
        QtBasicGraph * button = new QtSvgSlideSwitch(widget);
        button->setSkin("Beryl");
        widget->addWidget(button);
        widget->show();

    \endcode

    The QtSvgSlideSwitch is a Button that can be dragged and moved to one diffrent state.
    It is like an on/off Button and a inherited QAbstractButton.

    It is important to call the function \a setSkin() to load a skin. If \a setSkin() is not called
    the Button will not have any visible content.
    The parameter \p skin has the skin name. The skins are in the resource file defined in the project file.
    The name scheme in the resource file is "Skin Name"/"unique picture name.svg".

    The \a setSkin() function loads the diffrent skins over the "Skin name".
    The needed realised graphics for this control are "normal.svg", "hovered.svg" and "pressed.svg".
    If you want to add new skins, they have to follow the name scheme to work.

    The actual skin can be read over the \a skin() function.

    \sa skin(), setSkin()

    No Signals are defined.

    private Slots:\n
    \fn setSwitchPosition()

*/

/*!
    Constructor of the widget with \p parent as
    Parent.
*/
QtSvgSlideSwitch::QtSvgSlideSwitch(QWidget * parent)
        : QAbstractButton(parent),
        m_rendererKnob(0),
        m_dragDistanceX(0),
        m_dragInProgress(false),
        m_position(0)
{
    init();
}

/*!
    Destructor
*/
QtSvgSlideSwitch::~QtSvgSlideSwitch()
{
}

/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        QtSvgSlideSwitch * button = new QtSvgSlideSwitch(this);
        button->setSkin("Beryl");
    \endcode

    This function has to be called before using the QtSvgSlideSwitch.

    \sa skin()

*/
void QtSvgSlideSwitch::setSkin(const QString& skin)
{
    m_skin = skin;
    const QString base = ":/svgslideswitch/" + skin + '/';

    m_rendererBase.load(base + "background.svg");
    m_rendererBaseHover.load(base + "background_hover.svg");
    m_rendererKnobOn.load(base + "knob_on.svg");
    m_rendererKnobOff.load(base + "knob_off.svg");

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

/*!

    This function returns the actual skin name. If no skin has been set the return value is "".

    \code
        QtSvgSlideSwitch * button = new QtSvgSlideSwitch(this);
        button->setSkin("Beryl");
        qDebug() << button->skin();
    \endcode

    \sa setSkin()

*/
QString QtSvgSlideSwitch::skin() const
{
    return m_skin;
}

/*!
    \internal
    Internal initialisation function
*/
void QtSvgSlideSwitch::init()
{
    // Usually switches are checkable
    setCheckable(true);
    setChecked(false);

    // Prepare the animated switch:
    m_timeLine = new QTimeLine(150, this);
    m_timeLine->setCurveShape(QTimeLine::EaseInCurve);
    connect(m_timeLine, SIGNAL(frameChanged(int)), SLOT(setSwitchPosition(int)));
    connect(this, SIGNAL(toggled(bool)), this, SLOT(updateSwitchPosition(bool)));
    setAttribute(Qt::WA_Hover);
}

/*!
    \overload
    \internal
    Overloaded paint event to draw the actual state.
*/
void QtSvgSlideSwitch::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    const QRectF button = buttonRect();

    // Render the Button:
    if (underMouse()) {
        m_rendererBaseHover.render(&painter, button);
    } else {
        m_rendererBase.render(&painter, button);
    }

    if (isChecked()) {
        m_rendererKnobOn.render(&painter, knobRect());
    } else {
        m_rendererKnobOff.render(&painter, knobRect());
    }
}

/*!
   \internal
    Calculates the possible QtSvgSlideSwitch visible rect over aspect ratio.
*/
QRectF QtSvgSlideSwitch::buttonRect() const
{
    // Keep aspect ratio:
    QSizeF buttonSize = m_rendererBase.defaultSize();
    buttonSize.scale(size(), Qt::KeepAspectRatio);

    return QRectF(QPointF(0, 0), buttonSize);
}

/*!
   \internal
    Calculates the possible QtSvgSlideSwitch knob in the widget.
*/
QRectF QtSvgSlideSwitch::knobRect() const
{
    QRectF button = buttonRect();
    QSizeF knobSize = m_rendererKnobOn.defaultSize();
    knobSize.scale(button.size(), Qt::KeepAspectRatio);
    QRectF knobRect(button.topLeft(), knobSize);

    // move the rect to the current position
    qreal pos = button.left() + (button.width() - knobSize.width()) * static_cast<qreal>(m_position) / 100.0;
    pos = qMax(button.left(), qMin(pos, button.right() - knobSize.width()));
    knobRect.moveLeft(pos);

    return knobRect;
}

/*!
    \overload
    \internal
    Overloaded function \a mouseMoveEvent().
    The knob will be dragged to the moved position.
*/
void QtSvgSlideSwitch::mouseMoveEvent(QMouseEvent * event)
{
    if (!m_dragInProgress)
        return;

    if (m_dragInProgress) {
        m_dragDistanceX = event->x() - m_dragStartPosition.x();

        if (isChecked())
            m_position = 100 * (buttonRect().width() - knobRect().width() + m_dragDistanceX) / (buttonRect().width() - knobRect().width());
        else
            m_position = 100 * m_dragDistanceX / (buttonRect().width() - knobRect().width());

        if (m_position >= 100) {
            m_position = 100;
            setChecked(true);
        }
        if (m_position <= 0) {
            m_position = 0;
            setChecked(false);
        }
    }

    update();
}

/*!
    \overload
    \internal
    Overloaded function \a mousePressEventEvent().
*/
void QtSvgSlideSwitch::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton &&
            knobRect().contains(event->pos()))
    {
        m_dragInProgress = true;
        m_dragStartPosition = event->pos();
    }
}

/*!
    \overload
    \internal
    Overloaded function \a mouseReleaseEvent().
*/
void QtSvgSlideSwitch::mouseReleaseEvent(QMouseEvent * event)
{
    Q_UNUSED(event)

#ifndef CHECKONCLICK
    if (m_dragDistanceX != 0) {
#endif
        if (m_position < 100) {
            if (isChecked())
                m_timeLine->setFrameRange(100 - m_position, 100);
            else
                m_timeLine->setFrameRange(m_position, 100);
        } else
            m_timeLine->setFrameRange(0, 100);

        if (!(m_dragDistanceX != 0 && (m_position == 0 || m_position == 100)))
            m_timeLine->start();

#ifndef CHECKONCLICK
    }
#endif
    m_dragDistanceX = 0;
    m_dragInProgress = false;
}

/*!
    \overload
    \internal
    Check if the widget has been clicked. Overloaded to
    define own hit area.
*/
bool QtSvgSlideSwitch::hitButton(const QPoint & pos) const
{
    return buttonRect().contains(pos);
}

/*!
    \internal
    Animation to change the state of the widget at the end of the
    set position or the start position. \n
    If one of the two possible states is reached the signal is
    send.
*/
void QtSvgSlideSwitch::setSwitchPosition(int position)
{
    m_position = isChecked() ? 100 - position : position;

    update();

    if (m_position == 100) {
        setChecked(true);
    }
    if (m_position == 0) {
        setChecked(false);
    }

}

/*!
    \internal
    Used to make sure the slider position is correct when the developer
    uses setChecked()
*/
void QtSvgSlideSwitch::updateSwitchPosition(bool checked)
{
    if (checked) {
        m_position = 100;
    } else {
        m_position = 0;
    }
}

/*!
    \overload
    Return size hint provided by the SVG graphics.
    Can be changed during runtime.
*/
QSize QtSvgSlideSwitch::sizeHint() const
{
    if (m_rendererBase.isValid()) {
        return m_rendererBase.defaultSize();
    } else {
        return QSize(100, 24);
    }
}
