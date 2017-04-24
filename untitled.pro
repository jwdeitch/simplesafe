#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T18:58:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSafe
TEMPLATE = app

macx:ICON = $${PWD}/safe.icns
macx:QMAKE_INFO_PLIST = $${PWD}/info.plist

include(botan.pri)

SOURCES += sources/main.cpp\
        sources/mainwindow.cpp \
    sources/appdata.cpp \
    sources/fs.cpp \
    sources/simplecrypt.cpp \
    sources/safeitem.cpp \
    sources/botanwrapper.cpp \
    sources/botan.cpp \
    sources/lockscreen.cpp \
    sources/passwordgenerator.cpp

HEADERS  += headers/mainwindow.h \
    headers/appdata.h \
    headers/fs.h \
    headers/simplecrypt.h \
    headers/safeitem.h \
    headers/botan.h \
    headers/botanwrapper.h \
    headers/lockscreen.h \
    headers/passwordgenerator.h

FORMS    += forms/mainwindow.ui \
    forms/safeitem.ui \
    forms/lockscreen.ui \
    forms/passwordgenerator.ui

RESOURCES += \
    resources.qrc
