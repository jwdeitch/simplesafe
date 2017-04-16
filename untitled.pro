#-------------------------------------------------
#
# Project created by QtCreator 2017-04-15T18:58:00
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    appdata.cpp \
    fs.cpp \
    simplecrypt.cpp

HEADERS  += mainwindow.h \
    appdata.h \
    fs.h \
    simplecrypt.h

FORMS    += mainwindow.ui
