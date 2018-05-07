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
 * File:   Game.cpp
 * Author: azarias
 *
 * Created on 11 octobre 2017, 10:09
 */

#include <iostream>
#include "Game.hpp"
#include "Application.hpp"


namespace mp {

Game::Game() :
    mPhysicWorld(mGravity),
    mainBall(*this),
    p1(*this, 1),
    p2(*this, 2),
    mUpperWall(*this, b2Vec2(WALL_WITDH/2.f,WALL_HEIGHT/2.f)),
    mLowerWall(*this, b2Vec2(WALL_WITDH/2.f , ARENA_HEIGHT - (WALL_HEIGHT/2.f))),
    m_countDownTime(sf::seconds(3)),
    m_state(GAMESTATE::COUNTDOWN),
    mContactListener(m_evManager)
{
    mPhysicWorld.SetContactListener(&mContactListener);
    m_evManager.declareListener(mContactListener.ballHitPaddleEvent, &Game::paddleHit, this);
}

Game::~Game()
{
}

void Game::paddleHit(std::size_t pNum, b2Vec2 position)
{
    m_evManager.trigger(hitPaddleEvent, pNum, position);
}

void Game::handleEvent(const sf::Event& ev, Player &player)
{
    if (ev.type == sf::Event::KeyPressed) {
        if (ev.key.code == sf::Keyboard::Up) {
            player.getPaddle().goUp();
        } else if (ev.key.code == sf::Keyboard::Down) {
            player.getPaddle().goDown();
        }
    } else if (ev.type == sf::Event::KeyReleased) {
        player.getPaddle().stop();
    }
}

void Game::update(const sf::Time &elapsed)
{
    p1.getPaddle().update(elapsed);
    p2.getPaddle().update(elapsed);
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
        m_evManager.trigger(countdownEndedEvent);
    }
}

void Game::updatePlaying(const sf::Time &elapsed)
{
    static const double step = 1.0 / 70.0;
    static double accumulator = 0.f;

    float dt = elapsed.asSeconds();
    if(dt > 0.25)
        dt = 0.25;

    accumulator += dt;

    while(accumulator >= step){
        mPhysicWorld.Step(step, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
        accumulator -= step;
    }

    mainBall.update(elapsed);

    if (mainBall.getPosition().x < -BALL_RADIUS) {
        m_evManager.trigger(lostEvent, 1);//Player 1 lost
    } else if (mainBall.getPosition().x > ARENA_WIDTH) {
        m_evManager.trigger(lostEvent, 2);
    }

    for(auto it = m_powerups.begin(); it != m_powerups.end();){
        Powerup &powerup = it->second;
        if(powerup.isHidden())
            continue;
        powerup.update(elapsed);
        if(powerup.isOut() && !powerup.timerStarted()){
            it = m_powerups.erase(it);
        }else{
            ++it;
        }
    }
}

const Powerup &Game::addPowerUp(Powerup::POWERUP_TYPE type, const sf::Vector2f &startPos, const sf::Vector2f &direction)
{
    sf::Uint64 key = Powerup::nextId();
    auto pair = m_powerups.emplace(std::piecewise_construct,
                                   std::forward_as_tuple(key),
                                   std::forward_as_tuple(*this, type, startPos, direction)
                                   );
#ifdef SERVER
    if(pair.second){
        mw_nwPowerups.emplace_back(&pair.first->second);
        //m_evManager.declareListener(pair.first->second.hitPaddle, &Game::powerupHitPaddle, this, pair.first->first);
    }
#endif
    return m_powerups.find(key)->second;
}

void Game::clearNewPowerUps()
{
    mw_nwPowerups.clear();;
}


void Game::powerupHitPaddle(sf::Uint64 powerUpId, int paddleNum)
{
    auto it = m_powerups.find(powerUpId);
    if(it == m_powerups.end())return;

    Powerup &   powerup = (*it).second;
    Player &affected = paddleNum == 1 ? p1 : p2;
    switch(powerup.getType()){
    case Powerup::BALL_EXTEND:
        mainBall.extend();
        break;
    case Powerup::BALL_RETRACT:
        mainBall.retract();
        break;
    case Powerup::PADDLE_EXTEND:
        affected.getPaddle().extend();
        break;
    case Powerup::PADDLE_RETRACT:
        affected.getPaddle().retract();
        break;
    }
    powerup.startTimer();
    auto pair = std::make_pair(powerUpId, paddleNum);
    getEventManager().declareListener(powerup.effectFinished, &Game::powerupEffectFinished, this, pair);
    //stop rendering the powerup (but keep it in memory ...)
}

void Game::powerupEffectFinished(std::pair<sf::Uint64, int> data)
{
    sf::Uint64 powerupId = data.first;
    int paddleNum = data.second;

    auto it = m_powerups.find(powerupId);
    if(it == m_powerups.end())return;

    Powerup &powerup = (*it).second;
    switch(powerup.getType()){
    case Powerup::BALL_EXTEND:
    case Powerup::BALL_RETRACT:
        mainBall.resetPowerup(powerup.getType());
        break;
    case Powerup::PADDLE_EXTEND:
    case Powerup::PADDLE_RETRACT:
        Player &affected = paddleNum == 1 ? p1 : p2;
        affected.getPaddle().resetPowerupEffect(powerup.getType());
        break;
    }

    m_powerups.erase(powerupId);
}

void Game::reset()
{
    mainBall.reset();
    p1.reset();
    p2.reset();
    m_state = GAMESTATE::COUNTDOWN;
    m_countDownTime = sf::seconds(3);
    m_powerups.clear();
    mw_nwPowerups.clear();
}

sf::Packet &operator<<(sf::Packet &packet, Game &game)
{
    packet << game.mainBall << game.p1 << game.p2 << static_cast<sf::Int8>(game.m_state) << game.m_countDownTime.asMicroseconds();
    packet <<(sf::Uint32) game.mw_nwPowerups.size();
    for(size_t i = 0; i < game.mw_nwPowerups.size(); ++i){
        packet << *game.mw_nwPowerups[i];
    }
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Game &game)
{
    sf::Int8 gameState;
    sf::Int64 microSeconds;
    packet >> game.mainBall >> game.p1 >> game.p2 >> gameState >> microSeconds;
    deserialize(packet, game.m_powerups, game);
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
    return p1.isWinner() ? p1.getNum() : p2.isWinner() ? p2.getNum() : -1;
}

bool Game::playerWon() const
{
    return p1.isWinner() || p2.isWinner();
}

bool Game::isCountingDown() const
{
    return m_state == GAMESTATE::COUNTDOWN;
}

const Ball& Game::getBall() const
{
    return mainBall;
}

const Player& Game::getPlayer1() const
{
    return p1;
}

Player& Game::getPlayer1()
{
    return p1;
}

Player& Game::getPlayer2()
{
    return p2;
}

const Wall &Game::upperWall() const
{
    return mUpperWall;
}

const Wall &Game::lowerWall() const
{
    return mLowerWall;
}

const Player& Game::getPlayer2() const
{
    return p2;
}

const sf::Time &Game::getCountdownTime() const
{
    return m_countDownTime;
}

b2World &Game::world() const
{
    return mPhysicWorld;
}

EventManager& Game::getEventManager()
{
    return m_evManager;
}

const std::unordered_map<sf::Uint64, Powerup> &Game::getPowerups() const
{
    return m_powerups;
}

}
