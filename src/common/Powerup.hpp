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
 * File:   Powerup.hpp
 * Author: azarias
 *
 * Created on 20/11/2017
 */
#pragma once

#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network/Packet.hpp>
#include "Config.hpp"

namespace mp {

class Game;

class Powerup
{
public:
    enum POWERUP_TYPE{
        BALL_EXTEND,
        BALL_RETRACT,
        PADDLE_EXTEND,
        PADDLE_RETRACT,

        ALL_POWERUPS
    };

    Powerup(Game &game);

    Powerup(Game &game, POWERUP_TYPE type, const sf::Vector2f &startPos, const sf::Vector2f &direction);

    virtual ~Powerup();

    void update(const sf::Time &elapsed);

    POWERUP_TYPE getType() const
    {
        return m_type;
    }

    const sf::FloatRect &getHitbox() const
    {
        return m_hitBox;
    }

    void startTimer();

    void hide();

    void show();

    bool isHidden() const;

    bool timerStarted() const;

    bool isOut() const;

    sf::Uint64 getId() const
    {
        return m_id;
    }

    static sf::Uint64 nextId();

    /**
     * @brief operator << serializes the paddle to the given sf::Packet
     * @param packet the packet in which to serialze the paddle
     * @param paddle the paddle to serialzie
     * @return the packet with the serialized paddle
     */
    friend sf::Packet &operator<<(sf::Packet &packet, const Powerup &powerup);

    /**
     * @brief operator >> deserializes the paddle
     * @param packet the packet from which to get the data
     * @param paddle the paddle to init with the packet's data
     * @return the deserialized packet
     */
    friend sf::Packet &operator>>(sf::Packet &packet, Powerup &powerup);

private:
    static sf::Uint64 m_nextId;

    Game &m_game;

    sf::Uint64 m_id;

    POWERUP_TYPE m_type;

    sf::FloatRect m_hitBox;

    sf::Vector2f m_direction;

    sf::Time m_effectTime = sf::Time::Zero;

    bool m_isHidden = false;

public:
    const sf::Uint64 hitPaddle;
    const sf::Uint64 effectFinished;
    const sf::Uint64 powerupDestroyed;
    //event "destroyed" by ball
};


}
