TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        comprobacion.cpp \
        main.cpp \
        piezas.cpp \
        colisiones.cpp \
        rotar.cpp \
        tablero.cpp

HEADERS += \
        comprobacion.h \
        piezas.h \
        colisiones.h \
        rotar.h \
        tablero.h
