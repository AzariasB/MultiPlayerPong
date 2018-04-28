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
 * File:   Lobby.h
 * Author: azarias
 *
 * Created on 17 octobre 2017, 16:45
 */

#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <memory>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/SocketSelector.hpp>

#include "src/common/Game.hpp"

enum LOBBY_STATE {
	WAIT,
	PLAY,
	STOP
};

/**
 * @brief The Lobby class a lobby is containg a single game
 * and two player's sockets, this way, the server can host
 * different lobbies at the same time
 */
class Lobby : sf::NonCopyable {
public:
	/**
	 * @brief Lobby constructor
	 */
	Lobby();

	/**
	 * @brief receivePlayers accepts the two neccessary players
	 * this function is blocking and will only finish once
	 * the two players are accepted
	 * @param listener the tcplistener to use to receive the players
	 */
	void receivePlayers(sf::TcpListener &listener);

	/**
	 * @brief start starts the game
	 */
	void start();

	/**
	 * @brief listenSockets called by the thread :
	 * listen for any incoming socket messages from any players
	 */
	void listenSockets();

	/**
	 * @brief getFirstSocket
	 * @return pointer to the first player's socket
	 */
	sf::TcpSocket *getFirstSocket()
	{
		return socket1.get();
	}

	/**
	 * @brief getSecondSocket
	 * @return  pointer to the second player's socket
	 */
	sf::TcpSocket *getSecondSocket()
	{
		return socket2.get();
	}

    /**
     * @brief tryAddPowerup if there is a chance, adds a power up
     * @return wether a powerup was added to the game
     */
    bool tryAddPowerup(const sf::Time &elapsed);

	/**
	 * @brief isFinished
	 * @return wether the lobby's game finished (thus it can be destroyed)
	 */
	bool isFinished() const;
	
	/**
	 * @brief ballBounce called when the bounce event is triggered
	 * handles the ball bouncing
	 * @param pNumber the player's number who's hitting the ball
	 */
    void ballBounce(std::size_t pNumber, b2Vec2 &pos);
	
	/**
	 * @brief handleLoss call when the event "playerLost" is fired
	 * @param pLooser the number of the player who lost
	 */
	void handleLoss(int pLooser);


	virtual ~Lobby();
private:
	/**
	 * @brief state the lobby's current state
	 */
	LOBBY_STATE state = LOBBY_STATE::WAIT;

	/**
	 * @brief receiveSocket received data from the given socket
	 * @param toReceive the socket to use to receive the data
	 * @param player the player corresponding to the socket
	 */
	void receiveSocket(std::unique_ptr<sf::TcpSocket> &toReceive, Player &player);

	/**
	 * @brief acceptSocket accepts a socket, and sets the given socket reference when the connection is established
	 * @param listener the tcp listener
	 * @param toAccept the reference to the socket to set once the connection is established
	 * @param pNumber the number of the player to accept
	 * @return
	 */
	bool acceptSocket(sf::TcpListener &listener, std::unique_ptr<sf::TcpSocket> &toAccept, int pNumber);
	
	/**
	 * @brief earlyWinner called when one of the player's left the match before it ends,
	 * to warn the other player that the game is over, and claim him winner
	 */
	void earlyWinner();

	/**
	 * @brief setState changes the state of the lobby
	 * @param nwState the new state of the lobby
	 */
	void setState(LOBBY_STATE nwState);

	/**
	 * @brief game the lobby's game
	 */
	Game game;

	/**
	 * @brief socket1 player's one socket
	 */
	std::unique_ptr<sf::TcpSocket> socket1;

	/**
	 * @brief socket2 players's two socket
	 */
	std::unique_ptr<sf::TcpSocket> socket2;

	/**
	 * @brief selector socket selector
	 */
	sf::SocketSelector selector;

	/**
	 * @brief listeningThread thread to listen for any incomming message from the clients
	 */
	sf::Thread listeningThread;

	/**
	 * @brief socketMutex mutex to lock any modifications of the sockets
	 */
	sf::Mutex socketMutex;

    /**
     * @brief m_timeSinceLastPowerUp time since last powerup poped up
     */
    sf::Time m_nextPowerup;

	/**
	 * @brief stateMutex mutex to lock when getting/setting the state's value
	 */
	mutable sf::Mutex stateMutex;
};

/**
 * @brief The LobbyThread struct the lobby with the thead running it
 */
struct LobbyThread {
	LobbyThread();

	virtual ~LobbyThread();

	Lobby lobby;
	sf::Thread thread;
};


