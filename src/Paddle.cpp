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
 * File:   Paddle.cpp
 * Author: azarias
 * 
 * Created on 8 octobre 2017, 19:10
 */

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <math.h>

#include "Ball.hpp"
#include "Paddle.hpp"

Paddle::Paddle(const Game &game, sf::Vector2f startPos) :
game(game),
isAI(isAI),
position(startPos),
m_initPosition(startPos),
direction(0, 0)
{
}

void Paddle::reset()
{
	position = m_initPosition;
	direction = sf::Vector2f(0,0);
}

Paddle::~Paddle()
{
}

void Paddle::goDown()
{
	direction.y = 1;
}

void Paddle::goUp()
{
	direction.y = -1;
}

void Paddle::stop()
{
	direction.y = 0;
}

void Paddle::update(const sf::Time &elapsed)
{
	position = position + direction * (elapsed.asSeconds() * (PADDLE_SPEED * 100));
	position.y = clampf(0, ARENA_HEIGHT - PADDLE_HEIGHT, position.y);
}


bool Paddle::intersectsWith(const Ball& ball)
{
	sf::Vector2f distToCircle;
	distToCircle.x = abs(ball.getPosition().x + BALL_RADIUS - (position.x + PADDLE_WIDTH / 2));
	distToCircle.y = abs(ball.getPosition().y + BALL_RADIUS - (position.y + PADDLE_HEIGHT / 2));


	if (distToCircle.x > (PADDLE_WIDTH / 2 + BALL_RADIUS) || distToCircle.y > (PADDLE_HEIGHT / 2 + BALL_RADIUS))return false;

	if (distToCircle.x <= PADDLE_WIDTH / 2 || distToCircle.y <= PADDLE_HEIGHT / 2) return true;

	float cornderSqDist = powf(distToCircle.x - PADDLE_WIDTH / 2, 2) +
		powf(distToCircle.y - PADDLE_HEIGHT / 2, 2);

	return cornderSqDist < powf(BALL_RADIUS, 2);
}

float Paddle::getBounceAngle(float yPos)
{
	float distFromCenter = yPos - (position.y + (PADDLE_HEIGHT / 2));
	return clampf(-0.8, 0.8, distFromCenter / (PADDLE_HEIGHT / 2));
}


sf::Packet &operator<<(sf::Packet &packet, const Paddle &paddle)
{
	return packet << paddle.position << paddle.direction;
}

sf::Packet &operator>>(sf::Packet &packet, Paddle &paddle)
{
	return packet >> paddle.position >> paddle.direction;
}

void Paddle::setPosition(const sf::Vector2f& nwPosition)
{
	position = nwPosition;
}
