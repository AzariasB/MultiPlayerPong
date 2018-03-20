#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T15:06:49
#
#-------------------------------------------------

QT              -= gui
CONFIG          += c++14
QMAKE_CXXFLAGS  += -std=c++14

win32:INCLUDEPATH += C:\SFML-2.4.2\include C:\Box2D\include
win32:DEFINES += "SFML_STATIC"
win32:LIBS += -LC:\SFML-2.4.2\lib  -lsfml-network-s-d -lsfml-system-s-d \
            -lws2_32 -lwinmm

unix:INCLUDEPATH += /usr/local/include
unix:LIBS +=  -L/usr/local/lib -lsfml-network -lsfml-system ../../lib/libenet.a

LIBS += ../../lib/libBox2D.a

SOURCES +=\
    src/main.cpp \
    src/Application.cpp \
    src/Ball.cpp \
    src/Paddle.cpp \
    src/EventManager.cpp \
    src/Game.cpp \
    src/Player.cpp \
    src/Powerup.cpp \
    src/Wall.cpp \
    src/ContactListener.cpp \
    src/PhysicObject.cpp \
    src/Math.cpp

HEADERS +=\
    src/Application.hpp \
    src/Ball.hpp \
    src/Paddle.hpp \
    src/EventManager.hpp \
    src/Game.hpp \
    src/Math.hpp \
    src/Player.hpp \
    src/VectorsUtils.hpp \
    src/Config.hpp \
    src/Powerup.hpp \
    src/lib/twin.hpp \
    src/Wall.hpp \
    src/ContactListener.hpp \
    src/PhysicObject.hpp

DISTFILES +=\
    ka1.ttf \
    bounce.wav

RESOURCES += \
    resources.qrc
