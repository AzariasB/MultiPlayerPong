#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T15:06:49
#
#-------------------------------------------------

QT              -= gui
CONFIG          += c++14
QMAKE_CXXFLAGS  += -std=c++14

win32:INCLUDEPATH += C:\SFML-2.5.0\include C:\Box2D\include
win32:DEFINES += "SFML_STATIC"
win32:LIBS += -LC:\SFML-2.5.0\lib ..\..\lib\Box2D.lib

unix:INCLUDEPATH += /usr/local/include
unix:LIBS +=  -L/usr/local/lib -lsfml-network -lsfml-system
unix:LIBS += ../../lib/libBox2D.a

SOURCES +=\
    src/main.cpp \
    src/common/Application.cpp \
    src/common/Ball.cpp \
    src/common/Paddle.cpp \
    src/common/EventManager.cpp \
    src/common/Game.cpp \
    src/common/Player.cpp \
    src/common/Powerup.cpp \
    src/common/Wall.cpp \
    src/common/ContactListener.cpp \
    src/common/PhysicObject.cpp \
    src/common/Math.cpp

HEADERS +=\
    src/common/Application.hpp \
    src/common/Ball.hpp \
    src/common/Paddle.hpp \
    src/common/EventManager.hpp \
    src/common/Game.hpp \
    src/common/Math.hpp \
    src/common/Player.hpp \
    src/common/VectorsUtils.hpp \
    src/common/Config.hpp \
    src/common/Powerup.hpp \
    src/lib/twin.hpp \
    src/common/Wall.hpp \
    src/common/ContactListener.hpp \
    src/common/PhysicObject.hpp
