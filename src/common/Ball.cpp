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
 * File:   Ball.cpp
 * Author: azarias
 * 
 * Created on 8 octobre 2017, 18:48
 */

#include <SFML/Network/Packet.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include "Ball.hpp"
#include "Game.hpp"

Ball::Ball(const Game& game) :
PhysicObject(game, PO_TYPE::BALL)
{
    b2BodyDef mBodyDef;
    mBodyDef.position = b2Vec2(BALL_START_X, BALL_START_Y);
    mBodyDef.type = b2_dynamicBody;
    mBody = mGame.world().CreateBody(&mBodyDef);

    mBody->ApplyLinearImpulse(b2Vec2(BALL_DIR_X, BALL_DIR_Y), mBody->GetWorldCenter(), false);
    mBody->SetUserData(this);

    b2CircleShape mShape;
    mShape.m_p.Set(0,0);
    mShape.m_radius = BALL_RADIUS;

    b2FixtureDef def;
    def.shape = &mShape;
    def.restitution = 1.f;
    def.density = 0.f;
    def.friction = 0.f;

    mBody->CreateFixture(&def);
}

Ball::~Ball()
{
}

void Ball::update(const sf::Time &elapsed)
{
    B2_NOT_USED(elapsed);
    //no updates for now
}

void Ball::resetPowerup(Powerup::POWERUP_TYPE type)
{
    if(type == Powerup::BALL_EXTEND || type == Powerup::BALL_RETRACT){
        m_radiusBoost = 0;
    }
}

void Ball::reset()
{
    mBody->SetTransform(b2Vec2(BALL_START_X, BALL_START_Y),0);
    mBody->SetLinearVelocity(b2Vec2(BALL_DIR_X, BALL_DIR_Y));
}

void Ball::extend()
{
    m_radiusBoost = BALL_RADIUS_POWERUP;
}

void Ball::retract()
{
    m_radiusBoost = -BALL_RADIUS_POWERUP;
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
