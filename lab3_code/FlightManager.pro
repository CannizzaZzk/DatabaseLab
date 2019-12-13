#-------------------------------------------------
#
# Project created by QtCreator 2019-06-12T20:43:24
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlightManager
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    addproduct.cpp \
    adminorder.cpp \
    adminwelcome.cpp \
    dataconnect.cpp \
    login.cpp \
    register.cpp \
    useranocmnt.cpp \
    userbill.cpp \
    userbuyticket.cpp \
    userolpay.cpp \
    userorder.cpp \
    userwelcome.cpp \
    adminflight.cpp \
    userflight.cpp

HEADERS += \
    addproduct.h \
    adminorder.h \
    adminwelcome.h \
    dataconnect.h \
    login.h \
    register.h \
    useranocmnt.h \
    userbill.h \
    userbuyticket.h \
    userolpay.h \
    userorder.h \
    userwelcome.h \
    adminflight.h \
    userflight.h

FORMS += \
    addproduct.ui \
    adminorder.ui \
    adminwelcome.ui \
    login.ui \
    register.ui \
    useranocmnt.ui \
    userbill.ui \
    userbuyticket.ui \
    userolpay.ui \
    userorder.ui \
    userwelcome.ui \
    adminflight.ui \
    userflight.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    drawable.qrc
