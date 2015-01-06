TARGET = hlredact
INCLUDEPATH += src libhltas/src
CONFIG += c++14
QT += widgets
LIBS += -lboost_system -lboost_thread

HEADERS += \
    libhltas/src/hltas.hpp \
    src/autofdelegate.hpp \
    src/common.hpp \
    src/framemodel.hpp \
    src/frameview.hpp \
    src/ftdelegate.hpp \
    src/mainwindow.hpp \
    src/numrepdelegate.hpp \
    src/propswindow.hpp \
    src/strafedelegate.hpp \
    src/toggledelegate.hpp \
    src/uintvalidator.hpp \
    src/yawdelegate.hpp \

SOURCES += \
    libhltas/src/hltas.cpp \
    src/autofdelegate.cpp \
    src/framemodel.cpp \
    src/frameview.cpp \
    src/ftdelegate.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/numrepdelegate.cpp \
    src/propswindow.cpp \
    src/strafedelegate.cpp \
    src/toggledelegate.cpp \
    src/uintvalidator.cpp \
    src/yawdelegate.cpp \
