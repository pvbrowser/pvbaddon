/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include <QtCore/QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QAbstractButton>
#include <QGridLayout>
#include <QBitmap>

#include "qt5waybutton.h"

#include "qtsvgpixmapcache.h"



/*!
    \class Qt5WayButton

    \brief The Qt5WayButton provides a button group with SVG graphics.

    Qt5WayButton is a widget that consists of five Buttons, one on any edge
    and one in the middle of the widget. Each button is represented as a
    QAbstractButton and can be accessed with the methods \a upButton(),
    \a downButton(), \a leftButton(), \a rightButton(), \a centerButton().
    The returned buttons can then be used to connect signals and slots or to
    change properties like the checkable state.

    \section qt5waybutton_example Example Usage
    The following example shows how to create a Qt5WayButton.
    \code
    Qt5WayButton* button = new Qt5WayButton(parent);
    button->setSkin("Beryl");
    QObject::connect(button->upButton(), SIGNAL(clicked()), this, SLOT(moveUp()));
    \endcode

    \section qt5waybutton_skin Setting a Skin

    After creating a new Qt5WayButton a skin needs to be set by calling
    \a setSkin(). Without a skin set, a Qt5WayButton will not have any
    visible content. skin() returns the current skin.
    Further details about skinning the Qt5WayButton can be found in the
    widget description.
*/

/*!
    \class NavigationButton
    \brief Private helper class which is used for the region and events of the Buttons.
*/
class NavigationButton : public QAbstractButton
{
public:
    NavigationButton(QWidget* parent) : QAbstractButton(parent)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_normal = new QtSvgPixmapCache(this);
        m_pressed = new QtSvgPixmapCache(this);
        m_hovered = new QtSvgPixmapCache(this);
    }

    virtual ~NavigationButton() {}

    void setSkin(const QString& skin, const QString& name)
    {
        const QString base = ":/5waybutton/" + skin + '/' + name;
        m_normal->load(base + ".svg");
        m_pressed->load(base + "_pressed.svg");
        m_hovered->load(base + "_hover.svg");
    }

    void paint(QPainter* painter)
    {
        if (isDown() || isChecked()) {
            m_pressed->render(painter, geometry());
        } else if (underMouse()) {
            m_hovered->render(painter, geometry());
        } else {
            m_normal->render(painter, geometry());
        }
    }

    void updateMask()
    {
        QPixmap pixmap(size());
        pixmap.fill();

        QPainter painter(&pixmap);
        m_normal->render(&painter, rect());
        painter.end();

        QBitmap bitmap = pixmap.createHeuristicMask();
        setMask(bitmap);
        update();
    }


protected:
    // Implemented to sacrifice pure virtual
    virtual void paintEvent(QPaintEvent*) {}

    virtual void enterEvent(QEvent*)
    {
        parentWidget()->update();
    }

    virtual void leaveEvent(QEvent * event)
    {
        Q_UNUSED(event);
        parentWidget()->update();
    }

private:
    QtSvgPixmapCache *m_normal;
    QtSvgPixmapCache *m_pressed;
    QtSvgPixmapCache *m_hovered;
};


/*!
    Constructor of the widget with  parent as
    Parent.
*/
Qt5WayButton::Qt5WayButton(QWidget * parent)
    : QWidget(parent)
{
    init();
}
/*!
    Destructor
*/
Qt5WayButton::~Qt5WayButton()
{
}
/*!
    \internal
    Internal initalisation function
*/
void Qt5WayButton::init()
{
    QSizePolicy sp;
    sp.setHeightForWidth(true);
    setSizePolicy(sp);

    QGridLayout* grid = new QGridLayout(this);
    grid->setMargin(0);
    grid->setSpacing(0);

    m_upButton = new NavigationButton(this);
    m_downButton = new NavigationButton(this);
    m_leftButton = new NavigationButton(this);
    m_rightButton = new NavigationButton(this);
    m_centerButton = new NavigationButton(this);

    grid->addWidget(m_upButton, 0, 0, 1, 2);
    grid->addWidget(m_downButton, 1, 0, 1, 2);
    grid->addWidget(m_leftButton, 0, 0, 2, 1);
    grid->addWidget(m_rightButton, 0, 1, 2, 1);
    grid->addWidget(m_centerButton, 0, 0, 2, 2);

    m_rendererBase = new QtSvgPixmapCache(this);
}
/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        button->setSkin("Beryl");
    \endcode

    This function has to be called before using the Qt5WayButton.

    \sa skin()

*/
void Qt5WayButton::setSkin(const QString& skin)
{
    m_skin = skin;

    const QString base = ":/5waybutton/" + skin + '/';
    m_rendererBase->load(base + "background.svg");

    m_upButton->setSkin(skin, "up");
    m_downButton->setSkin(skin, "down");
    m_leftButton->setSkin(skin, "left");
    m_rightButton->setSkin(skin, "right");
    m_centerButton->setSkin(skin, "center");

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();

    m_upButton->updateMask();
    m_downButton->updateMask();
    m_leftButton->updateMask();
    m_rightButton->updateMask();
    m_centerButton->updateMask();


}

/*!

    This function returns the actual skin name. If no skin has been set the
    return value is "".

    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        button->setSkin("Beryl");
        qDebug() << button->skin();
    \endcode

    \sa setSkin()

*/
QString Qt5WayButton::skin() const
{
    return m_skin;
}

/*!
    This function returns the actual pointer from the upButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::upButton()
{
    return m_upButton;
}

/*!
    This function returns the actual pointer from the downButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->downButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::downButton()
{
    return m_downButton;
}

/*!
    This function returns the actual pointer from the leftButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->leftButton(), (pressed()), button->rightButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::leftButton()
{
    return m_leftButton;
}

/*!
    This function returns the actual pointer from the rightButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->leftButton(), (pressed()), button->rightButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::rightButton()
{
    return m_rightButton;
}

/*!
    This function returns the actual pointer from the centerButton.
    Here you can connect to the Signals/Slots from QAbstractButton
    \code
        Qt5WayButton * button = new Qt5WayButton(this);
        QObject::connect(button->upButton(), (pressed()), button->centerButton(), (clicked()));
    \endcode
*/
QAbstractButton * Qt5WayButton::centerButton()
{
    return m_centerButton;
}

/*!
    \overload
    The \a paintEvent() draws the Qt5WayButton and shows the actual state
    "normal", "hovered", "clicked" from the button.
*/
void Qt5WayButton::paintEvent(QPaintEvent * event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    m_rendererBase->render(&painter, m_centerButton->geometry());

    m_upButton->paint(&painter);
    m_downButton->paint(&painter);
    m_leftButton->paint(&painter);
    m_rightButton->paint(&painter);
    m_centerButton->paint(&painter);
}

/*!
    \overload
    To provide a minimum size hint at startup. Can be changed at runtime.
*/
QSize Qt5WayButton::minimumSizeHint() const
{
    return QSize(100, 100);
}

/*!
    \overload
    To provide a size hint at startup. Can be changed at runtime.
*/
QSize Qt5WayButton::sizeHint() const
{
    return QSize(150, 150);
}

/*!
    \overload
    \internal
    To update the clickable area of the Buttons on size change.
*/
void Qt5WayButton::resizeEvent(QResizeEvent* event)
{
    // update masks
    m_upButton->updateMask();
    m_downButton->updateMask();
    m_leftButton->updateMask();
    m_rightButton->updateMask();
    m_centerButton->updateMask();

    QWidget::resizeEvent(event);
}

/*!
    \overload
    To be sure that the width and the height are always the same size.
*/
int Qt5WayButton::heightForWidth(int w) const
{
    return w;
}
