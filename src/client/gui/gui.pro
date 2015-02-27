TARGET = ../citylordgui

SOURCES += \
    main.cpp \
    LoginWindow.cpp

HEADERS += \
    LoginWindow.hpp

QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic

DESTDIR = ../../../bin

LIBS += 

OBJECTS_DIR = $$DESTDIR/gui/
MOC_DIR = $$DESTDIR/gui/.moc
RCC_DIR = $$DESTDIR/gui/.rcc
UI_DIR = $$DESTDIR/gui/.ui
