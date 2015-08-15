#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T14:34:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newbrushdialog.cpp

HEADERS  += mainwindow.hpp \
    newbrushdialog.hpp

FORMS    += mainwindow.ui \
    newbrushdialog.ui
