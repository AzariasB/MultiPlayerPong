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
 * File:   Ball.h
 * Author: azarias
 *
 * Created on 8 octobre 2017, 18:48
 */


#ifndef BALL_H
#define BALL_H


#include <iostream>
#include <SFML/Graphics.hpp>
#include <complex>
#include <SFML/Network/Packet.hpp>

#include "Config.hpp"
#include "Math.hpp"
#include "VectorsUtils.hpp"

class Game;

/**
 * @brief The Ball class the ball is the game object moving
 * on its own ( ruled by the server ), and that bounces between
 * the two paddles. It has a circular shape. If the ball gets out
 * of the field, the player that missed it looses.
 */
class Ball {
public:
	/**
	 * @brief Ball constructor
	 * @param game a reference to the game
	 */
	Ball(const Game &game);

	/**
	 * @brief update updates the ball position, given its current position
	 * and direction
	 * @param dtS the time since the last update
	 */
	void update(const sf::Time &elapsed);

	void reset();

	/**
	 * @brief xBounce bounces to the opposite X direction, normalize the vector direction
	 * @param bounceDir the new direction where to bounce
	 */
	void xBounce(float bounceDir)
	{
		direction.x = -direction.x;
		direction.y = bounceDir;
		direction = normalize(direction);
		position += direction;
	}

	/**
	 * @brief getPosition the current position
	 * @return the current position of the ball
	 */
	const sf::Vector2f &getPosition() const
	{
		return position;
	}

	/**
	 * @brief operator << seraializes the ball into a sf::Packet
	 * @param packet the packet in which to seralize
	 * @param ball the ball object to serialize
	 * @return the sf Packet with the serialized ball
	 */
	friend sf::Packet &operator<<(sf::Packet &packet, const Ball &ball);

	/**
	 * @brief operator >> deserialize the ball int the given ball object
	 * @param packet the packet to use to deserialize
	 * @param ball the target ball to init
	 * @return the sf::Packet with the deserialized ball
	 */
	friend sf::Packet &operator>>(sf::Packet &packet, Ball &ball);

	virtual ~Ball();
private:
	/**
	 * @brief a reference to the game object
	 */
	const Game &game;

	/**
	 * @brief position position of the ball
	 */
	sf::Vector2f position;

	/**
	 * @brief direction direction of the ball
	 */
	sf::Vector2f direction;
};




#endif /* BALL_H */

