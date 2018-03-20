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
 * File:   Optionstate.cpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#include <qglobal.h>
#include "OptionState.hpp"
#include "KeyBindingState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/StateMachine.hpp"
#include "src/client/SoundEngine.hpp"

OptionState::OptionState():
m_menu()
{
    sf::Text &label =  *m_menu.addLabel("Options",SF_ARENA_WIDTH/2, 0);
	label.setPosition(label.getPosition().x - label.getGlobalBounds().width / 2.f, label.getPosition().y);

	int startY = 50;
	Button &muteButton = *m_menu.addButton("Toggle sound", 0, startY);

    m_soundSprite = m_menu.addSprite("icons", sf::Vector2f(SF_ARENA_WIDTH - 50, 0), getCurrentSoundRect()).get();
	m_soundSprite->setPosition(m_soundSprite->getPosition().x, startY);
	m_soundSprite->scale(4,4);
    pr::connect(muteButton.clickedEvent, &OptionState::toggleSound, this);


    sf::Uint64 keyBindingClicked = m_menu.addButton("Key bindings", 0, startY + muteButton.getHeight())->clickedEvent;
    pr::connect(keyBindingClicked , &StateMachine::goToState , &pr::stateMachine() ,  std::make_pair((int) cc::KEY_BINDINGS, TransitionData::GO_RIGHT) );

    sf::Uint64 backClicked = m_menu.addButton("Menu", 0, SF_ARENA_HEIGHT - 50)->clickedEvent;
    pr::connect(backClicked, &StateMachine::goToState,  &pr::stateMachine() , std::make_pair((int)cc::MENU, TransitionData::GO_LEFT) );
}

void OptionState::toggleSound()
{

    pr::soundEngine().isMuted() ? pr::soundEngine().unmute() :
                                          pr::soundEngine().mute();
	m_soundSprite->setTextureRect(getCurrentSoundRect());
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
	renderer.render(m_menu);
}

void OptionState::update(const sf::Time &elapsed)
{
	Q_UNUSED(elapsed);
}

void OptionState::handleEvent(const sf::Event &ev)
{
	if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::stateMachine().setCurrentState((int)cc::MENU);
	}else{
		m_menu.handleEvent(ev);
	}
}

void OptionState::onEnter(BaseStateData *data)
{
	Q_UNUSED(data);
}

void OptionState::onLeave()
{

}
