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
 * File:   PlayState.cpp
 * Author: azarias
 *
 * Created on 12/03/2018
 */

#include "PlayState.hpp"
#include "PlayMultiplayerState.hpp"
#include "PlaySoloState.hpp"
#include "PauseState.hpp"
#include "EndState.hpp"

#include "src/common/Game.hpp"
#include "src/common/Config.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/SoundEngine.hpp"
#include "src/client/StateMachine.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/particles/ParticleGenerator.hpp"


namespace mp {

PlayState::PlayState():
    m_p1ScoreText("0", pr::resourceManager().get<const sf::Font&>()),
    m_p2ScoreText("0", pr::resourceManager().get<const sf::Font&>()),
    m_nextParticle(cc::Times::trailCountdownTime, true)
{
    m_p1ScoreText.setPosition(SF_ARENA_WIDTH / 4 - m_p1ScoreText.getGlobalBounds().width, 0);
    m_p2ScoreText.setPosition((SF_ARENA_WIDTH / 4)*3 - m_p2ScoreText.getGlobalBounds().width , 0);

    m_nextParticle.setCallback([this](){
        m_particleGenerator.ballTrail(b2VecToSfVect(pr::game().getBall().getPosition()));
    });
}

void PlayState::onBeforeEnter()
{
    pr::game().hitPaddleSignal.add([this](std::size_t pNum, b2Vec2 position){
        Q_UNUSED(pNum);
        pr::soundEngine().playSound(Assets::Sounds::Bounce);

        sf::Vector2f gainPointPos = m_p1ScoreText.getPosition();
        if(pNum == 2){
            gainPointPos = m_p2ScoreText.getPosition();
        }
        gainPointPos.x -= 30.f;
        gainPointPos.y += 30.f;

        m_particleGenerator.gainPoint(gainPointPos );
        m_particleGenerator.explode(b2VecToSfVect(position));
        pr::renderer().shake();
    });


}

void PlayState::update(const sf::Time &elapsed)
{
    if(!pr::stateMachine().currentIs<PlayMultiplayerState>()
        && !pr::stateMachine().currentIs<PlaySoloState>()) return;

    if (pr::game().playerWon()){
        pr::stateMachine().slideTo<EndState>(SlideData::GO_UP);
        return;
    }


    pr::game().update(elapsed);

    m_nextParticle.update(elapsed);
    m_p1ScoreText.setString(std::to_string(pr::game().getPlayer1().getScore()));
    m_p2ScoreText.setString(std::to_string(pr::game().getPlayer2().getScore()));

    if(pr::game().isCountingDown()){
        int secs = static_cast<int>(pr::game().getCountdownTime().asSeconds());
        if( m_lastCountdownValue != secs){
            m_lastCountdownValue = secs;
            m_particleGenerator.countdown(std::to_string( m_lastCountdownValue + 1), sf::Vector2f(SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT / 3.f));
            pr::soundEngine().playSound(Assets::Sounds::PingPong8bitBeeep);
        }
    }else if(m_lastCountdownValue == 0){
        m_lastCountdownValue = -1;
        m_particleGenerator.countdown("Go !", sf::Vector2f(SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT / 3.f));
        pr::soundEngine().playSound(Assets::Sounds::PingPong8bitBiiip);
    }
    m_particleGenerator.update(elapsed);
}

void PlayState::onAfterLeaving()
{
    if(!pr::stateMachine().currentIs<PauseState>())
        m_particleGenerator.clear();
    pr::game().hitPaddleSignal.clear();
}

void PlayState::render(Renderer &renderer) const
{
    renderer.push()
            .scale(M_TO_P)
            .render(m_particleGenerator)
            .renderBall(pr::game().getBall())
            .renderPaddle(pr::game().getPlayer1().getPaddle())
            .renderPaddle(pr::game().getPlayer2().getPaddle())
            .renderWall(pr::game().upperWall())
            .renderWall(pr::game().lowerWall())
            .pop()
            .draw(m_p1ScoreText)
            .draw(m_p2ScoreText);

}

PlayState::~PlayState()
{
}

void PlayState::handleEvent(const sf::Event &ev)
{
    pr::game().handleEvent(ev);
}


}
