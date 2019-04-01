#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T15:06:49
#
#-------------------------------------------------

include(common.pro)

unix:LIBS += -lsfml-network -lsfml-system
win32:LIBS += -lsfml-network-s -lsfml-system-s -lws2_32 -lwinmm

DEFINES += "SERVER"


#Change config depending on the build configuration
TARGET = server
DESTDIR = build/server
OBJECTS_DIR = build/server/.obj
MOC_DIR = build/server/.moc
RCC_DIR = build/server/.rcc

include(src/server/server.pro)
