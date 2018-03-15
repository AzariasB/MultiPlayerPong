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
win32:LIBS += -LC:\SFML-2.4.2\lib  -lsfml-audio-s-d -lsfml-network-s-d -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d \
            -lws2_32 -lwinmm -ljpeg -lfreetype -lopengl32 -lgdi32 -lvorbisfile -lvorbisenc -lvorbis -lflac -lopenal32 -logg
unix:INCLUDEPATH += /usr/local/include
unix:LIBS +=  -L/usr/local/lib -lsfml-audio -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system

LIBS += ../../lib/libBox2D.a

DEFINES += "CLIENT"

#Change config depending on the build configuration
CONFIG(debug, debug|release) {
        TARGET = pong
        DESTDIR = build/client
        OBJECTS_DIR = build/client/.obj
        MOC_DIR = build/client/.moc
        RCC_DIR = build/client/.rcc
} else {
        TARGET = pong
        DESTDIR = build/client
        OBJECTS_DIR = build/client/.obj
        MOC_DIR = build/client/.moc
        RCC_DIR = build/client/.rcc
}

include(src/client/client.pro)

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
