/*
 * The MIT License
 *
 * Copyright 2017-2019 azarias.
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

    m_musicButton = &m_menu.addButton("toggle_music", 3 * SF_ARENA_WIDTH / 4.f, startY, Assets::IconAtlas::musicOnIcon);
    startY += m_muteButton->getHeight() + 10;

    Button &keyBindingButton = m_menu.addButton("key_bindings", SF_ARENA_WIDTH/4.f , startY, Assets::IconAtlas::wrenchIcon);

    m_screenButton = &m_menu.addButton("fullscreen", 3 * SF_ARENA_WIDTH / 4.F, startY, Assets::IconAtlas::largerIcon);
    startY += m_screenButton->getHeight() + 50.f;

    startY += m_menu.addCenteredLabel("language", SF_CENTER_X, startY, 70)->height() + 50;

    float xPos = SF_ARENA_WIDTH / 4.f;
    float currentY = startY;
    int idx = 0;
    for(const auto &lang: Assets::I18N::translations){
        auto &btn = m_menu.addButton(lang.second.name, xPos, currentY);
        m_langButtons[lang.first] = &btn;
        btn.setAlignment(Button::Alignment::TopLeft);
        currentY += btn.getHeight() + 10;
        btn.clickedSignal.add([this, lang](){
            pr::translator().setCurrentTranslation(lang.first);
            updateLangButtonsIcon();
        });
        idx++;
        if(idx%3 == 0){
            xPos += SF_ARENA_WIDTH / 2.f;
            currentY = startY;
        }
    }
    updateLangButtonsIcon();

    Button& backButton = m_menu.addButton("menu", SF_ARENA_WIDTH/4.f , SF_ARENA_HEIGHT - 6, Assets::IconAtlas::exitLeftIcon);

    Button &playButton = m_menu.addButton("play", SF_ARENA_WIDTH * 3 / 4.f, SF_ARENA_HEIGHT - 6, Assets::IconAtlas::rightIcon);

    m_menu.normalizeButtons();

    backButton.setOrigin(backButton.getWidth() / 2.f, backButton.getHeight());
    playButton.setOrigin(playButton.getWidth() / 2.f, playButton.getHeight());
    pr::translator().translationChangedSignal.add([&](){
        m_menu.normalizeButtons();
        backButton.setOrigin(backButton.getWidth() / 2.f, backButton.getHeight());
        playButton.setOrigin(playButton.getWidth() / 2.f, playButton.getHeight());
    });

    keyBindingButton.clickedSignal.add([](){ pr::stateMachine().slideTo(cc::KEY_BINDINGS, SlideData::GO_RIGHT); });
    backButton.clickedSignal.add([](){pr::stateMachine().slideTo(cc::MENU, SlideData::GO_LEFT);});
    playButton.clickedSignal.add([](){
        pr::stateMachine().getStateAt(cc::PLAY_SOLO).onBeforeEnter();
        pr::stateMachine().slideTo(cc::PAUSE, SlideData::GO_RIGHT);
    });
    m_muteButton->clickedSignal.add([this](){toggleSound();});
    m_screenButton->clickedSignal.add([this](){toggleFullScreen();});
    m_musicButton->clickedSignal.add([this](){this->toggleMusic();});
}

void OptionState::updateLangButtonsIcon()
{
    for(auto &btn : m_langButtons){
        if(btn.first == pr::translator().currentTranslation()){
            btn.second->setIcon(Assets::IconAtlas::checkmarkIcon);
        } else {
            btn.second->removeIcon();
        }
    }
}

void OptionState::toggleMusic()
{
    musicSignal.trigger();
    m_musicButton->setIconTextureRect(getCurrentMusicRect());
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

const sf::IntRect &OptionState::getCurrentMusicRect() const
{
    return pr::soundEngine().isMusicStoped() ? Assets::IconAtlas::musicOffIcon.bounds : Assets::IconAtlas::musicOnIcon.bounds;
}

const sf::IntRect &OptionState::getCurrentSoundRect() const
{
    return pr::soundEngine().isSoundMuted() ? Assets::IconAtlas::audioOffIcon.bounds : Assets::IconAtlas::audioOnIcon.bounds;
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
        pr::stateMachine().slideTo(cc::MENU, SlideData::GO_LEFT);
    }else{
        m_menu.handleEvent(ev);
    }
}

}
