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
 * File:   Player.cpp
 * Author: azarias
 *
 * Created on 18 octobre 2017, 22:05
 */

#include "Player.hpp"

namespace mp {

Player::Player(Game& game, std::size_t num) :
    m_game(game),
    m_num(num),
    m_paddle(game, num)
{

}

void Player::reset()
{
    m_paddle.reset();
    m_num = -1;
    m_score = 0;
    m_isWinner = false;
}

Player::~Player()
{
}

sf::Packet &operator<<(sf::Packet &packet, const Player &p)
{
    return packet << p.m_paddle << p.m_isWinner << p.m_num << p.m_score;
}

sf::Packet &operator>>(sf::Packet &packet, Player &p)
{
    return packet >> p.m_paddle >> p.m_isWinner >> p.m_num >> p.m_score;
}

void Player::gainPoint()
{
    m_score++;
}

}
