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

#include "qtmultislider.h"

/*!

    \class QtMultiSlider qtmultislider.h

    The description of the QtMultiSlider.

    \brief The QtMultiSlider class provides a double slider with SVG
    graphics.

    The QtMultiSlider is an example to show the capabilities of the Qt Framework
    related to customized controls.

    Here is a possible implementation shown

    \code

        // Create a QtSvgDialGauge
        QWidget * widget = new QWidget(this);
        QtMultiSlider * slider = new QtMultiSlider("&Range", widget);
        slider->setRange(0, 100);
        slider->setMaximumRange(70);
        slider->setValue(80);
        slider->setSkin("Beryl");
        widget->addWidget(slider);
        widget->show();

    \endcode

    It is important to call the function \a setSkin() to load a skin. If \a setSkin() is not called
    the QtMultiSlider will not have any visible content.
    The parameter \p skin has the skin name. The skins are in the resource file defined in the project file.
    The name scheme in the resource file is "Skin Name"/"unique picture name.svg".

    The \a setSkin() function loads the diffrent skins over the "Skin name".
    The needed graphics for this control are "normal.svg", "hovered.svg" and "pressed.svg".
    If you want to add new skins, they have to follow the name scheme to work.

    The current skin can be read over the \a skin() function.

    \sa skin(), setSkin()


    Signals: \n

    \fn void maximumExceeded()
    \fn void minimumExceeded()

    Slots: \n

    \fn void setMaximumRange()
    \fn void setMinimumRange()
    \fn void setValue()

*/

/*! \class QtMultiSliderHelper qtmultiSlider.h
    \brief Private class of QtMultiSlider
*/

QtMultiSliderHelper::QtMultiSliderHelper(QWidget * parent)
        : QAbstractSlider(parent)
{
    setMouseTracking(true);
}

QtMultiSliderHelper::~QtMultiSliderHelper()
{
}

void QtMultiSliderHelper::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)
}

QtMultiSlider::QtMultiSlider(QWidget * parent)
        : QProgressBar(parent)
{
    init();
}

/*!
    Destructor
*/
QtMultiSlider::~QtMultiSlider()
{
}

/*!
    With this function you can set the skin that will be displayed in the widget.

    \code
        QtMultiSlider * slider = new QtMultiSlider(this);
        button->setSkin("Beryl");
    \endcode

    This function has to be called before using the QtMultiSlider.

    \sa skin()

*/
void QtMultiSlider::setSkin(const QString& skin)
{
    m_skin = skin;
    const QString base = ":/multislider/" + skin + '/';

    m_rendererValueBar->load(base + "valuebar.svg");
    m_rendererValueBarFilled->load(base + "valuebar_filled.svg");
    m_rendererValueBarTop->load(base + "valuebar_top.svg");
    m_rendererValueBarBottom->load(base + "valuebar_bottom.svg");
    m_rendererTopSlider->load(base + "slider_max.svg");
    m_rendererTopSliderHovered->load(base + "slider_max_hovered.svg");
    m_rendererTopSliderPressed->load(base + "slider_max_pressed.svg");
    m_rendererBottomSlider->load(base + "slider_min.svg");
    m_rendererBottomSliderHovered->load(base + "slider_min_hovered.svg");
    m_rendererBottomSliderPressed->load(base + "slider_min_pressed.svg");
    m_rendererGroove->load(base + "groove.svg");

    m_topSliderRenderer = m_rendererTopSlider;
    m_bottomSliderRenderer = m_rendererBottomSlider;

    // update geometry for new sizeHint and repaint
    updateGeometry();
    update();
}

/*!

    This function returns the actual skin name. If no skin has been set the return value is "".

    \code
        QtMultiSlider * slider = new QtMultiSlider(this);
        slider->setSkin("Beryl");
        qDebug() << slider->skin();
    \endcode

    \sa setSkin()

*/
QString QtMultiSlider::skin() const
{
    return m_skin;
}

