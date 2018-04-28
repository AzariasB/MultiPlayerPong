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
 * File:   Paddle.h
 * Author: azarias
 *
 * Created on 8 octobre 2017, 19:10
 */

#pragma once


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Network/Packet.hpp>

#include <Box2D/Dynamics/b2Body.h>

#include "Ball.hpp"
#include "VectorsUtils.hpp"
#include "Config.hpp"
#include "PhysicObject.hpp"

class Game;

/**
 * @brief The Paddle class the paddle is controlled
 * by the player with the up/down arrows, this is used
 * to make the ball bounce, and avoid loosing the game
 */
class Paddle : public PhysicObject {
public:
	/**
	 * @brief Paddle constructor
	 * @param game reference to the game
	 * @param startPos starting position of the paddle
	 */
    Paddle(const Game &game, std::size_t pNumber);

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
     * @brief extend when the "extend" boost was taken
     */
    void extend();

    /**
     * @brief retract when the "retract" boost was taken
     */
    void retract();

    /**
     * @brief resetPowerupEffect removes the effect of a given powerup type
     */
    void resetPowerupEffect(Powerup::POWERUP_TYPE type);

	/**
	 * @brief update update the paddle states
	 * @param dtS the time since the last update
	 */
	void update(const sf::Time &elapsed);

	/**
	 * @brief reset resets the inner state of the paddle
	 */
	void reset();

    /**
     * @brief setIsAI changes the ai state of the paddle
     * @param isAI wether the paddle is controlled by the computer
     */
    void setIsAI(bool isAI);

    /**
     * @brief getNum the number of the player owning this paddle
     * @return
     */
    std::size_t getNum() const;


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
    void setYVelocity(float32 yVelocity);

    /**
     * @brief mStartPos store the starting position
     * to use when reseting the paddle
     */
    const b2Vec2 mStartPos;

    b2Vec2 mVelocity;

    sf::Int32 m_widthBoost = 0;

    /**
     * @brief mNum keep the number
     * of the player in the paddle
     * for when a contact happens
     */
    const std::size_t mNum;

    /**
     * @brief isAI wether this paddle is controlled by an AI
     */
    bool m_isAI = false;
};





