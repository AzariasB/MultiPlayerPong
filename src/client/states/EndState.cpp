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


EndState::EndState() :
    m_messageDialog(Dialog::message( "",""))
{
    m_messageDialog->setOkButtonTitle("Menu");

    pr::connect(
                m_messageDialog->okEvent,
                &EndState::goToMenu,
                this
                );

    pr::connect(
                m_messageDialog->cancelEvent,
                &EndState::goToMenu,
                this
                );

    m_messageDialog->show();
}

EndState::~EndState()
{
    delete m_messageDialog;
}


void EndState::goToMenu()
{
    pr::stateMachine().goToState(cc::MENU, TransitionData::GO_RIGHT);
}

void EndState::draw(Renderer& renderer) const
{
    m_messageDialog->draw(renderer);
}


void EndState::handleEvent(const sf::Event& ev)
{
    //When escape pressed, go to menu
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        goToMenu();
    }else{
        m_messageDialog->handleEvent(ev);
    }
}

void EndState::onEnter(BaseStateData *data)
{
    Q_UNUSED(data);
    m_messageDialog->setMessage("Your score :" + std::to_string(pr::player().getScore()));
    m_messageDialog->setTitle(ClientApp::getInstance().isWinner() ? "You won ! " : "You lost");
    pr::game().reset();
}

void EndState::onBeforeLeaving()
{
    //Disconnect the sockets and "null" them
    pr::socket().disconnect();
    m_messageDialog->hide();
}

void EndState::update(const sf::Time &elapsed)
{
    m_messageDialog->update(elapsed);
}
