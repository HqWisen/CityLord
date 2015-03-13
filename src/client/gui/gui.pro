TARGET = ../citylordgui
QT += widgets core gui
TEMPLATE = app

SOURCES += main.cpp\
    login.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    createaccount.cpp \
    defaultwidget.cpp \
    creategame.cpp \
    clientmanager.cpp \
    joingame.cpp \
    citylordview.cpp \
    ingame.cpp

HEADERS  += \
    login.h \
    mainmenu.h \
    mainwindow.h \
    createaccount.h \
    defaultwidget.h \
    creategame.h \
    clientmanager.h \
    joingame.h \
    citylordview.h \
    ingame.h


FORMS    += \
    login.ui \
    mainmenu.ui \
    mainwindow.ui \
    createaccount.ui \
    creategame.ui \
    joingame.ui \
    ingame.ui

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Wno-write-strings

DESTDIR = ../../../bin

LIBS += $$DESTDIR/socket.a $$DESTDIR/models.a $$DESTDIR/server.a

OBJECTS_DIR = $$DESTDIR/gui/
MOC_DIR = $$DESTDIR/gui/.moc
RCC_DIR = $$DESTDIR/gui/.rcc
UI_DIR = $$DESTDIR/gui/.ui
