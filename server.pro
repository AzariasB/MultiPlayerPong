#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T15:06:49
#
#-------------------------------------------------

include(common.pro)

DEFINES += "SERVER"


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
