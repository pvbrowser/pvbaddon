/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include <QtSvg/QSvgRenderer>
#include <QPainter>


#include <QtSvgToggleSwitch>

/*!

    \class QtSvgToggleSwitch qtsvgtoggleswitch.h

    The description of the QtSvgToggleSwitch.

    \brief The QtSvgToggleSwitch class provides a toggle switch.

    The QtSvgToggleSwitch is an example to show the capabilities of the Qt Framework
    related to customized controls.

    Here is a possible implementation shown

    \code

        // Create a QtSvgToggleSwitch
        QWidget * widget = new QWidget(this)
        QtSvgToggleSwitch * switch = new QtSvgToggleSwitch(widget);
        switch->setSkin("Beryl");
        widget->addWidget(switch);
        widget->show();

    \endcode

    It is important to call the function \a setSkin() to load a skin. If \a setSkin() is not called
    the QtSvgToggleSwitch will not have any visible content.
    The parameter \p skin has the skin name. The skins are in the resource file defined in the project file.
    The name scheme in the resource file is "Skin Name"/"unique picture name.svg".

    The \a setSkin() function loads the diffrent skins over the "Skin name".
    The needed realised graphics for this control are "normal.svg", "hovered.svg" and "pressed.svg".
    If you want to add new skins, they have to follow the name scheme to work.

    The actual skin can be read over the \a skin() function.

    \sa skin(), setSkin()


    No Signals defined. \n

    No Slots defined.


*/

/*!
    Constructor of the QtMultiSliderHelper.
    The \a parent object holds the Parent of the QAbstractButton.
*/
QtSvgToggleSwitch::QtSvgToggleSwitch(QWidget * parent) : QAbstractButton(parent)
{
    m_rendererButtonOff = new QSvgRenderer(this);
    m_rendererButtonOn = new QSvgRenderer(this);

    setCheckable(true);
}

/*!
    Destructor
*/
QtSvgToggleSwitch::~QtSvgToggleSwitch()
{
}

/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        QtSvgToggleSwitch * switch = new QtSvgToggleSwitch(this);
        switch->setSkin("Beryl");
    \endcode

    This function has to be called before using the QtSvgToggleSwitch.

    \sa skin()

*/
void QtSvgToggleSwitch::setSkin(const QString& skin)
{
    m_skin = skin;
    const QString base = ":/svgtoggleswitch/" + skin + '/';

    m_rendererButtonOff->load(base + "off.svg");
    m_rendererButtonOn->load(base + "on.svg");

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

/*!

    This function returns the actual skin name. If no skin has been set the return value is "".

    \code
        QtSvgToggleSwitch * switch = new QtSvgToggleSwitch(this);
        switch->setSkin("Beryl");
        qDebug() << switch->skin();
    \endcode

    \sa setSkin()

*/
QString QtSvgToggleSwitch::skin() const
{
    return m_skin;
}

/*!
    \internal
    Calculate the button rectangle and keep aspect ratio.
*/
QRect QtSvgToggleSwitch::buttonRect() const
{
    // Keep aspect ratio, always aligned to the left.
    // Later, if a label can be shown to the right
    QSize buttonSize = m_rendererButtonOff->defaultSize();
    buttonSize.scale(size(), Qt::KeepAspectRatio);
    return QRect(QPoint(0, 0), buttonSize);
}

/*!
    \internal
    \overload
    Overload paint event to render the SVG graphics.
*/
void QtSvgToggleSwitch::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if (!isChecked()) {
        m_rendererButtonOff->render(&painter, buttonRect());
    } else {
        m_rendererButtonOn->render(&painter, buttonRect());
    }
}

/*!
    \internal
    \overload
    Set size hint. Can be changed at runtime.
*/
QSize QtSvgToggleSwitch::sizeHint() const
{
    if (m_rendererButtonOn->isValid()) {
        return m_rendererButtonOn->defaultSize();
    } else {
        return QAbstractButton::sizeHint();
    }
}
