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
 * File:   Paddle.h
 * Author: azarias
 *
 * Created on 8 octobre 2017, 19:10
 */

#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Network/Packet.hpp>

#include "Ball.hpp"
#include "VectorsUtils.hpp"
#include "Config.hpp"

class Game;

/**
 * @brief The Paddle class the paddle is controlled
 * by the player with the up/down arrows, this is used
 * to make the ball bounce, and avoid loosing the game
 */
class Paddle {
public:
	/**
	 * @brief Paddle constructor
	 * @param game reference to the game
	 * @param startPos starting position of the paddle
	 */
	Paddle(const Game &game, sf::Vector2f startPos = sf::Vector2f(0, 0));

	/**
	 * @brief goUp changes the direction in order to go up
	 */
	void goUp();

	/**
	 * @brief goDown changes the direction in order to go down
	 */
	void goDown();

	/**
	 * @brief stop sets the direction to the null vector in order to stop moving
	 */
	void stop();

	/**
	 * @brief update update the paddle states
	 * @param dtS the time since the last update
	 */
	void update(const sf::Time &elapsed);

	/**
	 * @brief setPosition changes the position of the paddle
	 * @param nwPosition the new position of the paddle
	 */
	void setPosition(const sf::Vector2f &nwPosition);

	/**
	 * @brief intersectsWith checks if the paddle is currently intersecting with the game's ball
	 * @param ball the ball to check for collision
	 * @return wether the paddle is colliding with the ball
	 */
	bool intersectsWith(const Ball &ball);

	/**
	 * @brief reset resets the inner state of the paddle
	 */
	void reset();

	/**
	 * @brief getBounceAngle the ball's bouncing angle is quite special :
	 * it depends on where it hits the paddle, so depending on the position where
	 * the ball hits the paddle, the bouncing angle will not be the same
	 * @param yPos the yPosition of the ball
	 * @return the new angle of the ball
	 */
	float getBounceAngle(float yPos);

	/**
	 * @brief getPosition
	 * @return const reference to the paddle's position
	 */
	const sf::Vector2f &getPosition() const
	{
		return position;
	}

	/**
	 * @brief getDirection
	 * @return const reference to the paddle's direction
	 */
	const sf::Vector2f &getDirection() const
	{
		return direction;
	}

    /**
     * @brief getHitBox the hitbox of the paddle
     * with the correct height if any boost were given
     * @return
     */
    sf::FloatRect getHitBox() const;

	/**
	 * @brief operator << serializes the paddle to the given sf::Packet
	 * @param packet the packet in which to serialze the paddle
	 * @param paddle the paddle to serialzie
	 * @return the packet with the serialized paddle
	 */
	friend sf::Packet &operator<<(sf::Packet &packet, const Paddle &paddle);

	/**
	 * @brief operator >> deserializes the paddle
	 * @param packet the packet from which to get the data
	 * @param paddle the paddle to init with the packet's data
	 * @return the deserialized packet
	 */
	friend sf::Packet &operator>>(sf::Packet &packet, Paddle &paddle);


	virtual ~Paddle();
private:
	/**
	 * @brief game reference to the game object
	 */
	const Game &game;


    int m_widthBoost = 0;

	/**
	 * @brief position the paddle's position
	 */
	sf::Vector2f position;

	/**
	 * @brief direction the paddle's direction
	 */
	sf::Vector2f direction;

	/**
	 * @brief isAI wether the paddles is owned by an AI
	 */
	bool isAI;

	const sf::Vector2f m_initPosition;
};



#endif /* PADDLE_H */

