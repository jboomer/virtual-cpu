#-------------------------------------------------
#
# Project created by QtCreator 2014-10-09T15:50:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VirtualCPU
TEMPLATE = app


SOURCES += main.cpp\
        virtualcpu.cpp \
    memory.cpp \
    mipsproc.cpp

HEADERS  += virtualcpu.h \
    memory.h \
    mipsproc.h \
    mipsopcodes.h

FORMS    += virtualcpu.ui
