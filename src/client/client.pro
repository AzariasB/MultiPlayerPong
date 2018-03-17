include(states/states.pro)
include(particles/particles.pro)

SOURCES +=\
    $$PWD/Button.cpp \
    $$PWD/ClientApp.cpp \
    $$PWD/Renderer.cpp \
    $$PWD/ResourcesManager.cpp \
    $$PWD/SoundEngine.cpp \
    $$PWD/StateMachine.cpp \
    $$PWD/TextInput.cpp \
    $$PWD/Dialog.cpp \
    $$PWD/Menu.cpp \
    $$PWD/KeyBinding.cpp \
    $$PWD/Animation.cpp \
    $$PWD/Provider.cpp

HEADERS +=\
    $$PWD/Button.hpp \
    $$PWD/ClientApp.hpp \
    $$PWD/Renderer.hpp \
    $$PWD/ResourcesManager.hpp \
    $$PWD/SoundEngine.hpp \
    $$PWD/StateMachine.hpp \
    $$PWD/TextInput.hpp \
    $$PWD/State.hpp \
    $$PWD/Widget.hpp \
    $$PWD/Dialog.hpp \
    $$PWD/Menu.hpp \
    $$PWD/KeyBinding.hpp \
    $$PWD/Animation.hpp \
    $$PWD/Provider.hpp \
    State.hpp
