TARGET = hlredact
INCLUDEPATH += src libhltas/src
CONFIG += c++14
QT += widgets
LIBS += -lboost_system -lboost_thread

HEADERS += \
    libhltas/src/hltas.hpp \
    src/mainwindow.hpp \

SOURCES += \
    libhltas/src/hltas.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
