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
 * File:   PlayState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:49
 */

#include <qglobal.h>
#include <SFML/Network/IpAddress.hpp>

#include "PlayMultiplayerState.hpp"
#include "Provider.hpp"
#include "ClientApp.hpp"

PlayMultiplayerState::PlayMultiplayerState() :
    PlayState(),
    listeningThread(&PlayMultiplayerState::listenSocket, this)
{
    pr::connect(
                pr::game().bounceEvent,
                &PlayMultiplayerState::bounced,
                this
                ); //Subscribe to bounce event
}

PlayMultiplayerState::~PlayMultiplayerState()
{
}

void PlayMultiplayerState::bounced(int pNum, sf::Vector2f position)
{
    Q_UNUSED(pNum);
    pr::soundEngine().playSound(SoundEngine::BOUNCE);
    pr::particleGenerator().explode(position);//get position
    pr::renderer().shake();
}

void PlayMultiplayerState::handleEvent(const sf::Event& ev)
{
    PlayState::handleEvent(ev);
    sf::Event realEv = pr::keyBinding().toGameEvent(ev);
    if (realEv.type == sf::Event::KeyPressed || realEv.type == sf::Event::KeyReleased) {
        sf::Packet p;
        p << realEv.type << realEv.key.code;
        pr::socket().send(p);
    }
}

void PlayMultiplayerState::onEnter(BaseStateData *data)
{
    Q_UNUSED(data);
    listeningThread.launch();
}

void PlayMultiplayerState::onLeave()
{
    listeningThread.terminate();
}

void PlayMultiplayerState::listenSocket()
{
    while (1) {
        sf::Packet p;
        if(pr::socket().getRemoteAddress() == sf::IpAddress::None){
            std::cerr << "Socket is null \n";
            return;
        }
        sf::Socket::Status rcvStatus = pr::socket().receive(p);
        if (rcvStatus == sf::Socket::Done) {
            p >> pr::game();
        } else if (rcvStatus == sf::Socket::Disconnected) {
            //Send message to main thread
        }
    }
}
