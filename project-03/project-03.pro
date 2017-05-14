TEMPLATE = app
QT -= core gui
CONFIG -= qt
CONFIG += console c++11
SOURCES = main.cpp \
    queue.cpp \
    test_stack.cpp \
    regexes.cpp

HEADERS += \
    queue.hh \
    stack.hh