/*!
    \internal
    Initialize function
*/
void QtMultiSlider::init()
{
    m_previousExceededMaximum = false;
    m_previousExceededMinimum = false;
    m_dragInProgress = false;

    m_rendererValueBar = new QtSvgPixmapCache(this);
    m_rendererValueBarFilled = new QtSvgPixmapCache(this);
    m_rendererValueBarTop = new QtSvgPixmapCache(this);
    m_rendererValueBarBottom = new QtSvgPixmapCache(this);
    m_rendererTopSlider = new QtSvgPixmapCache(this);
    m_rendererTopSliderHovered = new QtSvgPixmapCache(this);
    m_rendererTopSliderPressed = new QtSvgPixmapCache(this);
    m_rendererBottomSlider = new QtSvgPixmapCache(this);
    m_rendererBottomSliderHovered = new QtSvgPixmapCache(this);
    m_rendererBottomSliderPressed = new QtSvgPixmapCache(this);
    m_rendererGroove = new QtSvgPixmapCache(this);

    m_topSliderRenderer = m_rendererTopSlider;
    m_bottomSliderRenderer = m_rendererBottomSlider;

    // Prepare for mouse over ( "hover") detection
    setMouseTracking(true);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    m_topSlider = new QtMultiSliderHelper(this);
    m_topSlider->setValue(maximum());
    m_topSlider->setMaximum(maximum());
    m_topSlider->setMinimum(minimum());

    m_bottomSlider = new QtMultiSliderHelper(this);
    m_bottomSlider->setValue(minimum());
    m_bottomSlider->setMaximum(maximum());
    m_bottomSlider->setMinimum(minimum());

    connect(m_topSlider, SIGNAL(valueChanged(int)), SLOT(checkMaximumRange(int)));
    connect(m_bottomSlider, SIGNAL(valueChanged(int)), SLOT(checkMinimumRange(int)));
}

/*!
    Returns the top slider
*/
QtMultiSliderHelper * QtMultiSlider::topSlider()
{
    return m_topSlider;
}

/*!
    Returns the bottom slider
*/
QtMultiSliderHelper * QtMultiSlider::bottomSlider()
{
    return m_bottomSlider;
}

/*!
    Set the actual vlaue
*/
void QtMultiSlider::setValue(int value)
{
    QProgressBar::setValue(value);

    checkMaximumRange(topSlider()->value());
    checkMinimumRange(bottomSlider()->value());
}

/*!
    Check if the top slider value is bigger than the actual value.
    If true send the signal maximumExceeded(bool).
*/
void QtMultiSlider::checkMaximumRange(int topSliderValue)
{
    const bool exceeded = value() > topSliderValue;
    if (m_previousExceededMaximum != exceeded) {
        m_previousExceededMaximum = exceeded;
        emit maximumExceeded(exceeded);
    }
}

/*!
    Check if the bottom slider value is smaller than the actual value.
    If true send the signal minimumExceeded(bool).
*/
void QtMultiSlider::checkMinimumRange(int bottomSliderValue)
{
    const bool exceeded = value() < bottomSliderValue;
    if (m_previousExceededMinimum != exceeded) {
        m_previousExceededMinimum = exceeded;
        emit minimumExceeded(exceeded);
    }
}

/*!
    Set the maximum range of the topSlider.
*/
void QtMultiSlider::setMaximumRange(int maximum)
{
    topSlider()->setValue(maximum);
}

/*!
    Set the minimum range of the bottomSlider.
*/
void QtMultiSlider::setMinimumRange(int minimum)
{
    bottomSlider()->setValue(minimum);
}

