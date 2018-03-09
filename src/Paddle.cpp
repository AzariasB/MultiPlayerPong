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
#include "Game.hpp"

Paddle::Paddle(const Game &game, sf::Vector2f startPos) :
game(game),
isAI(isAI)
{
    b2BodyDef bodyDef;
    bodyDef.position = sfVecTob2Vec(startPos);
    bodyDef.type = b2_kinematicBody;
    mBody = game.world().CreateBody(&bodyDef);


    b2PolygonShape mShape;
    mShape.SetAsBox(pixToMeters(PADDLE_WIDTH), pixToMeters(PADDLE_HEIGHT));

    b2FixtureDef fDef;
    fDef.restitution = 1.f;
    fDef.friction = 0.f;

    fDef.shape = &mShape;
    mBody->CreateFixture(&fDef);
}

void Paddle::reset()
{
    /* position = m_initPosition;
    direction = sf::Vector2f(0,0); */
}

Paddle::~Paddle()
{
    game.world().DestroyBody(mBody);
    mBody = 0;
}

void Paddle::goDown()
{
    mVelocity.y = 1.f;
    mBody->SetLinearVelocity(mVelocity);
}

void Paddle::goUp()
{
    mVelocity.y = -1.f;
    mBody->SetLinearVelocity(mVelocity);
}

void Paddle::stop()
{
    mVelocity.y = 0;
    mBody->SetLinearVelocity(mVelocity);
}

void Paddle::extend()
{
    m_widthBoost = PADDLE_WIDTH_POWERUP;
}

void Paddle::retract()
{
    m_widthBoost = -PADDLE_WIDTH_POWERUP;
}

void Paddle::resetPowerupEffect(Powerup::POWERUP_TYPE type)
{
    if(type == Powerup::PADDLE_EXTEND || type == Powerup::PADDLE_RETRACT){
        m_widthBoost = 0;
    }
}

void Paddle::update(const sf::Time &elapsed)
{
    //no need for update for now
}



sf::Packet &operator<<(sf::Packet &packet, const Paddle &paddle)
{
    return packet << paddle.mBody->GetPosition() << paddle.mBody->GetLinearVelocity() << paddle.m_widthBoost;
}

sf::Packet &operator>>(sf::Packet &packet, Paddle &paddle)
{
    b2Vec2 position;
    b2Vec2 velocity;
    packet >> position >>  velocity >> paddle.m_widthBoost;
    paddle.mBody->SetTransform(position, paddle.mBody->GetAngle());
    paddle.mBody->SetLinearVelocity(velocity);
    return packet;
}
