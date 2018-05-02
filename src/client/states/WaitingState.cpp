/* * The MIT License
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
 * File:   WaitingState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */


#include <SFML/System/Thread.hpp>
#include <SFML/Network/IpAddress.hpp>

#include "src/client/ClientApp.hpp"
#include "src/client/ClientConf.hpp"
#include "WaitingState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/widgets/Dialog.hpp"


namespace mp {

WaitingState::~WaitingState()
{
}


WaitingState::WaitingState() :
    State(),
    m_menu(),
    m_content(*m_menu.addCenteredLabel("Connecting...",SF_ARENA_WIDTH/2.f, SF_ARENA_HEIGHT/2.f))
{
    Button &btn =  *m_menu.addCenteredButton("Cancel", SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT * 3 / 4.f);
    pr::connect(btn.clickedEvent, &WaitingState::cancelClicked, this);
}


void WaitingState::draw(Renderer& renderer) const
{
    m_menu.draw(renderer);
}

void WaitingState::handleEvent(const sf::Event& ev)
{
    m_menu.handleEvent(ev);
}


void WaitingState::cancelClicked()
{
    pr::socket().disconnect();
    pr::stateMachine().goToState(cc::MENU, TransitionData::GO_RIGHT);
}

void WaitingState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);

    //Blinking point
    bool startGame = false;
    sf::Packet rcvPacket;
    sf::Socket::Status rcvStatus = pr::socket().receive(rcvPacket);
    sf::String text = c_state == PENDING ? "Connecting..." :
                                           c_state == CONNECTED ? "Waiting for player ..." : "Disconnected :(";


    if(rcvStatus == sf::Socket::Done){
        if(c_state == PENDING){
            c_state = CONNECTED;
            int pNumber;
            rcvPacket >> pNumber;
            ClientApp::getInstance().setPNumber(pNumber);
        }else if(c_state == CONNECTED){
            startGame = true;
        }
    }else if(rcvStatus == sf::Socket::Disconnected){
        c_state = DISCONNECTED;
    }

    if (startGame)
        pr::stateMachine().goToState(cc::PLAY_MULTIPLAYER, TransitionData::GO_LEFT);

}

void WaitingState::onEnter(BaseStateData *data)
{
    c_state = CONNECTION_STATE::PENDING;

    StateData<std::string> *ipData = 0;
    if(!(ipData = static_cast<StateData<std::string>*>(data)))return;

    sf::IpAddress serverAddr(ipData->data());

    pr::socket().setBlocking(true);
    sf::Socket::Status status = pr::socket().connect(serverAddr, DEFAULT_PORT);
    pr::socket().setBlocking(false);
    if (status != sf::Socket::Done) {
        pr::dialogManager().message("Error","Failed to connect to the server");
        pr::stateMachine().goToState(cc::MENU, TransitionData::GO_LEFT);
    } else {
        m_content.setString("Waiting for player...");
    }
}

}

