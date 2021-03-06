/* * The MIT License
 *
 * Copyright 2017-2019 azarias.
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

#include "MenuState.hpp"
#include "WaitingState.hpp"
#include "PlayMultiplayerState.hpp"

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
    m_content(*m_menu.addCenteredLabel("connecting", SF_CENTER_X, SF_CENTER_Y - 100)),
    m_loading(sf::Vector2f(SF_CENTER_X, SF_CENTER_Y), 300)
{
    m_menu.addButton("cancel", SF_CENTER_X, SF_ARENA_HEIGHT * 3 / 4.f, Assets::IconAtlas::crossIcon)
            .clickedSignal.add([this](){
                m_socket->disconnect();
                m_socket = {};
                pr::stateMachine().slideTo<MenuState>(cc::SLIDE_DIRECTION::SLIDE_RIGHT);
            });

    m_menu.normalizeButtons(10);
    pr::translator().translationChangedSignal.add([this](){
        m_menu.normalizeButtons(10);
    });
}


void WaitingState::render(Renderer& renderer) const
{
    renderer
            .render(m_menu)
            .render(m_loading);
}

void WaitingState::handleEvent(const sf::Event& ev)
{
    if(!pr::stateMachine().currentIs<WaitingState>())return;
    m_menu.handleEvent(ev);
}

void WaitingState::update(const sf::Time &elapsed)
{
    if(!pr::stateMachine().currentIs<WaitingState>())return;

    m_menu.update(elapsed);
    m_loading.update(elapsed);

    //Blinking point
    bool startGame = false;
    sf::Packet rcvPacket;
    sf::Socket::Status rcvStatus = m_socket->receive(rcvPacket);


    if(rcvStatus == sf::Socket::Done){
        if(c_state == PENDING){
            c_state = CONNECTED;
            rcvPacket >> m_pNumber;
        }else if(c_state == CONNECTED){
            startGame = true;
        }
    }else if(rcvStatus == sf::Socket::Disconnected){
        c_state = DISCONNECTED;
    }

    if (startGame){
        pr::game().setGameMode(GAME_MODE::STANDARD_MULTIPLAYER);
        pr::stateMachine().slideTo<PlayMultiplayerState>(cc::SLIDE_DIRECTION::SLIDE_LEFT, m_pNumber, m_socket);
    }

}

void WaitingState::onEnter(std::string &&data)
{
    m_pNumber = -1;
    c_state = CONNECTION_STATE::PENDING;
    m_loading.setState(Loading::LD_INACTIVE);

    m_socket = std::make_unique<sf::TcpSocket>();
    sf::IpAddress serverAddr(data);

    m_socket->setBlocking(true);
    sf::Socket::Status status = m_socket->connect(serverAddr, DEFAULT_PORT);
    m_socket->setBlocking(false);
    if (status != sf::Socket::Done) {
        DialogMessage& msg = pr::dialogManager().message("error","failed_connect");
        msg.okClickedSignal.add([&msg](){pr::dialogManager().hideDialog(msg.id());});
        pr::stateMachine().slideTo<MenuState>(cc::SLIDE_DIRECTION::SLIDE_LEFT);
    } else {
        m_content.setString("waiting_player");
        m_loading.setState(Loading::LD_ACTIVE);
    }
}

}

