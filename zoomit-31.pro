TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    eight-puzzle-solver.cpp

QMAKE_CXXFLAGS += -std=c++0x -O3

LIBS += -lncurses -lpthread

HEADERS += \
    eight-puzzle-solver.h
