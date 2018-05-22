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
 * File:   CreditsState.cpp
 * Author: azarias
 *
 * Created on 17/5/2018
 */
#include "CreditsState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/StateMachine.hpp"


namespace mp {

CreditsState::CreditsState():
    mMenu()
{
    mMenu.addCenteredLabel("Credits", SF_ARENA_WIDTH  / 2.f, 100, 40);

    float he = 150;

    he += mMenu.addLabel("- Programming : Azarias Boutin", 10, he)->getLocalBounds().height;
    he += mMenu.addLabel("- Drawing : Azarias Boutin", 10, he)->getLocalBounds().height;
    he += mMenu.addLabel("- Using Keney sounds (www.kenney.nl)", 10, he)->getLocalBounds().height;
    he += mMenu.addLabel("- Font 'Whatever it takes' (brittneymurphydesign.com)", 10, he)->getLocalBounds().height;
    he += mMenu.addLabel("- SFML 2.5.0 (sfml-dev.org)", 10, he)->getLocalBounds().height;
    he += mMenu.addLabel("- Box2D 2.3.1 (box2d.org)", 10, he)->getLocalBounds().height;
    he += mMenu.addLabel("- Qt 5.10.1 (qt.io)", 10, he)->getLocalBounds().height;

    Button &btn = mMenu.addButton("Menu", SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT - 50, Assets::Icons::Exitleft);
    btn.setWidth(btn.getWidth() + 10);
    pr::connect(btn.clickedEvent, &CreditsState::menu, this);
}


void CreditsState::handleEvent(const sf::Event &ev)
{
    mMenu.handleEvent(ev);
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
        menu();
}

void CreditsState::update(const sf::Time &elapsed)
{
    mMenu.update(elapsed);
}

void CreditsState::draw(Renderer &renderer) const
{
    mMenu.draw(renderer);
}

void CreditsState::menu()
{
    pr::stateMachine().goToState(cc::MENU, TransitionData::GO_RIGHT);
}

}
