/*
 * The MIT License
 *
 * Copyright 2017 azarias.
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
 * File:   PauseState.cpp
 * Author: azarias
 *
 * Created on 7/5/2018
 */
#include "PauseState.hpp"
#include "PlaySoloState.hpp"
#include "OptionState.hpp"
#include "MenuState.hpp"

#include "src/common/Game.hpp"
#include "src/common/Config.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/Translator.hpp"
#include "src/client/StateMachine.hpp"

#include <iostream>

namespace mp {

PauseState::PauseState():
    m_menu()
{
    m_menu.addCenteredLabel("Pause", SF_CENTER_X, 50, 100);

    float startY = 250.f;

    Button &resume = m_menu.addButton("resume", SF_CENTER_X, startY, Assets::IconAtlas::rightIcon);
    startY += resume.getHeight() + 10.f;

    Button &restart = m_menu.addButton("restart", SF_CENTER_X, startY, Assets::IconAtlas::returnIcon);
    startY += restart.getHeight() + 10.f;

    Button &options = m_menu.addButton("options", SF_CENTER_X , startY, Assets::IconAtlas::gearIcon);
    startY += options.getHeight() + 10.f;

    Button &menuBtn = m_menu.addButton("menu", SF_CENTER_X, startY, Assets::IconAtlas::exitLeftIcon);
    startY += menuBtn.getHeight() + 10.f;

    m_menu.normalizeButtons(10);

    resume.clickedSignal.add([](){
        pr::stateMachine().fadeTo<PlaySoloState>();
    });
    options.clickedSignal.add([](){
        pr::stateMachine().slideTo<OptionState>(cc::SLIDE_DIRECTION::SLIDE_RIGHT);
    });
    menuBtn.clickedSignal.add([](){
        pr::stateMachine().slideTo<MenuState>(cc::SLIDE_DIRECTION::SLIDE_DOWN);
    });
    restart.clickedSignal.add([](){
        pr::game().reset();
        pr::stateMachine().fadeTo<PlaySoloState>();
    });

    pr::translator().translationChangedSignal.add([this](){
        m_menu.normalizeButtons(10);
    });
}

PauseState::~PauseState()
{
}


void PauseState::render(Renderer &renderer) const
{
    renderer.render(pr::stateMachine().get<PlaySoloState>())
            .render(m_menu);
}

void PauseState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void PauseState::handleEvent(const sf::Event &ev)
{
    m_menu.handleEvent(ev);
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
        pr::stateMachine().fadeTo<PlaySoloState>();
}


}
