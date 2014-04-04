CONFIG    = qt warn_on release dll
QT       += svg gui widgets
DEFINES  += EMBEDDED_WIDGETS_LIBRARY
TEMPLATE  = lib
TARGET    = ewidgets

QMAKE_LFLAGS += -shared

SOURCES += mywidget.cpp
HEADERS += mywidget.h                \
           embedded_widgets_global.h 

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID2 =0x20004c45
    TARGET.UID3 = 0xE393BFA9
    TARGET.CAPABILITY =NetworkServices
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = ewidgets.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

INCLUDEPATH  += qt_embedded_widgets/src/common
INCLUDEPATH  += qt_embedded_widgets/src/scrolldial
INCLUDEPATH  += qt_embedded_widgets/src/svgtoggleswitch
INCLUDEPATH  += qt_embedded_widgets/src/5waybutton
INCLUDEPATH  += qt_embedded_widgets/src/svgdialgauge
INCLUDEPATH  += qt_embedded_widgets/src/svgslideswitch
INCLUDEPATH  += qt_embedded_widgets/src/svgbutton
INCLUDEPATH  += qt_embedded_widgets/src/basicgraph
INCLUDEPATH  += qt_embedded_widgets/src/multislider
INCLUDEPATH  += qt_embedded_widgets/src/basicdialgauge
INCLUDEPATH  += qt_embedded_widgets/src/scrollwheel

HEADERS += \
    qt_embedded_widgets/src/common/qtsvgpixmapcache.h               \
    qt_embedded_widgets/src/svgtoggleswitch/qtsvgtoggleswitch.h     \
    qt_embedded_widgets/src/5waybutton/qt5waybutton.h               \
    qt_embedded_widgets/src/svgdialgauge/qtsvgdialgauge.h           \
    qt_embedded_widgets/src/svgslideswitch/qtsvgslideswitch.h       \
    qt_embedded_widgets/src/svgbutton/qtsvgbutton.h                 \
    qt_embedded_widgets/src/basicgraph/qtbasicgraph.h               \
    qt_embedded_widgets/src/multislider/qtmultislider.h             \
    qt_embedded_widgets/src/basicdialgauge/qtbasicdialgauge.h       \
    qt_embedded_widgets/src/scrollwheel/qtscrollwheel.h             \
    qt_embedded_widgets/src/scrolldialpopup/scrolldialpopup.h       \
    qt_embedded_widgets/src/scrolldial/qtscrolldial.h               

SOURCES += \
    qt_embedded_widgets/src/common/qtsvgpixmapcache.cpp             \
    qt_embedded_widgets/src/svgtoggleswitch/qtsvgtoggleswitch.cpp   \
    qt_embedded_widgets/src/5waybutton/qt5waybutton.cpp             \
    qt_embedded_widgets/src/svgdialgauge/qtsvgdialgauge.cpp         \
    qt_embedded_widgets/src/svgslideswitch/qtsvgslideswitch.cpp     \
    qt_embedded_widgets/src/svgbutton/qtsvgbutton.cpp               \
    qt_embedded_widgets/src/basicgraph/qtbasicgraph.cpp             \
    qt_embedded_widgets/src/multislider/qtmultislider.cpp           \
    qt_embedded_widgets/src/basicdialgauge/qtbasicdialgauge.cpp     \
    qt_embedded_widgets/src/scrollwheel/qtscrollwheel.cpp           \
    qt_embedded_widgets/src/scrolldialpopup/scrolldialpopup.cpp     \
    qt_embedded_widgets/src/scrolldial/qtscrolldial.cpp             \
    my_qrc.cpp

RESOURCES += \
    qt_embedded_widgets/skins/thermometer_svgdialgauge.qrc \
    qt_embedded_widgets/skins/tachometer_svgdialgauge.qrc \
    qt_embedded_widgets/skins/amperemeter_svgdialgauge.qrc \
    qt_embedded_widgets/skins/beryl_5waybutton.qrc \
    qt_embedded_widgets/skins/beryl_multislider.qrc \
    qt_embedded_widgets/skins/beryl_svgslideswitch.qrc \
    qt_embedded_widgets/skins/beryl_svgbutton.qrc \
    qt_embedded_widgets/skins/beryl_svgtoggleswitch.qrc \
    qt_embedded_widgets/skins/berylsquare_svgtoggleswitch.qrc \
    qt_embedded_widgets/skins/berylsquare_svgbutton.qrc \
    qt_embedded_widgets/skins/beryl_scrollwheel.qrc \
    qt_embedded_widgets/skins/beryl_scrolldial.qrc \
    qt_embedded_widgets/skins/metallicbrush_svgbutton.qrc \
    qt_embedded_widgets/skins/metallicbrush_svgslideswitch.qrc \
    qt_embedded_widgets/skins/tempagua_svgdialgauge.qrc


