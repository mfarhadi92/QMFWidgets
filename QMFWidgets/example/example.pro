QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include ( $$PWD/../QMFWidgets.pri )
TARGET = QMFExampleWidget
TEMPLATE = app
CONFIG += c++11


FORMS += \
    $$PWD/qmfexamplewidget.ui

HEADERS += \
    $$PWD/qmfexamplewidget.h

SOURCES += \
    $$PWD/qmfexamplewidget.cpp \
    $$PWD/main.cpp

