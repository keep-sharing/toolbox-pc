QT += core gui network serialport
win32:CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    basicmethod.cpp \
    connectting.cpp \
    main.cpp \
    myControl/dragdialog.cpp \
    myControl/messagebox.cpp \
    myControl/mycombobox.cpp \
    myControl/mylineedit.cpp \
    myControl/mymessagebox.cpp \
    myControl/mywidget.cpp \
    myControl/mywindowstytle.cpp \
    myControl/tableviewdelegate.cpp \
    passwordverify.cpp \
    radiusprogressbar.cpp \
    serialportsetting.cpp \
    toolbox.cpp \
    unp/qunp.cpp \
    upgradewnd.cpp \
    waitingwnd.cpp

HEADERS += \
    basicmethod.h \
    connectting.h \
    myControl/dragdialog.h \
    myControl/messagebox.h \
    myControl/mycombobox.h \
    myControl/mylineedit.h \
    myControl/mymessagebox.h \
    myControl/mywidget.h \
    myControl/mywindowstytle.h \
    myControl/tableviewdelegate.h \
    passwordverify.h \
    radiusprogressbar.h \
    serialportsetting.h \
    toolbox.h \
    unp/qunp.h \
    unxx_params.h \
    upgradewnd.h \
    version.h \
    waitingwnd.h

FORMS += \
    myControl/messagebox.ui \
    myControl/mymessagebox.ui \
    passwordverify.ui \
    serialportsetting.ui \
    toolbox.ui \
    upgradewnd.ui \
    waitingwnd.ui

INCLUDEPATH += $$PWD/ucxx14 \
               $$PWD/ucxx22 \
               $$PWD/ucxx52

include($$PWD/ucxx14/ucxx14.pri)
include($$PWD/ucxx22/ucxx22.pri)
include($$PWD/ucxx52/ucxx52.pri)

TRANSLATIONS += \
    ToolBox_zh_CN.ts

RESOURCES += image/image.qrc

RC_FILE += version.rc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

