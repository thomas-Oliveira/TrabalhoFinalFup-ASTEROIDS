TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    cenario.c \
    funcoes_gerais.c
LIBS += -lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    estruturas.h \
    cenario.h \
    funcoes_gerais.h

