#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T16:57:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenVR-Inspector
TEMPLATE = app


SOURCES  += src/main.cpp \
            src/gui/mainwindow.cpp \
            src/gui/deviceitempage.cpp \
            src/model/itemviewmodel.cpp 

HEADERS  += src/logging.h \
            src/gui/mainwindow.h \
            src/gui/deviceitempage.h \
            src/model/itemviewmodel.h 

FORMS    += src/gui/mainwindow.ui \
            src/gui/deviceitempage.ui 

INCLUDEPATH += third-party/openvr/headers \
               third-party/easylogging++

LIBS += -Lthird-party/openvr/lib/win64 -lopenvr_api

DESTDIR = bin/win64
