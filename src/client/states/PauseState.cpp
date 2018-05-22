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
#include "src/common/Config.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/StateMachine.hpp"

namespace mp {

PauseState::PauseState():
    m_menu()
{
    m_menu.addCenteredLabel("Pause", SF_ARENA_WIDTH / 2.f, 50, 100);

    const Button &resume = *m_menu.addButton("Resume", SF_ARENA_WIDTH / 2.f , 250);
    pr::connect(resume.clickedEvent, &PauseState::resume, this);

    const Button &options = *m_menu.addButton("Options", SF_ARENA_WIDTH / 2.f , 300);
    pr::connect(options.clickedEvent, &StateMachine::goToState, &pr::stateMachine(), std::make_pair((int)cc::OPTIONS, TransitionData::GO_RIGHT));

    const Button &menuBtn = *m_menu.addButton("Menu", SF_ARENA_WIDTH / 2.f, 350);
    pr::connect(menuBtn.clickedEvent, &StateMachine::goToState, &pr::stateMachine(), std::make_pair((int)cc::MENU, TransitionData::GO_DOWN));

    m_menu.normalizeButtons();
}


void PauseState::draw(Renderer &renderer) const
{
    pr::stateMachine().getStateAt(cc::PLAY_SOLO).draw(renderer);
    m_menu.draw(renderer);
}

void PauseState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void PauseState::handleEvent(const sf::Event &ev)
{
    m_menu.handleEvent(ev);
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
        resume();
}

void PauseState::resume()
{
    pr::stateMachine().setCurrentState(cc::PLAY_SOLO);
}


}
