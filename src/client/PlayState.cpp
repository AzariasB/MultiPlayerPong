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
 * File:   PlayState.cpp
 * Author: azarias
 * 
 * Created on 16 octobre 2017, 17:49
 */

#include "PlayState.hpp"
#include "ClientApp.hpp"

PlayState::PlayState(ClientApp& client) :
State(client),
listeningThread(&PlayState::listenSocket, this),
m_p1ScoreText("0", client.getResourcesManager().getFont()),
m_p2ScoreText("0", client.getResourcesManager().getFont()),
m_countdownText("3", client.getResourcesManager().getFont())
{
	getApp().getGame().getEventManager()
		.declareListener(
	                        getApp().getGame().bounceEvent,
				&PlayState::bounced,
				this
			); //Subscribe to bounce event

	m_p1ScoreText.setPosition(ARENA_WIDTH / 4 - m_p1ScoreText.getGlobalBounds().width, 0);
	m_p2ScoreText.setPosition((ARENA_WIDTH / 4)*3 - m_p2ScoreText.getGlobalBounds().width , 0);
	m_countdownText.setPosition(
				ARENA_WIDTH / 2  - m_countdownText.getGlobalBounds().width,
				ARENA_HEIGHT / 2 - m_countdownText.getGlobalBounds().height
	);
}

PlayState::~PlayState()
{
}

void PlayState::bounced(int pNum, sf::Vector2f position)
{
	getApp().getSoundEngine().playSound(SoundEngine::BOUNCE);
	getApp().getParticleGenerator().explode(position);//get position
	getApp().getRenderer().shake();
}

void PlayState::draw(Renderer& renderer) const
{
	if(getApp().getGame().isCountingDown()){
		renderer.render(m_countdownText);
	}

	renderer.renderBall(getApp().getGame().getBall());
	renderer.renderPaddle(getApp().getGame().getPlayer1().getPaddle());
	renderer.renderPaddle(getApp().getGame().getPlayer2().getPaddle());

	renderer.render(m_p1ScoreText);
	renderer.render(m_p2ScoreText);

	renderer.render(getApp().getParticleGenerator());
}

void PlayState::handleEvent(const sf::Event& ev)
{
	sf::Event realEv = getApp().getKeyBindings().toGameEvent(ev);

	getApp().getGame().handleEvent(realEv, getApp().getPlayer());
	if (realEv.type == sf::Event::KeyPressed || realEv.type == sf::Event::KeyReleased) {
		sf::Packet p;
		p << realEv.type << realEv.key.code;
		getApp().getSocket().send(p);
	}
}

void PlayState::update(const sf::Time &elapsed)
{
	if (getApp().getGame().playerWon())
		getApp().getStateMachine().setCurrentState(STATE_TYPE::FINISHED);
	else
		getApp().getGame().update(elapsed);

	getApp().getParticleGenerator().update(elapsed);
	m_p1ScoreText.setString(
		sf::String(
		std::to_string(getApp().getGame().getPlayer1().getScore())
		)
		);
	m_p2ScoreText.setString(
		sf::String(
		std::to_string(getApp().getGame().getPlayer2().getScore())
		)
		);
	m_countdownText.setString(
				std::to_string(1 + (int)getApp().getGame().getCountdownTime().asSeconds())
				);

}

void PlayState::onEnter(BaseStateData *data)
{
	listeningThread.launch();
}

void PlayState::onLeave()
{
	listeningThread.terminate();
}

void PlayState::listenSocket()
{
	while (1) {
		sf::Packet p;
		sf::Socket::Status rcvStatus = getApp().getSocket().receive(p);
		if (rcvStatus == sf::Socket::Done) {
			p >> getApp().getGame();
		} else if (rcvStatus == sf::Socket::Disconnected) {
			//Send message to main thread
		}
	}
}
