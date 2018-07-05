include(states/states.pro)
include(particles/particles.pro)
include(widgets/widgets.pro)

SOURCES +=\
    $$PWD/ClientApp.cpp \
    $$PWD/Renderer.cpp \
    $$PWD/ResourcesManager.cpp \
    $$PWD/SoundEngine.cpp \
    $$PWD/StateMachine.cpp \
    $$PWD/KeyBinding.cpp \
    $$PWD/Animation.cpp \
    $$PWD/Provider.cpp \
    $$PWD/ColorTweening.cpp \
    $$PWD/ClientConf.cpp \
    $$PWD/Assets.cpp \
    $$PWD/Translator.cpp

HEADERS +=\
    $$PWD/ClientApp.hpp \
    $$PWD/Renderer.hpp \
    $$PWD/ResourcesManager.hpp \
    $$PWD/SoundEngine.hpp \
    $$PWD/StateMachine.hpp \
    $$PWD/State.hpp \
    $$PWD/KeyBinding.hpp \
    $$PWD/Animation.hpp \
    $$PWD/Provider.hpp \
    $$PWD/State.hpp \
    $$PWD/ClientConf.hpp \
    $$PWD/ColorTweening.hpp \
    $$PWD/Assets.hpp \
    $$PWD/Renderable.hpp \
    $$PWD/Translator.hpp
