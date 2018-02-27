# Created at 2017-02-27 (TAI: 1898444597)
QT += widgets
HEADERS += inc/MMClient.h
HEADERS += inc/MMClientWindow.h
SOURCES += src/MMClient.cpp
SOURCES += src/MMClientWindow.cpp
SOURCES += src/main.cpp
INCLUDEPATH += /usr/local/boost_1_59_0
LIBS += "-L/usr/local/boost_1_59_0/stage/lib/"
TARGET = hssclient
