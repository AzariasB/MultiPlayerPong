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
 * File:   Game.h
 * Author: azarias
 *
 * Created on 11 octobre 2017, 10:09
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Network/Packet.hpp>

#include "Config.hpp"
#include "Paddle.hpp"
#include "Player.hpp"
#include "EventManager.hpp"

/**
 * @brief The GAMESTATE enum current state of the game
 */
enum GAMESTATE{
	COUNTDOWN,
	PLAYING,
};

/**
 * @brief The Game class one of the main classes of the app
 * Contains all the data relative to the game : it's component
 * and the resources necessary for these components to work
 * (like the event manager)
 * this class is supposed to be thread safe
 */
class Game {
public:
	/**
	 * @brief Game constructor
	 */
	Game();
	virtual ~Game();

	/**
	 * @brief update updates the game states, and all it's sub-components
	 * @param dtS the time since the last update
	 */
	void update(const sf::Time &elapsed);

	/**
	 * @brief handleEvent handles the given event, trigerred by the given player
	 * @param ev the sfml event
	 * @param player the player who trigerred the event
	 */
	void handleEvent(const sf::Event &ev, Player &player);

	/**
	 * @brief getBall const reference to the ball object
	 * @return const reference to the ball object
	 */
	const Ball& getBall() const;

	/**
	 * @brief getPlayer1 const reference to the first player
	 * @return const reference to the first player
	 */
	const Player &getPlayer1() const;

	/**
	 * @brief getPlayer1 reference to the first player
	 * @return reference to the first player
	 */
	Player &getPlayer1();

	/**
	 * @brief getPlayer2 reference to the second player
	 * @return reference to the second player
	 */
	Player &getPlayer2();

	/**
	 * @brief getEventManager reference to the event manager
	 * @return a reference to the event manager
	 */
	EventManager &getEventManager();

	/**
	 * @brief getPlayer2 const reference to the second player
	 * @return const reference to the second player
	 */
	const Player &getPlayer2() const;

	/**
	 * @brief setPaddle2Position changes the player1 paddle's position
	 * @param p2PaddlePos the new position of the paddle
	 */
	void setPaddle2Position(const sf::Vector2f &p2PaddlePos);

	/**
	 * @brief setPaddle1Position changes the player2 paddle's position
	 * @param p1Pos
	 */
	void setPaddle1Position(const sf::Vector2f &p1Pos);


	/**
	 * @brief setGameState changes the current game state
	 * @param gameState the new game state
	 */
	void setGameState(GAMESTATE gameState);

	/**
	 * @brief reset resets the inner state of the game object
	 */
	void reset();

	/**
	 * @brief operator << serialize the game to a sf::Packet
	 * @param packet the packet in which to serialize the game object
	 * @param game the game to serialize
	 * @return the packet with the serialize game object
	 */
	friend sf::Packet &operator<<(sf::Packet &packet, Game &game);

	/**
	 * @brief operator >> deserializes the game object using the given packet
	 * @param packet the packet from where to retrieve the data
	 * @param game the game to init with the packet's data
	 * @return
	 */
	friend sf::Packet &operator>>(sf::Packet &packet, Game &game);

	/**
	 * @brief playerWon wether one player won the match
	 * @return wether one player won the match
	 */
	bool playerWon() const;

	/**
	 * @brief getNumWinner
	 * @return the number of the winner (-1) if no one won
	 */
	int getNumWinner() const;

	/**
	 * @brief isCountingDown
	 * @return wether the game is currently doing the countdown before the start
	 */
	bool isCountingDown() const;

	sf::Time getCountdownTime() const;

private:
	/**
	 * @brief updateCountdown updates the game when in countdown mode
	 * @param elapsed time elapsed since last update
	 */
	void updateCountdown(const sf::Time &elapsed);

	/**
	 * @brief updatePlaying updates the game when in playing mode
	 * @param elapsed time elapsed since last update
	 */
	void updatePlaying(const sf::Time &elapsed);

	/**
	 * @brief mainBall the ball object for the game
	 */
	Ball mainBall;

	/**
	 * @brief m_evManager THE event manager for the game
	 */
	EventManager m_evManager;

	/**
	 * @brief p1 the first player
	 */
	Player p1;

	/**
	 * @brief p2 the second player
	 */
	Player p2;

	/**
	 * @brief m_countDownTime time before we can start the game
	 */
	sf::Time m_countDownTime;

	/**
	 * @brief m_state current state of the game
	 */
	GAMESTATE m_state;

	/**
	 * @brief mutex the mutex used to make this class thread safe
	 */
	mutable sf::Mutex mutex;

	//"signals"
public:
	const sf::Uint64 bounceEvent = m_evManager.nextEventCode();
	const sf::Uint64 lostEvent = m_evManager.nextEventCode();
	const sf::Uint64 countdownEndedEvent = m_evManager.nextEventCode();
};


#endif /* GAME_H */

