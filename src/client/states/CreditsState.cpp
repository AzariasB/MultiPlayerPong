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
#include "MenuState.hpp"
#include <Box2D/Common/b2Settings.h>

#include "src/client/Provider.hpp"
#include "src/client/StateMachine.hpp"


namespace mp {

CreditsState::CreditsState():
    mMenu()
{
    mMenu.addCenteredLabel("credits", SF_CENTER_X, 100, 70);

    const float leftPos = 20;
    float he = 180;

    he += mMenu.addLabel({"- ","programming"," : Azarias Boutin"}, leftPos, he)->height();
    he += mMenu.addLabel({"- ","drawing"," : Azarias Boutin"}, leftPos, he)->height();
    he += mMenu.addLabel({"- ","sounds","/", "icons"," : Kenney (www.kenney.nl)"}, leftPos, he)->height();
    he += mMenu.addLabel({"- ","font"," : 'Caveat brush regular' (Impallari Type)"}, leftPos, he)->height();
    he += mMenu.addLabel("- SFML " + sfmlVersion() + " (sfml-dev.org)", leftPos, he)->height();
    he += mMenu.addLabel("- Box2D " + box2dVersion() + " (box2d.org)", leftPos, he)->height();
    he += mMenu.addLabel("- Qt " + qtVersion() + " (qt.io)", leftPos, he)->height();
    he += mMenu.addLabel({"- ","music", " :  Preludes from Chris Zabriske"}, leftPos, he)->height();

    Button &btn = mMenu.addButton("menu", SF_CENTER_X, SF_ARENA_HEIGHT - 15, Assets::IconAtlas::exitLeftIcon);
    btn.setOrigin(btn.getWidth() / 2.f, btn.getHeight());
    btn.setWidth(btn.getWidth() + 10);
    btn.clickedSignal.add([this](){ menu(); });
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

std::string CreditsState::sfmlVersion() const
{
    return toVersion(SFML_VERSION_MAJOR, SFML_VERSION_MINOR, SFML_VERSION_PATCH);
}

std::string CreditsState::box2dVersion() const
{
    b2Version v = b2_version;
    return toVersion(v.major, v.minor, v.revision);
}

std::string CreditsState::qtVersion() const
{
    return QT_VERSION_STR;
}

std::string CreditsState::toVersion(int major, int minor, int patch) const
{
    return std::to_string(major) + "." +
            std::to_string(minor) + "." +
            std::to_string(patch) + ".";
}

void CreditsState::render(Renderer &renderer) const
{
    mMenu.render(renderer);
}

void CreditsState::menu()
{
    pr::stateMachine().slideTo<MenuState>(cc::SLIDE_DIRECTION::SLIDE_RIGHT);
}

}
