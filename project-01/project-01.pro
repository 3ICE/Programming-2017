TEMPLATE = app
QT -= core gui
CONFIG -= qt
CONFIG += console
SOURCES = main.cpp \
    product.cpp \
    splitter.cpp \
    data.cpp

DISTFILES += \
    products.txt \
    bad_1.txt \
    bad_2.txt \
    bad_3.txt \
    bad_4.txt \
    bad_5.txt \
    bad_6.txt \
    bad_7.txt \
    bad_8.txt \
    products--cheapest-milk-sub-order-alphabetical-too.txt \
    products--same-more-than-once.txt

HEADERS += \
    product.hh \
    splitter.hh \
    data.hh