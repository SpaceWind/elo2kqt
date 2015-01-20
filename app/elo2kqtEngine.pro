#-------------------------------------------------
#
# Project created by QtCreator 2014-11-12T09:45:24
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = elo2kqtEngine
TEMPLATE = app

include(../src/graphicsEngine/engine.pri)
include(../src/components/components.pri)
include(../src/core/core.pri)
include(../src/entities/entities.pri)
include(../src/systems/systems.pri)

SOURCES += main.cpp \


FORMS    +=

RESOURCES += \
    images.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/defines_lib/bin/ -ldefinesLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/defines_lib/bin/ -ldefinesLibd
else:unix:!macx: LIBS += -L$$PWD/../libs/defines_lib/bin/ -ldefinesLib

INCLUDEPATH += $$PWD/../libs/defines_lib/headers
DEPENDPATH += $$PWD/../libs/defines_lib/bin/
