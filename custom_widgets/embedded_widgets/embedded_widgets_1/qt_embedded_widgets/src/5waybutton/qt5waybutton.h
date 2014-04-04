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

#ifndef QT_5WAY_BUTTON_H
#define QT_5WAY_BUTTON_H

#include <QtCore/QRect>
#include <QAbstractButton>

class QtSvgPixmapCache;
class NavigationButton;


class Qt5WayButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString skin READ skin WRITE setSkin)
public:
    explicit Qt5WayButton(QWidget * parent = 0);
    virtual ~Qt5WayButton();

    QAbstractButton * upButton();
    QAbstractButton * downButton();
    QAbstractButton * leftButton();
    QAbstractButton * rightButton();
    QAbstractButton * centerButton();

    void setSkin(const QString& skin);
    QString skin() const;

private Q_SLOTS:

protected:
    virtual void resizeEvent(QResizeEvent* event);
    virtual void paintEvent(QPaintEvent* event);
    virtual int heightForWidth ( int w ) const;

private:
    void init();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    /** name of actual skin **/
    QString m_skin;

    /** pointer to one Button **/
    NavigationButton* m_upButton;
    /** pointer to one Button **/
    NavigationButton* m_downButton;
    /** pointer to one Button **/
    NavigationButton* m_leftButton;
    /** pointer to one Button **/
    NavigationButton* m_rightButton;
    /** pointer to one Button **/
    NavigationButton* m_centerButton;

    /** m_rendererBase used to render the skin SVG graphics **/
    QtSvgPixmapCache *m_rendererBase;
};

#undef QSvgRenderer

#endif // QT_5WAY_BUTTON_H