/*!
    \overload
    \internal
    Overloaded paint event that draws all elmements with the
    SVG graphics.
*/
void QtMultiSlider::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event)

    if (!isVisible())
        return;

    QPainter painter;
    painter.begin(this);

    // Calculating the layout:
    int spacing = 5;
    int labelHeight = 0;

    int valueBarWidth = 20;

    // Calculating the maximum string size

    int valueBarX = spacing;

    int valueBarTopY = 0;
    int valueBarBottomY = 0;

    QSizeF originalSize = m_rendererValueBarTop->defaultSize();
    QSizeF targetSize = originalSize;
    targetSize.scale(QSizeF(valueBarWidth, originalSize.height()), Qt::KeepAspectRatio);
    qreal scaleRatio = targetSize.width() /
                       originalSize.width();

    QSize topSliderHandleSize = m_topSliderRenderer->defaultSize() * scaleRatio;
    QSize bottomSliderHandleSize = m_bottomSliderRenderer->defaultSize() * scaleRatio;

    QSize valueBarTopSize = m_rendererValueBarTop->defaultSize() * scaleRatio;


    if (topSliderHandleSize.height() > valueBarTopSize.height())
    {
        valueBarTopY =topSliderHandleSize.height() - valueBarTopSize.height();
    }


    QRect valueBarTopRect = QRect(QPoint(valueBarX, valueBarTopY),
                                  valueBarTopSize);
    m_rendererValueBarTop->render(&painter, valueBarTopRect);

    QSize valueBarBottomSize = m_rendererValueBarBottom->defaultSize() * scaleRatio;

    if (bottomSliderHandleSize.height() > valueBarBottomSize.height()) {
        valueBarBottomY = height() - labelHeight - valueBarTopRect.bottom()
                            - bottomSliderHandleSize.height();
    } else {
        valueBarBottomY = height() - labelHeight - valueBarTopRect.bottom()
                            - valueBarBottomSize.height();
    }

    m_valueBarRect =    QRect(QPoint(valueBarX, valueBarTopRect.bottom()),
                              QSize(valueBarWidth, valueBarBottomY));

    m_rendererValueBar->render(&painter, m_valueBarRect);

    QRect valueBarBottomRect = QRect(QPoint(valueBarX, m_valueBarRect.bottom()),
                                     valueBarBottomSize);
    m_rendererValueBarBottom->render(&painter, valueBarBottomRect);


    // Drawing the actual value bar
    int filledPixels = ((double)value()) / maximum() * m_valueBarRect.height();
    QRect filledRect = m_valueBarRect;
    filledRect.setTop(filledRect.bottom() - filledPixels);
    m_rendererValueBarFilled->render(&painter, filledRect);

    // draw the background of the sliders
    int w = topSliderHandleSize.width() - 20;
    int h = m_valueBarRect.bottom();
    QRect rect(m_valueBarRect.right() + 2 + 15, valueBarTopY, w - 5, h);
    m_rendererGroove->render(&painter, rect);

    // Drawing the min-max sliders
    int sliderSpacing = 2;
    m_topSlider->setGeometry(QRect(
                                 QPoint(m_valueBarRect.right() + sliderSpacing,
                                        m_valueBarRect.bottom() - valueToPixel(topSlider()->value()) - topSliderHandleSize.height()),
                                 topSliderHandleSize
                             ));

    m_topSliderRenderer->render(&painter, m_topSlider->geometry());

    m_bottomSlider->setGeometry(QRect(
                                    QPoint(m_valueBarRect.right() + sliderSpacing,
                                           m_valueBarRect.bottom() - valueToPixel(bottomSlider()->value())),
                                    bottomSliderHandleSize
                                ));

    m_bottomSliderRenderer->render(&painter, m_bottomSlider->geometry());

    painter.end();
}

/*!
    \internal
    This function calculates from the actual value the pixel in the progress bar.
*/
int  QtMultiSlider::valueToPixel(int value)
{
    return (double)(value) / (double)(maximum() - minimum())
           * (double)(m_valueBarRect.bottom() - m_valueBarRect.top());
}

/*!
    \internal
    This function calculates from the actual pixel the set value from the progress bar.
*/
int  QtMultiSlider::pixelToValue(int pixel)
{
    if (pixel < 0)
        return minimum();
    if (pixel > m_valueBarRect.bottom())
        return maximum();

    return (double)(pixel) / (double)(m_valueBarRect.bottom() - m_valueBarRect.top())
           * (double)(maximum() - minimum());
}

