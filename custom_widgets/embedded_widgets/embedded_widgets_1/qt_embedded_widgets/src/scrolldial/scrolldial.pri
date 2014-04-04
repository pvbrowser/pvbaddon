INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
HEADERS += $$PWD/qtscrolldial.h \
           $$PWD/scrolldialpopup.h
SOURCES += $$PWD/qtscrolldial.cpp \
           $$PWD/scrolldialpopup.cpp

include(../basicdialgauge/basicdialgauge.pri)
include(../scrollwheel/scrollwheel.pri)

QT += svg
