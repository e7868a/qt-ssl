QT       += core network

QT       -= gui

TARGET = sslserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sslserver.cpp

HEADERS += \
    sslserver.h
