#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T14:47:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += webkitwidgets webkit

TARGET = KeyEventTest
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    KeyPressEater.cpp

HEADERS  += MainWindow.h \
    KeyPressEater.h

FORMS    += MainWindow.ui
