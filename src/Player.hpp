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
 * File:   Player.h
 * Author: azarias
 *
 * Created on 18 octobre 2017, 22:05
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Config.hpp>

#include "Paddle.hpp"

class Game;

/**
 * @brief The Player class the player is the person controlling
 * the paddle, the object contains the paddle controlled by the player
 * the player's score, and the player number
 */
class Player {
public:
	/**
	 * @brief Player constructor
	 * @param game reference to the game
	 * @param num the player's number
	 */
    Player(Game &game, std::size_t num);

	/**
	 * @brief reset resets the inner state of the player
	 */
	void reset();

	/**
	 * @brief operator << serializes the player's object
	 * @param packet the packet in which to serialize
	 * @param p the player to serialize
	 * @return the packet with the serialized player
	 */
	friend sf::Packet &operator<<(sf::Packet &packet, const Player &p);

	/**
	 * @brief operator >> deserialized the player's object
	 * @param packet the packet in which to serialize
	 * @param p the player to init
	 * @return the packet with the deserialized player
	 */
	friend sf::Packet &operator>>(sf::Packet &packet, Player &p);

	/**
	 * @brief getNum
	 * @return the player's number
	 */
	int getNum() const
	{
		return m_num;
	}

	/**
	 * @brief setNum sets the player number
	 * @param num the new player number
	 */
	void setNum(int num)
	{
		this->m_num = num;
	}

	/**
	 * @brief getPaddle
	 * @return  const reference to the player's paddle
	 */
	const Paddle &getPaddle() const
	{
		return m_paddle;
	}

	/**
	 * @brief getPaddle
	 * @return a reference to the player's paddle
	 */
	Paddle &getPaddle()
	{
		return m_paddle;
	}

	/**
	 * @brief getScore
	 * @return the player's score
	 */
	int getScore() const
	{
		return m_score;
	}

	/**
	 * @brief gainPoint increments the player's score by one
	 */
	void gainPoint();

	/**
	 * @brief isWinner
	 * @return wether the player is the winner
	 */
	bool isWinner() const
	{
		return m_isWinner;
	}

	/**
	 * @brief setIsWinner changes the "winner" state of the player
	 * @param isWinner the new winner state
	 */
	void setIsWinner(bool isWinner)
	{
		m_isWinner = isWinner;
	}

	virtual ~Player();
private:
	/**
	 * @brief m_game reference to the game object
	 */
	Game &m_game;

	/**
	 * @brief m_num the player's number
	 */
	int m_num = -1;

	/**
	 * @brief m_score the player's score
	 */
	int m_score = 0;

	/**
	 * @brief m_isWinner wether the player is the winner
	 */
	bool m_isWinner = false;

	/**
	 * @brief m_paddle the players paddle
	 */
	Paddle m_paddle;
};

#endif /* PLAYER_H */

