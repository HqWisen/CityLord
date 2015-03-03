TARGET = ../citylordgui
QT += widgets core gui
TEMPLATE = app

SOURCES += main.cpp\
    login.cpp \
    mainmenu.cpp \
    inplay.cpp \
    mainwindow.cpp \
    createaccount.cpp \
    defaultwidget.cpp \
    creategame.cpp \
<<<<<<< HEAD
    clientmanager.cpp
=======
    joingame.cpp
>>>>>>> 8947808f1fbea653d2706b8cb98785f6eaf305c8

HEADERS  += \
    login.h \
    mainmenu.h \
    inplay.h \
    mainwindow.h \
    createaccount.h \
    defaultwidget.h \
    creategame.h \
<<<<<<< HEAD
    clientmanager.h
=======
    joingame.h
>>>>>>> 8947808f1fbea653d2706b8cb98785f6eaf305c8


FORMS    += \
    login.ui \
    mainmenu.ui \
    inplay.ui \
    mainwindow.ui \
    createaccount.ui \
    creategame.ui \
    joingame.ui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

DESTDIR = ../../../bin

LIBS += 

OBJECTS_DIR = $$DESTDIR/gui/
MOC_DIR = $$DESTDIR/gui/.moc
RCC_DIR = $$DESTDIR/gui/.rcc
UI_DIR = $$DESTDIR/gui/.ui
