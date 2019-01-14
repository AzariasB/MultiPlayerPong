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
 * File:   Ball.cpp
 * Author: azarias
 *
 * Created on 8 octobre 2017, 18:48
 */

#include <SFML/Network/Packet.hpp>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include "Ball.hpp"
#include "Game.hpp"
#include "Jay.hpp"

namespace mp {

Ball::Ball(const Game& game) :
    PhysicObject(game, this, declareBody(game))
{
    reset();
}

b2Body *Ball::declareBody(const Game &game)
{
    return Jay::define(game, b2Vec2(BALL_START_X, BALL_START_Y), b2_dynamicBody)
                .addCircleFixture(b2Vec2(0,0), BALL_RADIUS, 1.f, .0f)
                .body();
}

Ball::~Ball()
{
}

void Ball::update(const sf::Time &elapsed)
{
    B2_NOT_USED(elapsed);
    //no updates for now
}

void Ball::reset()
{
    mBody->SetTransform(b2Vec2(BALL_START_X, BALL_START_Y),0);
    int xR = math::rrand(0, 100);
    int xDir = xR < 50 ? 1 : -1;
    int yR = math::rrand(0, 100);
    int yDir = yR < 50 ? 1 : -1;

    mBody->SetLinearVelocity(b2Vec2(BALL_DIR_X * BALL_SPEED * xDir, BALL_DIR_Y * BALL_SPEED * yDir));
}

void Ball::extend()
{
    //m_radiusBoost = BALL_RADIUS_POWERUP;
}

void Ball::retract()
{
    //m_radiusBoost = -BALL_RADIUS_POWERUP;
}

sf::Packet &operator<<(sf::Packet &packet, const Ball &ball)
{
    return packet << ball.mBody->GetPosition() << ball.mBody->GetLinearVelocity() << ball.m_radiusBoost;
}

sf::Packet &operator>>(sf::Packet &packet, Ball &ball)
{
    b2Vec2 position;
    b2Vec2 linearVelocity;

    packet >> position >> linearVelocity >> ball.m_radiusBoost;
    ball.mBody->SetLinearVelocity(linearVelocity);
    ball.mBody->SetTransform(position, ball.mBody->GetAngle());
    return packet;
}

}
