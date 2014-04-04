/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

//Button to switch a property on or off
#ifndef QT_SVG_TOGGLE_SWITCH
#define QT_SVG_TOGGLE_SWITCH
#include <QAbstractButton>
#include <QtCore/QString>
class QSvgRenderer;

class QtSvgToggleSwitch: public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
    public:
        explicit QtSvgToggleSwitch(QWidget * parent = 0);
        virtual ~QtSvgToggleSwitch();

        void setSkin(const QString& skin);
        QString skin() const;
        virtual QSize sizeHint() const;

    private:
        QRect buttonRect() const;

        QSvgRenderer * m_rendererButtonOff;
        QSvgRenderer * m_rendererButtonOn;
        QString m_skin;
    protected:
        void paintEvent(QPaintEvent * event);
};

#endif // QT_SVG_TOGGLE_SWITCH