/*!
    \internal
    Set the minimum size hint. Can be changed during runtime.
*/
QSize QtMultiSlider::minimumSizeHint() const
{
    return QSize(80, 100);
}

/*!
    \internal
    Set the size hint. Can be changed during runtime.
*/
QSize QtMultiSlider::sizeHint() const
{
    return QSize(80, 150);
}

/*!
    \internal
    \overload
    Update widget if mouse leave the widget area
*/
void QtMultiSlider::leaveEvent(QEvent * event)
{
    Q_UNUSED(event)

    update();
}

/*!
    \internal
    \overload
    Update sliders at mouse move event.
*/
void QtMultiSlider::mouseMoveEvent(QMouseEvent * event)
{
    if (m_topSlider->isSliderDown()) {
        m_topSlider->setValue(pixelToValue(m_valueBarRect.bottom() - (event->y() - (m_dragStartPosition.y() - (m_valueBarRect.bottom() - valueToPixel(m_dragStartValue))))));
        m_bottomSlider->setMaximum(m_topSlider->value());
    }

    if (m_bottomSlider->isSliderDown()) {
        m_bottomSlider->setValue(pixelToValue(m_valueBarRect.bottom() - (event->y() - (m_dragStartPosition.y() - (m_valueBarRect.bottom() - valueToPixel(m_dragStartValue))))));
        m_topSlider->setMinimum(m_bottomSlider->value());
    }

    updateSliders(event);
}

/*!
    \internal
    \overload
    Update sliders at mouse press event.
*/
void QtMultiSlider::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton &&
            (m_topSlider->geometry().contains(event->pos()) || m_bottomSlider->geometry().contains(event->pos()))) {
        m_dragInProgress = true;
        m_dragStartPosition = event->pos();

        if (m_topSlider->geometry().contains(event->pos())) {
            m_topSlider->setSliderDown(true);
            m_dragStartValue = m_topSlider->value();
        }

        if (m_bottomSlider->geometry().contains(event->pos())) {
            m_bottomSlider->setSliderDown(true);
            m_dragStartValue = m_bottomSlider->value();
        }

        updateSliders(event);
    }
}

/*!
    \internal
    \overload
    Update sliders at mouse release event.
*/
void QtMultiSlider::mouseReleaseEvent(QMouseEvent * event)
{
    m_dragInProgress = false;

    m_topSlider->setSliderDown(false);
    m_bottomSlider->setSliderDown(false);

    updateSliders(event);
}

/*!
    \internal
    \overload
    Update slider picture.
*/
void QtMultiSlider::updateSliders(QMouseEvent * event)
{
    QPointer<QtSvgPixmapCache> previousTopSliderRenderer = m_topSliderRenderer;
    QPointer<QtSvgPixmapCache> previousBottomSliderRenderer = m_bottomSliderRenderer;

    //update renderer depending on slider state
    m_topSliderRenderer = m_rendererTopSlider;
    if (m_topSlider->geometry().contains(event->pos())) {
        if (m_topSlider->isSliderDown()) {
            m_topSliderRenderer = m_rendererTopSliderPressed;
        }
        else {
            m_topSliderRenderer = m_rendererTopSliderHovered;
        }
    }

    //update renderer depending on slider state
    m_bottomSliderRenderer = m_rendererBottomSlider;
    if (m_bottomSlider->geometry().contains(event->pos())) {
        if (m_bottomSlider->isSliderDown()) {
            m_bottomSliderRenderer = m_rendererBottomSliderPressed;
        }
        else {
            m_bottomSliderRenderer = m_rendererBottomSliderHovered;
        }
    }

    //repaint sliders on renderer change
    if (previousTopSliderRenderer != m_topSliderRenderer ||
            previousBottomSliderRenderer != m_bottomSliderRenderer) {
        update();
    }
}
