/*
 * The MIT License
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
 * File:   PlayState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:49
 */

#include <qglobal.h>
#include <SFML/Network/IpAddress.hpp>

#include "PlayMultiplayerState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientApp.hpp"

#include <iostream>

namespace mp {


PlayMultiplayerState::PlayMultiplayerState() :
    PlayState()
{
}

PlayMultiplayerState::~PlayMultiplayerState()
{
}

void PlayMultiplayerState::update(const sf::Time &elapsed)
{
    PlayState::update(elapsed);
    sf::Packet rcvPacket;
    if(pr::socket().receive(rcvPacket) == sf::Socket::Done){
        rcvPacket >> pr::game();
    }
}

int PlayMultiplayerState::playerNum()
{
    return m_pNumber;
}

void PlayMultiplayerState::onEnter(int pNumber)
{
    m_pNumber = pNumber;
}

void PlayMultiplayerState::handleEvent(const sf::Event& ev)
{
    if(!pr::stateMachine().currentIs<PlayMultiplayerState>()) return;

    PlayState::handleEvent(ev);
    sf::Event realEv = pr::game().input().toBaseEvent(ev, m_pNumber);
    if (realEv.type == sf::Event::KeyPressed || realEv.type == sf::Event::KeyReleased) {
        sf::Packet p;
        p << realEv.type << realEv.key.code;
        pr::socket().send(p);
    }
}

void PlayMultiplayerState::onBeforeLeaving()
{
}


}
