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
 * File:   Paddle.cpp
 * Author: azarias
 *
 * Created on 8 octobre 2017, 19:10
 */

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <math.h>
#include <limits>

#include "Ball.hpp"
#include "Paddle.hpp"
#include "Game.hpp"

namespace mp {

Paddle::Paddle(const Game &game, std::size_t pNumber) :
    PhysicObject(game, this, typeid (Paddle), toBodyDef(toPosition(pNumber), b2_dynamicBody, true )),
    m_num(pNumber),
    m_startPos(pNumber == 1 ? b2Vec2(PADDLE_WIDTH/2.f, ARENA_HEIGHT/2.f) : b2Vec2(ARENA_WIDTH - PADDLE_WIDTH/2.f,  ARENA_HEIGHT/2.f))
{
    b2PolygonShape mShape;
    mShape.SetAsBox(PADDLE_WIDTH/2.f, PADDLE_HEIGHT/2.f);

    b2FixtureDef fDef;
    fDef.restitution = 0.f;
    fDef.friction = 0.f;
    fDef.density = 100000.f;

    fDef.shape = &mShape;
    mBody->CreateFixture(&fDef);
}

void Paddle::reset()
{
    mBody->SetTransform(m_startPos, mBody->GetAngle());
    mBody->SetLinearVelocity(b2Vec2());
    m_velocity.y = 0;
}

b2Vec2 Paddle::toPosition(std::size_t pNumber)
{
    return pNumber == 1 ?
                b2Vec2(PADDLE_WIDTH/2.f, ARENA_HEIGHT/2.f) :
                b2Vec2(ARENA_WIDTH - PADDLE_WIDTH/2.f,  ARENA_HEIGHT/2.f);
}


Paddle::~Paddle()
{
}


void Paddle::extend()
{
    //m_widthBoost = PADDLE_WIDTH_POWERUP;
}

void Paddle::retract()
{
    //m_widthBoost = -PADDLE_WIDTH_POWERUP;
}

void Paddle::setYVelocity(float32 yVelocity)
{
    m_velocity.y = yVelocity;
    mBody->SetLinearVelocity(m_velocity);
}

std::size_t Paddle::getNum() const
{
    return m_num;
}


void Paddle::setIsAI(bool isAI)
{
    m_isAI = isAI;
}

bool Paddle::isAi() const
{
    return m_isAI;
}

void Paddle::update(const sf::Time &elapsed)
{
    B2_NOT_USED(elapsed);
    if(!m_isAI)return;

    float ballYPosition = mGame.getBall().getPosition().y;

    float mYPosition = mBody->GetPosition().y;
    if(mYPosition < ballYPosition){
        setYVelocity(1);
    }else if(mYPosition > ballYPosition){
        setYVelocity(-1);
    }else{
        setYVelocity(0);
    }
}



sf::Packet &operator<<(sf::Packet &packet, const Paddle &paddle)
{
    return packet << paddle.mBody->GetPosition() << paddle.mBody->GetLinearVelocity();
}

sf::Packet &operator>>(sf::Packet &packet, Paddle &paddle)
{
    b2Vec2 position;
    b2Vec2 velocity;
    packet >> position >>  velocity;
    paddle.mBody->SetTransform(position, paddle.mBody->GetAngle());
    paddle.mBody->SetLinearVelocity(velocity);
    return packet;
}

}
