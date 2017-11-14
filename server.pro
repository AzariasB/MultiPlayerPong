#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T15:06:49
#
#-------------------------------------------------

QT              -= gui core
CONFIG          += c++14
QMAKE_CXXFLAGS  += -std=c++14

win32:LIBS += -LC:\SFML\lib -lsfml-network-s-d -lsfml-system-s-d -lws2_32 -lwinmm
else:LIBS += -lsfml-network -lsfml-system

DEFINES += "SERVER" "SFML_STATIC"

win32:INCLUDEPATH += C:\SFML\include


#Change config depending on the build configuration
CONFIG(debug, debug|release) {
        TARGET = pong
        DESTDIR = build/server
        OBJECTS_DIR = build/server/.obj
        MOC_DIR = build/server/.moc
        RCC_DIR = build/server/.rcc
} else {
        TARGET = pong
        DESTDIR = build/release
        OBJECTS_DIR = build/release/.obj
        MOC_DIR = build/release/.moc
        RCC_DIR = build/release/.rcc
}

include(src/server/server.pro)

SOURCES +=\
    src/main.cpp \
    src/Application.cpp \
    src/Ball.cpp \
    src/Paddle.cpp \
    src/EventManager.cpp \
    src/Game.cpp \
    src/Player.cpp

HEADERS +=\
    src/Application.hpp \
    src/Ball.hpp \
    src/Paddle.hpp \
    src/EventManager.hpp \
    src/Game.hpp \
    src/Math.hpp \
    src/Player.hpp \
    src/VectorsUtils.hpp \
    src/Config.hpp
