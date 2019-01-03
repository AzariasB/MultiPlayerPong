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
 * File:   Game.cpp
 * Author: azarias
 *
 * Created on 11 octobre 2017, 10:09
 */

#include <iostream>
#include <SFML/Window/Event.hpp>
#include "Game.hpp"
#include "Application.hpp"


namespace mp {

Game::Game() :
    m_physicWorld(m_gravity),
    m_ball(*this),
    m_p1(*this, 1),
    m_p2(*this, 2),
    m_upperWall(*this, b2Vec2(WALL_WITDH/2.f,WALL_HEIGHT/2.f)),
    m_lowerWall(*this, b2Vec2(WALL_WITDH/2.f , ARENA_HEIGHT - (WALL_HEIGHT/2.f))),
    m_countDownTime(sf::seconds(3)),
    m_state(GAMESTATE::COUNTDOWN),
    m_contactListener(),
    m_input()
{
    m_physicWorld.SetContactListener(&m_contactListener);

    m_contactListener.ballHitPaddleSignal.add(hitPaddleSignal);
}

Game::~Game()
{
}

void Game::handleEvent(const sf::Event& ev)
{
    m_input.handleEvent(ev);
    /* if (ev.type == sf::Event::KeyPressed) {
        if (ev.key.code == sf::Keyboard::Up) {
            player.getPaddle().goUp();
        } else if (ev.key.code == sf::Keyboard::Down) {
            player.getPaddle().goDown();
        }
    } else if (ev.type == sf::Event::KeyReleased) {
        player.getPaddle().stop();
    } */
}

void Game::update(const sf::Time &elapsed)
{
    if(!m_p1.getPaddle().isAi())
        m_p1.getPaddle().setYVelocity(m_input.getAxis(Input::Y_AXIS_1));

    if(!m_p2.getPaddle().isAi())
        m_p2.getPaddle().setYVelocity(m_input.getAxis(Input::Y_AXIS_2));

    m_p1.getPaddle().update(elapsed);
    m_p2.getPaddle().update(elapsed);
    if(m_state == GAMESTATE::COUNTDOWN){
        updateCountdown(elapsed);
    }else if(m_state == GAMESTATE::PLAYING){
        updatePlaying(elapsed);
    }
}

void Game::updateCountdown(const sf::Time &elapsed)
{
    m_countDownTime -= elapsed;
    if(m_countDownTime <= sf::Time::Zero){
        countdownEndedSignal.trigger();
    }
}

void Game::updatePlaying(const sf::Time &elapsed)
{
    static const float step = 1.0f / 70.0f;
    static float accumulator = 0.0f;

    float dt = elapsed.asSeconds();
    if(dt > 0.25f)
        dt = 0.25f;

    accumulator += dt;

    while(accumulator >= step){
        m_physicWorld.Step(step, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        accumulator -= step;
    }

    m_ball.update(elapsed);

    if (m_ball.getPosition().x < -BALL_RADIUS) {
        lostSignal.trigger(1);
    } else if (m_ball.getPosition().x > ARENA_WIDTH) {
        lostSignal.trigger(2);
    }
}

void Game::reset()
{
    m_ball.reset();
    m_p1.reset();
    m_p2.reset();
    m_state = GAMESTATE::COUNTDOWN;
    m_countDownTime = sf::seconds(3);
}

sf::Packet &operator<<(sf::Packet &packet, Game &game)
{
    packet << game.m_ball << game.m_p1 << game.m_p2 << static_cast<sf::Int8>(game.m_state) << game.m_countDownTime.asMicroseconds();
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Game &game)
{
    sf::Int8 gameState;
    sf::Int64 microSeconds;
    packet >> game.m_ball >> game.m_p1 >> game.m_p2 >> gameState >> microSeconds;
    game.m_state = static_cast<GAMESTATE>(gameState);
    game.m_countDownTime = sf::microseconds(microSeconds);
    return packet;
}

void Game::setGameState(GAMESTATE gameState)
{
    m_state = gameState;
}

int Game::getNumWinner() const
{
    return m_p1.isWinner() ? m_p1.getNum() : m_p2.isWinner() ? m_p2.getNum() : -1;
}

bool Game::playerWon() const
{
    return m_p1.isWinner() || m_p2.isWinner();
}

bool Game::isCountingDown() const
{
    return m_state == GAMESTATE::COUNTDOWN;
}

const Ball& Game::getBall() const
{
    return m_ball;
}

const Player& Game::getPlayer1() const
{
    return m_p1;
}

Player& Game::getPlayer1()
{
    return m_p1;
}

Player& Game::getPlayer2()
{
    return m_p2;
}

const Wall &Game::upperWall() const
{
    return m_upperWall;
}

const Wall &Game::lowerWall() const
{
    return m_lowerWall;
}

const Player& Game::getPlayer2() const
{
    return m_p2;
}

const sf::Time &Game::getCountdownTime() const
{
    return m_countDownTime;
}

b2World &Game::world() const
{
    return m_physicWorld;
}

Input &Game::input()
{
    return m_input;
}

}
