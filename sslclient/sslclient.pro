QT       += core network

QT       -= gui

TARGET = sslclient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    sslclient.cpp

HEADERS += \
    sslclient.h
