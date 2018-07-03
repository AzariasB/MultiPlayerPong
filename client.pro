#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T15:06:49
#
#-------------------------------------------------

include(common.pro)
win32:LIBS += -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-network-s -lsfml-system-s \
            -lfreetype -lopengl32 -lgdi32 -lvorbisfile -lvorbisenc -lvorbis -lflac -lopenal32 -logg -lws2_32 -lwinmm

unix:LIBS +=  -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-network -lsfml-system
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

RESOURCES += resources.qrc
