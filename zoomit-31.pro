TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    eight-puzzle-solvercpp.cpp

QMAKE_CXXFLAGS += -std=c++0x -O3

LIBS += -lncurses

HEADERS += \
    eight-puzzle-solver.h
