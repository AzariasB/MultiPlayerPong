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
    PhysicObject(game, PO_TYPE::PADDLE),
    mNum(pNumber),
    mStartPos(pNumber == 1 ? b2Vec2(PADDLE_WIDTH/2.f, ARENA_HEIGHT/2.f) : b2Vec2(ARENA_WIDTH - PADDLE_WIDTH/2.f,  ARENA_HEIGHT/2.f))
{
    b2BodyDef bodyDef;
    bodyDef.position = mStartPos;
    bodyDef.type = b2_dynamicBody;
    mBody = mGame.world().CreateBody(&bodyDef);
    mBody->SetFixedRotation(true);
    mBody->SetUserData(this);

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
    mBody->SetTransform(mStartPos, mBody->GetAngle());
    mBody->SetLinearVelocity(b2Vec2());
    mVelocity.y = 0;
}

Paddle::~Paddle()
{
}

void Paddle::goDown()
{
    setYVelocity(1.f);
}

void Paddle::goUp()
{
    setYVelocity(-1.f);
}

void Paddle::stop()
{
    setYVelocity(0);
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
    mVelocity.y = yVelocity;
    mBody->SetLinearVelocity(mVelocity);
}

std::size_t Paddle::getNum() const
{
    return mNum;
}


void Paddle::setIsAI(bool isAI)
{
    m_isAI = isAI;
}


void Paddle::update(const sf::Time &elapsed)
{
    B2_NOT_USED(elapsed);
    if(!m_isAI)return;

    float ballYPosition = mGame.getBall().getPosition().y;

    float mYPosition = mBody->GetPosition().y;
    if(mYPosition < ballYPosition){
        goDown();
    }else if(mYPosition > ballYPosition){
        goUp();
    }else{
        stop();
    }
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

}
