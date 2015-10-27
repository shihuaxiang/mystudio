#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T20:26:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = wheelTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphics_view_zoom.cpp

HEADERS  += mainwindow.h \
    graphics_view_zoom.h

FORMS    += mainwindow.ui

CONFIG(debug, debug|release){
    #output
    DESTDIR = $$PWD/../../bin/debug
    MOC_DIR += $$PWD/GeneratedFiles/debug
    OBJECTS_DIR += $$PWD/GeneratedFiles/debug
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles
}else{
    #output
    DESTDIR = $$PWD/../../bin/release
    MOC_DIR += $$PWD/GeneratedFiles/release
    OBJECTS_DIR += $$PWD/GeneratedFiles/release
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles
}
