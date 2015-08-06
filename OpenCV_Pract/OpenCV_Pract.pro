#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T15:33:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV_Pract
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    salt.cpp \
    colorreduce.cpp \
    sharpen.cpp \
    colordetector.cpp \
    linefinder.cpp

HEADERS  += mainwindow.h \
    salt.h \
    colorreduce.h \
    sharpen.h \
    colordetector.h \
    linefinder.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui
