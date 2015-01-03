TARGET = hlredact
INCLUDEPATH += src
CONFIG += c++14
QT += widgets

HEADERS += \
    src/common.hpp \
    src/framemodel.hpp \
    src/frameview.hpp \
    src/ftdelegate.hpp \
    src/hltas.hpp \
    src/mainwindow.hpp \
    src/numrepdelegate.hpp \
    src/strafedelegate.hpp \
    src/toggledelegate.hpp \
    src/yawdelegate.hpp \

SOURCES += \
    src/framemodel.cpp \
    src/ftdelegate.cpp \
    src/hltas.cpp \
    src/main.cpp \
    src/frameview.cpp \
    src/mainwindow.cpp \
    src/numrepdelegate.cpp \
    src/strafedelegate.cpp \
    src/toggledelegate.cpp \
    src/yawdelegate.cpp \
