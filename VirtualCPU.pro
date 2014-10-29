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
    cpu.cpp

HEADERS  += virtualcpu.h \
    opcodes.h \
    memory.h \
    cpu.h \
    mips.h

FORMS    += virtualcpu.ui
