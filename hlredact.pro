TARGET = hlredact
INCLUDEPATH += src libhltas/src
CONFIG += c++14
QT += widgets

HEADERS += \
    libhltas/src/hltas.hpp \
    src/common.hpp \
    src/framemodel.hpp \
    src/frameview.hpp \
    src/ftdelegate.hpp \
    src/mainwindow.hpp \
    src/numrepdelegate.hpp \
    src/strafedelegate.hpp \
    src/toggledelegate.hpp \
    src/yawdelegate.hpp \

SOURCES += \
    libhltas/src/hltas.cpp \
    src/framemodel.cpp \
    src/frameview.cpp \
    src/ftdelegate.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/numrepdelegate.cpp \
    src/strafedelegate.cpp \
    src/toggledelegate.cpp \
    src/yawdelegate.cpp \