#-------------------------------------------------
#
# Project created by QtCreator 2012-09-02T19:07:26
#
#-------------------------------------------------

QT       += core gui network webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Importer
TEMPLATE = app


SOURCES += main.cpp\
        importerwindow.cpp \
    wordsbuilder.cpp \
    picturesdownloader.cpp

HEADERS  += importerwindow.h \
    wordsbuilder.h \
    picturesdownloader.h

FORMS    += importerwindow.ui
