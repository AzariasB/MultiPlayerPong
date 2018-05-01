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
#include "src/client/ClientConf.hpp"
#include "src/client/SoundEngine.hpp"
#include "src/client/StateMachine.hpp"

namespace mp {

OptionState::OptionState():
    m_menu()
{
    float startY = 50.f;
    startY += m_menu.addCenteredLabel("Options",SF_ARENA_WIDTH/2, 50)->getGlobalBounds().height + 20.f;

    m_muteButton = m_menu.addButton("Toggle sound", SF_ARENA_WIDTH/4.f, startY).get();
    sf::Sprite sound = sf::Sprite(pr::resourceManager().getTexture("sound_icons"), getCurrentSoundRect());
    m_muteButton->setIcon(sound);

    pr::connect(m_muteButton->clickedEvent, &OptionState::toggleSound, this);

    startY += m_muteButton->getHeight();
    const Button &keyBindingButton = *m_menu.addButton("Key bindings", SF_ARENA_WIDTH/4.f , startY);

    startY += keyBindingButton.getHeight() + 50.f;
    pr::connect(keyBindingButton.clickedEvent , &StateMachine::goToState , &pr::stateMachine() ,  std::make_pair((int) cc::KEY_BINDINGS, TransitionData::GO_RIGHT) );

    sf::Uint64 backClicked = m_menu.addCenteredButton("Menu", SF_ARENA_WIDTH/2.f , startY )->clickedEvent;
    pr::connect(backClicked, &StateMachine::goToState,  &pr::stateMachine() , std::make_pair((int)cc::MENU, TransitionData::GO_LEFT) );
}

void OptionState::toggleSound()
{
    pr::soundEngine().isMuted() ? pr::soundEngine().unmute() :
                                  pr::soundEngine().mute();

    sf::Sprite buttonSprite= m_muteButton->getIcon();
    buttonSprite.setTextureRect(getCurrentSoundRect());
    m_muteButton->setIcon(buttonSprite);
}

const sf::IntRect &OptionState::getCurrentSoundRect() const
{
    return pr::soundEngine().isMuted() ? m_withoutSoundRect : m_withSoundRect;
}

OptionState::~OptionState()
{

}

void OptionState::draw(Renderer &renderer) const
{
    m_menu.draw(renderer);
}

void OptionState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void OptionState::handleEvent(const sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::stateMachine().setCurrentState((int)cc::MENU);
    }else{
        m_menu.handleEvent(ev);
    }
}

}
