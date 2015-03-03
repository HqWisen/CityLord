TARGET = ../citylordgui
QT += widgets core gui
TEMPLATE = app

SOURCES += main.cpp\
    login.cpp \
    mainmenu.cpp \
    inplay.cpp \
    mainwindow.cpp \
    widgetmanager.cpp \
    createaccount.cpp \
    defaultwidget.cpp

HEADERS  += \
    login.h \
    mainmenu.h \
    inplay.h \
    mainwindow.h \
    widgetmanager.h \
    createaccount.h \
    defaultwidget.h


FORMS    += \
    login.ui \
    mainmenu.ui \
    inplay.ui \
    mainwindow.ui \
    createaccount.ui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

DESTDIR = ../../../bin

LIBS += 

OBJECTS_DIR = $$DESTDIR/gui/
MOC_DIR = $$DESTDIR/gui/.moc
RCC_DIR = $$DESTDIR/gui/.rcc
UI_DIR = $$DESTDIR/gui/.ui
