/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#ifndef QT_SVG_BUTTON_H
#define QT_SVG_BUTTON_H

#include <QAbstractButton>
#include <QPicture>

class QSvgRenderer;

class QtSvgButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
public:
    explicit QtSvgButton(QWidget * parent = 0);
    ~QtSvgButton();

    void setSkin(const QString& skin);
    QString skin() const;

    virtual QSize sizeHint() const;

private:
    QRect buttonRect() const;

    /** The default button size, need to calculate aspect ratio. **/ 
    QSize m_defaultSize;
    
    /** The loaded SVG picture "normal.svg". **/     
    QPicture m_normal;
    /** The loaded SVG picture "hovered.svg". **/     
    QPicture m_hovered;
    /** The loaded SVG picture "hovered.svg". **/     
    QPicture m_pressed;
    /** The actual skin name. **/     
    QString m_skin;

protected:
    virtual void paintEvent(QPaintEvent* event);
};

#endif // QT_SVG_BUTTON_H
