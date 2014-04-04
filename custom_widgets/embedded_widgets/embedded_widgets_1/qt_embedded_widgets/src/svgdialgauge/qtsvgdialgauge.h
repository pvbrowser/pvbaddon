/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#ifndef QT_SVG_DIAL_GAUGE
#define QT_SVG_DIAL_GAUGE
#include <QWidget>
#include <QtCore/QPair>


class QSvgRenderer;
class QtSvgPixmapCache;

class QtSvgDialGauge :  public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(qreal startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(qreal endAngle READ endAngle WRITE setEndAngle)



public:
    explicit QtSvgDialGauge(QWidget * parent = 0);
    ~QtSvgDialGauge();

    void setSkin(const QString& skin);
    QString skin() const;


    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void setNeedleOrigin(qreal x, qreal y);
    void setStartAngle(qreal angle);
    void setEndAngle(qreal angle);

    int value() const;
    int minimum() const;
    int maximum() const;
    qreal needleOriginX() const;
    qreal needleOriginY() const;
    qreal startAngle() const;
    qreal endAngle() const;

    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
    void setShowOverlay(bool);

public slots:
    void setValue(int value);

private:
    void init();
    QRectF availableRect(QtSvgPixmapCache * renderObject) const;

    QtSvgPixmapCache* m_backgroundRenderer;
    QtSvgPixmapCache* m_needleShadowRenderer;
    QSvgRenderer* m_needleRenderer;
    QRectF availableRect(QSvgRenderer * renderObject) const;
    QtSvgPixmapCache* m_overlayRenderer;
    /** minimum possible value **/
    int m_minimum;
    /** maximum possible value **/
    int m_maximum;
    /** actual value **/
    int m_value;
    /** smallest start angle **/
    qreal m_startAngle;
    /** highest end angle **/
    qreal m_endAngle;
    /** position x of needle **/
    qreal m_originX;
    /** position y of needle **/
    qreal m_originY;
    bool m_showOverlay;

    /** name of actual skin **/
    QString m_skin;
protected:
    void paintEvent(QPaintEvent * event);
};

#endif // QT_SVG_DIAL_GAUGE
