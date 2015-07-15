#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T13:46:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += debug release

TARGET = MyApp
TEMPLATE = app

SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

CONFIG(debug, debug|release){
    #output
    DESTDIR = $$PWD/../bin/debug
    MOC_DIR += $$PWD/GeneratedFiles/debug
    OBJECTS_DIR += $$PWD/GeneratedFiles/debug
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles

    #libs
    INCLUDEPATH += $$PWD/../MyCoo
    INCLUDEPATH += $$PWD/../MyUtil
    DEPENDPATH += $$PWD/../bin/debug/
    LIBS += -L$$PWD/../bin/debug/
}else{
    #output
    DESTDIR = $$PWD/../bin/release
    MOC_DIR += $$PWD/GeneratedFiles/release
    OBJECTS_DIR += $$PWD/GeneratedFiles/release
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles

    #libs
    INCLUDEPATH += $$PWD/../MyCoo
    INCLUDEPATH += $$PWD/../MyUtil
    DEPENDPATH += $$PWD/../bin/release/
    LIBS += -L$$PWD/../bin/release/
}

win32:CONFIG(release, debug|release): LIBS += -lMyCoo -lMyUtil
else:win32:CONFIG(debug, debug|release): LIBS += -lMyCoo -lMyUtil
else:unix: LIBS += -lMyCoo -lMyUtil
