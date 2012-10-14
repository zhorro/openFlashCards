#-------------------------------------------------
#
# Project created by QtCreator 2012-09-02T19:07:26
#
#-------------------------------------------------

QT       += core gui network webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Importer
TEMPLATE = app


SOURCES += \
    wordsbuilder.cpp \
    urldownloader.cpp \
    soundUrlExtractor.cpp \
    picturesdownloader.cpp \
    main.cpp \
    importerwindow.cpp

HEADERS  += \
    wordsbuilder.h \
    urldownloader.h \
    soundUrlExtractor.h \
    picturesdownloader.h \
    importerwindow.h

FORMS    += importerwindow.ui
