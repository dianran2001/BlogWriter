#-------------------------------------------------
#
# Project created by QtCreator 2014-08-04T20:26:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BlogWriter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileop.cpp \
    myeditwidget.cpp

HEADERS  += mainwindow.h \
    fileop.h \
    myeditwidget.h

RESOURCES += \
    image.qrc
