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
 * File:   Lobby.cpp
 * Author: azarias
 *
 * Created on 17 octobre 2017, 16:45
 */

#include "Lobby.hpp"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>

namespace mp {

//LobbyThread

LobbyThread::LobbyThread() :
    thread(&Lobby::start, &lobby)
{
}

LobbyThread::~LobbyThread()
{

}

//Lobby

Lobby::Lobby() :
    game(),
    listeningThread(&Lobby::listenSockets, this),
    m_nextPowerup(sf::seconds(3))
{
    game.setGameMode(GAME_MODE::STANDARD_MULTIPLAYER);
    game.hitPaddleSignal.add([this](std::size_t pNumber, b2Vec2 pos){
        if (pNumber == 1)
            game.getPlayer1().gainPoint();
        else if (pNumber == 2)
            game.getPlayer2().gainPoint();
    });

    game.lostSignal.add([this](int pLooser){
        bool p1Looser = pLooser == 1;
        game.getPlayer1().setIsWinner(!p1Looser);
        game.getPlayer2().setIsWinner(p1Looser);
    });

    game.countdownEndedSignal.add([this](){
        game.setGameState(GAMESTATE::PLAYING);
    });
}

Lobby::~Lobby()
{
}

void Lobby::receivePlayers(sf::TcpListener& listener)
{
    socket1 = std::make_unique<sf::TcpSocket>();
    while (!acceptSocket(listener, socket1, 1));

    socket2 = std::make_unique<sf::TcpSocket>();
    while (!acceptSocket(listener, socket2, 2));
}

bool Lobby::acceptSocket(sf::TcpListener& listener, std::unique_ptr<sf::TcpSocket>& toAccept, int pNumber)
{
    if (listener.accept(*toAccept) != sf::Socket::Done)return false;
    selector.add(*toAccept);
    sf::Packet p;
    p << pNumber;
    if (toAccept->send(p) != sf::Socket::Done) {
        toAccept->disconnect(); //Nope
        return false;
    }
    return true;
}

bool Lobby::pollEvent(std::pair<sf::Event, Player *> &event)
{
    m_eventsMutex.lock();
    if(m_events.size() == 0){
        m_eventsMutex.unlock();
        return false;
    }
    event = m_events.front();
    m_events.pop();
    m_eventsMutex.unlock();
    return true;
}

void Lobby::start()
{
    sf::Packet startPacket;
    startPacket << true;
    if (socket1->send(startPacket) != sf::Socket::Done ||
            socket2->send(startPacket) != sf::Socket::Done) {
        socket1->disconnect();
        socket2->disconnect();
        return; //Not possible to play
    }

    listeningThread.launch();
    sf::Clock mainClock;
    sf::Time totalTime;

    bool running = true;
    while (running) {
        sf::Time elapsed = mainClock.restart();
        totalTime += elapsed;

        running = !game.playerWon();
        std::pair<sf::Event, Player*> ev;
        while(pollEvent(ev)){
            game.handleEvent(ev.first);
        }

        game.update(elapsed);
        if (totalTime.asMilliseconds() > 1) {
            sf::Packet packet;
            packet << game;
            socket1->send(packet); //Update the players
            socket2->send(packet);
            totalTime = sf::Time(); // Reset total time
        }
        sf::sleep(sf::milliseconds(10));
        socketMutex.lock();
        if (!socket1 || !socket2) {
            socketMutex.unlock();
            break;
        }
        socketMutex.unlock();
    }

    if (socket1 && socket2) { // One player lost
        sf::Packet lastPacket;
        lastPacket << game;
        socket1->send(lastPacket);
        socket2->send(lastPacket);
        socket1->disconnect();
        socket2->disconnect();
    } else {//One player disconnected
        earlyWinner();
    }

    mState = { LOBBY_STATE::STOP };
    listeningThread.wait();
}

void Lobby::earlyWinner()
{
    //When on player disconnects, warns the second one (TODO: add a message explaining the other player disconnected)
    sf::Packet p;
    if (socket1) {
        game.getPlayer1().setIsWinner(true);
        p << game;
        socket1->send(p);
        socket1->disconnect();
    } else {
        game.getPlayer2().setIsWinner(true);
        p << game;
        socket2->send(p);
        socket2->disconnect();
    }
}

void Lobby::listenSockets()
{
    while (1) {
        if (!selector.wait())continue;
        receiveSocket(socket1, game.getPlayer1());
        receiveSocket(socket2, game.getPlayer2());
        if (isFinished())
            break;
    }
}

void Lobby::receiveSocket(std::unique_ptr<sf::TcpSocket>& toReceive, Player &player)
{
    if (!selector.isReady(*toReceive)) return; //Not ready to read, we don't know if it's still connected
    sf::Packet packet;
    int evtType;
    int evtKey;
    sf::Event::EventType type;
    sf::Keyboard::Key key;
    sf::Socket::Status rcvStatus = toReceive->receive(packet);
    if (rcvStatus == sf::Socket::Done) {
        sf::Event ev;
        packet >> evtType >> evtKey;
        type = static_cast<sf::Event::EventType> (evtType);
        key = static_cast<sf::Keyboard::Key> (evtKey);
        ev.type = type;
        ev.key.code = key;
        m_eventsMutex.lock();
        m_events.emplace(ev, &player);
        m_eventsMutex.unlock();
    } else /* if (rcvStatus == sf::Socket::Disconnected) */ {
        socketMutex.lock();
        toReceive = std::unique_ptr<sf::TcpSocket>{};
        socketMutex.unlock();
    }
}

bool Lobby::isFinished() const
{
    return mState == LOBBY_STATE::STOP;
}

}
