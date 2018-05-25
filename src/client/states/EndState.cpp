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
 * File:   EndState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:50
 */
#include "EndState.hpp"
#include "src/client/ClientApp.hpp"
#include "src/client/Provider.hpp"
#include "src/client/widgets/Dialog.hpp"
#include "src/client/ClientConf.hpp"

namespace mp {

EndState::EndState():
    m_menu(),
    m_content(*m_menu.addLabel("",0,0))
{
    m_menu.addCenteredLabel("Finished !", SF_ARENA_WIDTH/2.f, SF_ARENA_HEIGHT/4.f, 60);

    Button &btn = m_menu.addButton("Menu",SF_ARENA_WIDTH/2, 3*SF_ARENA_HEIGHT/4, Assets::IconAtlas::exitLeftIcon);
    pr::connect(btn.clickedEvent, &EndState::goToMenu, this);
}

EndState::~EndState()
{

}


void EndState::goToMenu()
{
    pr::stateMachine().goToState(cc::MENU, TransitionData::GO_RIGHT);
}

void EndState::draw(Renderer& renderer) const
{
    //m_messageDialog->draw(renderer);
    m_menu.draw(renderer);
}


void EndState::handleEvent(const sf::Event& ev)
{
    //When escape pressed, go to menu
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        goToMenu();
    }else{
        m_menu.handleEvent(ev);
    }
}

void EndState::onEnter(BaseStateData *data)
{
    m_content.setString(ClientApp::getInstance().isWinner() ? "You won !" : "You lost !");
    m_content.setOrigin(m_content.getLocalBounds().width/2.f, m_content.getLocalBounds().height / 2.f);
    m_content.setPosition(SF_ARENA_WIDTH/2.f, SF_ARENA_HEIGHT/2.f);

    pr::game().reset();
    pr::socket().disconnect();
}

void EndState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

}

