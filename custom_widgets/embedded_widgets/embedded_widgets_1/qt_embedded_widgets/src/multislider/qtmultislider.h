/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#ifndef QT_MULTI_SLIDER_H
#define QT_MULTI_SLIDER_H

#include <QtCore/QPointer>
#include <QtCore/QString>
#include <QtCore/QRect>
#include <QtCore/QSharedData>
#include <QAbstractSlider>
#include <QProgressBar>

#include "qtsvgpixmapcache.h"


class QtMultiSliderHelper : public QAbstractSlider
{
    Q_OBJECT
public:
    QtMultiSliderHelper(QWidget * parent = 0);
    virtual ~QtMultiSliderHelper();

private:
    void paintEvent(QPaintEvent * event);
};

class QtMultiSlider : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
public:
    QtMultiSlider(QWidget * parent = 0);
    virtual ~QtMultiSlider();

    QtMultiSliderHelper * topSlider();
    QtMultiSliderHelper * bottomSlider();

    void setSkin(const QString& skin);
    QString skin() const;
public Q_SLOTS:

    void setMaximumRange(int maximum);
    void setMinimumRange(int minimum);
    void setValue(int);

private Q_SLOTS:

    void checkMinimumRange(int value);
    void checkMaximumRange(int value);

Q_SIGNALS:

    void maximumExceeded(bool exceeded);
    void minimumExceeded(bool exceeded);

private:
    QtSvgPixmapCache *m_rendererValueBar;
    QtSvgPixmapCache *m_rendererValueBarFilled;
    QtSvgPixmapCache *m_rendererValueBarTop;
    QtSvgPixmapCache *m_rendererValueBarBottom;

    QtSvgPixmapCache *m_rendererTopSlider;
    QtSvgPixmapCache *m_rendererTopSliderHovered;
    QtSvgPixmapCache *m_rendererTopSliderPressed;

    QtSvgPixmapCache *m_rendererBottomSlider;
    QtSvgPixmapCache *m_rendererBottomSliderHovered;
    QtSvgPixmapCache *m_rendererBottomSliderPressed;

    QtSvgPixmapCache *m_rendererGroove;

    QRect m_valueBarRect;

    bool m_previousExceededMaximum;
    bool m_previousExceededMinimum;

    QPointer<QtMultiSliderHelper> m_topSlider;
    QPointer<QtMultiSliderHelper> m_bottomSlider;

    QPointer<QtSvgPixmapCache> m_topSliderRenderer;
    QPointer<QtSvgPixmapCache> m_bottomSliderRenderer;

    void init();

    void paintEvent(QPaintEvent * event);

    void updateSliders(QMouseEvent * event);

    int  valueToPixel(int value);
    int  pixelToValue(int pixel);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    // Mouse position related events:
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    QPoint m_dragStartPosition;
    int m_dragStartValue;
    bool m_dragInProgress;

    void leaveEvent(QEvent * event);

    QString m_skin;
};

#endif // QT_MULTI_SLIDER_H
