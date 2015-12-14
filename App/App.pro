#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T12:27:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    simulation.cpp \
    car.cpp

HEADERS  += mainwindow.h \
    simulation.h \
    car.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
