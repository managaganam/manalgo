QT       += core

TARGET = manalgo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    squaretime.cpp \
    boids.cpp

HEADERS += \
    squaretime.h \
    utils.h \
    boids.h
