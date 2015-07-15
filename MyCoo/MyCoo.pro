#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T13:46:01
#
#-------------------------------------------------

QT       -= gui

TARGET = MyCoo
TEMPLATE = lib

DEFINES += MYCOO_LIBRARY

SOURCES += mycoo.cpp

HEADERS += mycoo.h\
        mycoo_global.h

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
