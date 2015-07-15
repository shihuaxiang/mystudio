#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T15:04:05
#
#-------------------------------------------------

QT       -= gui

TARGET = MyUtil
TEMPLATE = lib

DEFINES += MYUTIL_LIBRARY

SOURCES += myutil.cpp

HEADERS += myutil.h\
        myutil_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release){
    #output
    DESTDIR = $$PWD/../bin/debug
    MOC_DIR += $$PWD/GeneratedFiles/debug
    OBJECTS_DIR += $$PWD/GeneratedFiles/debug
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles
}else{
    #output
    DESTDIR = $$PWD/../bin/release
    MOC_DIR += $$PWD/GeneratedFiles/release
    OBJECTS_DIR += $$PWD/GeneratedFiles/release
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles
}
