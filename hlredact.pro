TARGET = hlredact
INCLUDEPATH += src libhltas/src
CONFIG += c++14
QT += widgets
LIBS += -lboost_system -lboost_thread

HEADERS += \
    libhltas/src/hltas.hpp \
    src/mainwindow.hpp \
    src/timelinescene.hpp \
    src/timelineview.hpp \

SOURCES += \
    libhltas/src/hltas.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/timelinescene.cpp \
    src/timelineview.cpp \
