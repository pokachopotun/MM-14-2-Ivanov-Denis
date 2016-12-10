#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T14:25:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = fourie
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mathadditionals/mathadditionals.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    solution.h \
    mathadditionals/mathadditionals.h \
    qcustomplot.h

FORMS    += mainwindow.ui
