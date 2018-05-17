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
    m_menu.addCenteredLabel("Pause", SF_ARENA_WIDTH / 2.f, 50, 50);

    Button &resume = *m_menu.addCenteredButton("Resume", SF_ARENA_WIDTH / 2, 150);
    pr::connect(resume.clickedEvent, &PauseState::resume, this);

    Button &menuBtn = *m_menu.addCenteredButton("Menu", SF_ARENA_WIDTH / 2.f, 300);
    pr::connect(menuBtn.clickedEvent, &PauseState::menu, this);
}


void PauseState::draw(Renderer &renderer) const
{
    m_menu.draw(renderer);
}

void PauseState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void PauseState::handleEvent(const sf::Event &ev)
{
    m_menu.handleEvent(ev);
}

void PauseState::onEnter(BaseStateData *data)
{

}

void PauseState::menu()
{

}

void PauseState::resume()
{
    //pr::stateMachine().goToState();
}

}
