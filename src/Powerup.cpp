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
 * File:   Powerup.cpp
 * Author: azarias
 *
 * Created on 20/11/2017
 */
#include "Powerup.hpp"
#include "Game.hpp"

sf::Uint64 Powerup::m_nextId = 0;

sf::Uint64 Powerup::nextId()
{
    return m_nextId;
}

Powerup::Powerup(Game &game):
    m_game(game),
    m_id(m_nextId++),
    hitPaddle(game.getEventManager().nextEventCode()),
    effectFinished(game.getEventManager().nextEventCode())
{

}

Powerup::Powerup(Game &game, Powerup::POWERUP_TYPE type, const sf::Vector2f &startPos, const sf::Vector2f &direction):
    m_game(game),
    m_id(m_nextId++),
    m_type(type),
    m_hitBox(startPos.x, startPos.y, POWERUP_SIDE, POWERUP_SIDE),
    m_direction(direction),
    hitPaddle(game.getEventManager().nextEventCode()),
    effectFinished(game.getEventManager().nextEventCode())
{

}

void Powerup::startTimer()
{
    m_effectTime = sf::seconds(3);
}

void Powerup::update(const sf::Time &elapsed)
{
    if(m_effectTime > sf::Time::Zero){
        m_effectTime -= elapsed;
        if(m_effectTime <= sf::Time::Zero)
            m_game.getEventManager().trigger(effectFinished);
        return;
    }

    sf::Vector2f progression = m_direction * (elapsed.asSeconds() * PADDLE_SPEED * 100 );
    if((m_hitBox.top + m_hitBox.height + progression.y)  > ARENA_HEIGHT || (m_hitBox.top + progression.y) < 0){
        m_direction.y = -m_direction.y;
        m_hitBox.top += progression.y;
        m_hitBox.left += progression.x;
    }

    m_hitBox.left += progression.x;
    m_hitBox.top += progression.y;
    if(m_hitBox.intersects(m_game.getPlayer1().getPaddle().getHitBox())){
        m_game.getEventManager().trigger(hitPaddle, 1);
    }else if(m_hitBox.intersects(m_game.getPlayer2().getPaddle().getHitBox())){
        m_game.getEventManager().trigger(hitPaddle, 2);
    }
}

bool Powerup::isOut() const
{
    return m_hitBox.top + m_hitBox.height < 0 || m_hitBox.top  > ARENA_HEIGHT ||
            m_hitBox.left + m_hitBox.width < 0 || m_hitBox.left > ARENA_WIDTH;
}


sf::Packet &operator<<(sf::Packet &packet, const Powerup &powerup)
{
    return packet << powerup.m_id << static_cast<sf::Int32>(powerup.m_type) << powerup.m_hitBox << powerup.m_direction << powerup.m_effectTime.asMicroseconds();
}


sf::Packet &operator>>(sf::Packet &packet, Powerup &powerup)
{
    sf::Int64 effectTime;
    sf::Int32 powerupType;
    packet >> powerup.m_id >> powerupType >> powerup.m_hitBox >> powerup.m_direction >> effectTime;
    powerup.m_type = static_cast<Powerup::POWERUP_TYPE>(powerupType);
    powerup.m_effectTime = sf::microseconds(effectTime);
    return packet;
}
