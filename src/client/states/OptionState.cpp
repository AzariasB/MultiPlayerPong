/*
 * The MIT License
 *
 * Copyright 2017-2018 azarias.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * File:   Optionstate.cpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#include <qglobal.h>
#include "src/common/Config.hpp"
#include "OptionState.hpp"
#include "KeyBindingState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/Assets.hpp"
#include "src/client/ClientApp.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/SoundEngine.hpp"
#include "src/client/StateMachine.hpp"

namespace mp {

OptionState::OptionState():
    m_menu()
{
    float startY = 50.f;
    startY += m_menu.addCenteredLabel("Options",SF_CENTER_X, 50, 70)->height()+ 50.f;

    m_muteButton = &m_menu.addButton("toggle_sound", SF_ARENA_WIDTH / 4.f, startY, Assets::IconAtlas::audioOnIcon);

    startY += m_muteButton->getHeight() + 10;

    Button &keyBindingButton = m_menu.addButton("key_bindings", SF_ARENA_WIDTH/4.f , startY, Assets::IconAtlas::wrenchIcon);
    startY += keyBindingButton.getHeight() + 10;

    m_screenButton = &m_menu.addButton("fullscreen", SF_ARENA_WIDTH / 4.F, startY, Assets::IconAtlas::largerIcon);
    startY += m_screenButton->getHeight() + 50.f;

    startY += m_menu.addCenteredLabel("language", SF_CENTER_X, startY, 70)->height() + 50;

    for(const auto &lang: Assets::I18N::translations){
        auto &btn = m_menu.addButton(lang.second.name, SF_ARENA_WIDTH / 4.f, startY);
        startY += btn.getHeight();
        btn.clickedSignal.add([lang](){
            pr::translator().setCurrentTranslation(lang.first);
        });
    }

    startY += 50;

    Button& backButton = m_menu.addButton("menu", SF_ARENA_WIDTH/4.f , startY, Assets::IconAtlas::exitLeftIcon);

    Button &playButton = m_menu.addButton("play", SF_ARENA_WIDTH * 3 / 4.f, startY, Assets::IconAtlas::rightIcon);

    m_menu.normalizeButtons();
    pr::translator().translationChangedSignal.add([this](){
        m_menu.normalizeButtons();
    });

    keyBindingButton.clickedSignal.add([](){ pr::stateMachine().goToState(cc::KEY_BINDINGS, TransitionData::GO_RIGHT); });
    backButton.clickedSignal.add([](){pr::stateMachine().goToState(cc::MENU, TransitionData::GO_LEFT);});
    playButton.clickedSignal.add([](){pr::stateMachine().goToState(cc::PAUSE, TransitionData::GO_RIGHT);});
    m_muteButton->clickedSignal.add([this](){toggleSound();});
    m_screenButton->clickedSignal.add([this](){toggleFullScreen();});
}

void OptionState::toggleSound()
{
    soundSignal.trigger();
    m_muteButton->setIconTextureRect(getCurrentSoundRect());
}

void OptionState::toggleFullScreen()
{
    fullScreenSignal.trigger();
    m_screenButton->setIconTextureRect(getCurrentScreenRect());
}

const sf::IntRect &OptionState::getCurrentSoundRect() const
{
    return pr::soundEngine().isMuted() ? Assets::IconAtlas::audioOffIcon.bounds : Assets::IconAtlas::audioOnIcon.bounds;
}

const sf::IntRect &OptionState::getCurrentScreenRect() const
{
    return ClientApp::getInstance().isFullScreen() ? Assets::IconAtlas::smallerIcon.bounds : Assets::IconAtlas::largerIcon.bounds;
}

OptionState::~OptionState()
{

}

void OptionState::render(Renderer &renderer) const
{
    m_menu.render(renderer);
}

void OptionState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void OptionState::handleEvent(const sf::Event &ev)
{
    if(pr::stateMachine().getCurrentStateIndex() != (int)cc::OPTIONS) return;

    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::stateMachine().goToState(cc::MENU, TransitionData::GO_LEFT);
    }else{
        m_menu.handleEvent(ev);
    }
}

}
