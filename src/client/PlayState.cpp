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

#include <qglobal.h>
#include <SFML/Network/IpAddress.hpp>

#include "PlayState.hpp"
#include "Provider.hpp"
#include "ClientApp.hpp"

PlayState::PlayState() :
    listeningThread(&PlayState::listenSocket, this),
    m_p1ScoreText("0", pr::resourceManager().getFont()),
    m_p2ScoreText("0", pr::resourceManager().getFont()),
    m_countdownText("3", pr::resourceManager().getFont())
{
    pr::connect(
                pr::game().bounceEvent,
                &PlayState::bounced,
                this
                ); //Subscribe to bounce event

    m_p1ScoreText.setPosition(SF_ARENA_WIDTH / 4 - m_p1ScoreText.getGlobalBounds().width, 0);
    m_p2ScoreText.setPosition((SF_ARENA_WIDTH / 4)*3 - m_p2ScoreText.getGlobalBounds().width , 0);
    m_countdownText.setPosition(
                SF_ARENA_WIDTH / 2  - m_countdownText.getGlobalBounds().width,
                SF_ARENA_HEIGHT / 2 - m_countdownText.getGlobalBounds().height
                );
}

PlayState::~PlayState()
{
}

void PlayState::bounced(int pNum, sf::Vector2f position)
{
    Q_UNUSED(pNum);
    pr::soundEngine().playSound(SoundEngine::BOUNCE);
    pr::particleGenerator().explode(position);//get position
    pr::renderer().shake();
}

void PlayState::draw(Renderer& renderer) const
{
    if(pr::game().isCountingDown()){
        renderer.render(m_countdownText);
    }

    renderer.renderBall(pr::game().getBall());
    renderer.renderPaddle(pr::game().getPlayer1().getPaddle());
    renderer.renderPaddle(pr::game().getPlayer2().getPaddle());
    renderer.renderWall(pr::game().upperWall());
    renderer.renderWall(pr::game().lowerWall());

    renderer.render(m_p1ScoreText);
    renderer.render(m_p2ScoreText);

    const std::unordered_map<sf::Uint64, Powerup> &powerups = pr::game().getPowerups();
    for(auto it = powerups.begin(); it != powerups.end(); ++it){
        renderer.renderPowerup(it->second);
    }

    renderer.render(pr::particleGenerator());
}

void PlayState::handleEvent(const sf::Event& ev)
{
    sf::Event realEv = pr::keyBinding().toGameEvent(ev);

    pr::game().handleEvent(realEv, pr::player());
    if (realEv.type == sf::Event::KeyPressed || realEv.type == sf::Event::KeyReleased) {
        sf::Packet p;
        p << realEv.type << realEv.key.code;
        pr::socket().send(p);
    }
}

void PlayState::update(const sf::Time &elapsed)
{
    if (pr::game().playerWon())
        pr::stateMachine().setCurrentState(STATE_TYPE::FINISHED);
    else
        pr::game().update(elapsed);

    pr::particleGenerator().update(elapsed);
    m_p1ScoreText.setString(std::to_string(pr::game().getPlayer1().getScore()));
    m_p2ScoreText.setString(std::to_string(pr::game().getPlayer2().getScore()));
    m_countdownText.setString(std::to_string(1 + (int)pr::game().getCountdownTime().asSeconds()));

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
        if(pr::socket().getRemoteAddress() == sf::IpAddress::None){
            std::cerr << "Socket is null \n";
            return;
        }
        sf::Socket::Status rcvStatus = pr::socket().receive(p);
        if (rcvStatus == sf::Socket::Done) {
            p >> pr::game();
        } else if (rcvStatus == sf::Socket::Disconnected) {
            //Send message to main thread
        }
    }
}
