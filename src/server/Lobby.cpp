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
 * File:   Lobby.cpp
 * Author: azarias
 *
 * Created on 17 octobre 2017, 16:45
 */

#include "Lobby.hpp"

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
    game.getEventManager().declareListener(game.hitPaddleEvent, &Lobby::ballBounce, this);
    game.getEventManager().declareListener(game.lostEvent, &Lobby::handleLoss, this);
    game.getEventManager().declareListener(game.countdownEndedEvent, &Game::setGameState, &game, GAMESTATE::PLAYING);
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
//        if(tryAddPowerup(elapsed)){
//            std::cout << "Adding a powerup\n";
//        }

        game.update(elapsed);
        if (totalTime.asMilliseconds() > 10) {
            sf::Packet packet;
            packet << game;
            socket1->send(packet); //Update the players
            socket2->send(packet);
            game.clearNewPowerUps();
            totalTime = sf::Time(); // Reset total time
        }
        //sf::sleep(sf::milliseconds(1));
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
    setState(LOBBY_STATE::STOP);
    listeningThread.wait();
}

bool Lobby::tryAddPowerup(const sf::Time &elapsed)
{
    m_nextPowerup -= elapsed;
    if(m_nextPowerup > sf::Time::Zero)return false;
    m_nextPowerup = sf::seconds(3);
    //randomize the parameters
    Powerup::POWERUP_TYPE pt = static_cast<Powerup::POWERUP_TYPE>(rrand(0,4));
    int dirLeft = rrand(-100, 100);
    int dirUp = rrand(-100, 100);
    game.addPowerUp(pt,sf::Vector2f(SF_ARENA_WIDTH/2, SF_ARENA_HEIGHT/2), normalize(sf::Vector2f(dirLeft, dirUp)));
    return true;
}

void Lobby::ballBounce(std::size_t pNumber, b2Vec2 &pos)
{
    if (pNumber == 1)
        game.getPlayer1().gainPoint();
    else if (pNumber == 2)
        game.getPlayer2().gainPoint();
}

void Lobby::handleLoss(int pLooser)
{
    bool p1Looser = pLooser == 1;
    game.getPlayer1().setIsWinner(!p1Looser);
    game.getPlayer2().setIsWinner(p1Looser);
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

void Lobby::setState(LOBBY_STATE nwState)
{
    stateMutex.lock();
    state = nwState;
    stateMutex.unlock();
}

void Lobby::listenSockets()
{
    while (1) {
        if (!selector.wait())continue;
        socketMutex.lock();
        receiveSocket(socket1, game.getPlayer1());
        receiveSocket(socket2, game.getPlayer2());
        socketMutex.unlock();
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
        game.handleEvent(ev, player);
    } else /* if (rcvStatus == sf::Socket::Disconnected) */ {
        toReceive = std::unique_ptr<sf::TcpSocket>{};
    }
}

bool Lobby::isFinished() const
{
    bool isFinished = false;
    stateMutex.lock();
    isFinished = state == LOBBY_STATE::STOP;
    stateMutex.unlock();
    return isFinished;
}
