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
 * File:   Game.cpp
 * Author: azarias
 * 
 * Created on 11 octobre 2017, 10:09
 */

#include "Game.hpp"
#include "Application.hpp"

Game::Game() :
mainBall(*this),
p1(*this, 1),
p2(*this, 2),
m_countDownTime(sf::seconds(3)),
m_state(GAMESTATE::COUNTDOWN)
{
}

Game::~Game()
{
}

void Game::handleEvent(const sf::Event& ev, Player &player)
{
	mutex.lock();
	if (ev.type == sf::Event::KeyPressed) {
		if (ev.key.code == sf::Keyboard::Up) {
			player.getPaddle().goUp();
		} else if (ev.key.code == sf::Keyboard::Down) {
			player.getPaddle().goDown();
		}
	} else if (ev.type == sf::Event::KeyReleased) {
		player.getPaddle().stop();
	}
	mutex.unlock();
}

void Game::update(const sf::Time &elapsed)
{
	mutex.lock();
	p1.getPaddle().update(elapsed);
	p2.getPaddle().update(elapsed);
	if(m_state == GAMESTATE::COUNTDOWN){
		updateCountdown(elapsed);
	}else if(m_state == GAMESTATE::PLAYING){
		updatePlaying(elapsed);
	}
	mutex.unlock();
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
	mainBall.update(elapsed);

	if (p1.getPaddle().intersectsWith(mainBall)) {
		float bounceDir = p1.getPaddle().getBounceAngle(mainBall.getPosition().y + BALL_RADIUS / 2);
		mainBall.xBounce(bounceDir);
		m_evManager.trigger(bounceEvent, 1, sf::Vector2f(p1.getPaddle().getPosition().x + PADDLE_WIDTH, mainBall.getPosition().y + (BALL_RADIUS / 2.f) ) );
	} else if (p2.getPaddle().intersectsWith(mainBall)) {
		float bounceDir = p2.getPaddle().getBounceAngle(mainBall.getPosition().y + BALL_RADIUS / 2);
		mainBall.xBounce(bounceDir);
		m_evManager.trigger(bounceEvent, 2, sf::Vector2f(p2.getPaddle().getPosition().x + PADDLE_WIDTH, mainBall.getPosition().y + (BALL_RADIUS / 2.f) ));
	}

	if (mainBall.getPosition().x < -BALL_RADIUS) {
		m_evManager.trigger(lostEvent, 1);//Player 1 lost
	} else if (mainBall.getPosition().x > 750) {
		m_evManager.trigger(lostEvent, 2);
	}
}

void Game::reset()
{
	mutex.lock();
	mainBall.reset();
	p1.reset();
	p2.reset();
	m_state = GAMESTATE::COUNTDOWN;
	m_countDownTime = sf::seconds(3);
	mutex.unlock();
}

sf::Packet &operator<<(sf::Packet &packet, Game &game)
{
	game.mutex.lock();
	packet << game.mainBall << game.p1 << game.p2 << static_cast<sf::Int8>(game.m_state) << game.m_countDownTime.asMicroseconds();
	game.mutex.unlock();
	return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Game &game)
{
	sf::Int8 gameState;
	sf::Int64 microSeconds;
	game.mutex.lock();
	packet >> game.mainBall >> game.p1 >> game.p2 >> gameState >> microSeconds;
	game.m_state = static_cast<GAMESTATE>(gameState);
	game.m_countDownTime = sf::microseconds(microSeconds);
	game.mutex.unlock();
	return packet;
}

void Game::setPaddle2Position(const sf::Vector2f &p2PaddlePos)
{
	mutex.lock();
	p2.getPaddle().setPosition(p2PaddlePos);
	mutex.unlock();
}

void Game::setPaddle1Position(const sf::Vector2f& p1Pos)
{
	mutex.lock();
	p1.getPaddle().setPosition(p1Pos);
	mutex.unlock();
}

void Game::setGameState(GAMESTATE gameState)
{
	mutex.lock();
	m_state = gameState;
	mutex.unlock();
}

int Game::getNumWinner() const
{
	mutex.lock();
	int res = p1.isWinner() ? p1.getNum() : p2.isWinner() ? p2.getNum() : -1;
	mutex.unlock();
	return res;
}

bool Game::playerWon() const
{
	mutex.lock();
	bool won = p1.isWinner() || p2.isWinner();
	mutex.unlock();
	return won;
}

bool Game::isCountingDown() const
{
    mutex.lock();
    bool countingDown = m_state == GAMESTATE::COUNTDOWN;
    mutex.unlock();
    return countingDown;
}

const Ball& Game::getBall() const
{
	const Ball *b;
	mutex.lock();
	b = &mainBall;
	mutex.unlock();
	return *b;
}

const Player& Game::getPlayer1() const
{
	const Player *p;
	mutex.lock();
	p = &p1;
	mutex.unlock();
	return *p;
}

Player& Game::getPlayer1()
{
	Player *p;
	mutex.lock();
	p = &p1;
	mutex.unlock();
	return *p;
}

Player& Game::getPlayer2()
{
	Player *p;
	mutex.lock();
	p = &p2;
	mutex.unlock();
	return *p;
}

const Player& Game::getPlayer2() const
{
	const Player *p;
	mutex.lock();
	p = &p2;
	mutex.unlock();
	return *p;
}

sf::Time Game::getCountdownTime() const
{
    mutex.lock();
    sf::Time timeCopy = m_countDownTime;
    mutex.unlock();
    return timeCopy;
}

EventManager& Game::getEventManager()
{
	mutex.lock();
	EventManager &evM = m_evManager;
	mutex.unlock();
	return evM;
}
