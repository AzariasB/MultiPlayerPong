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
 * File:   EndState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:50
 */
#include "EndState.hpp"
#include "src/client/ClientApp.hpp"
#include "src/common/Math.hpp"
#include "src/client/Provider.hpp"
#include "src/client/widgets/Dialog.hpp"
#include "src/client/ClientConf.hpp"
#include "MenuState.hpp"

namespace mp {

EndState::EndState():
    m_menu(),
    m_content(*m_menu.addLabel("",0,0)),
    m_buffer(sf::PrimitiveType::Triangles, triangleNumber * 3),
    m_angle(0.f)
{
    m_menu.addCenteredLabel("finished", SF_CENTER_X, SF_ARENA_HEIGHT / 4.f, 60);

    m_menu.addButton("menu", SF_CENTER_X, 3*SF_ARENA_HEIGHT/4, Assets::IconAtlas::exitLeftIcon)
            .clickedSignal
            .add([this](){goToMenu(); });
    m_menu.normalizeButtons(10);
    pr::translator().translationChangedSignal.add([this](){
        m_menu.normalizeButtons(10);
    });
}

EndState::~EndState()
{
}

sf::Vector2f EndState::toVertexPosition(std::size_t index) const
{
    float angle = (2 * static_cast<float>(M_PI)) * (index / static_cast<float>(triangleNumber));
    return sf::Vector2f(
                std::cos(angle) * SF_CENTER_X + SF_CENTER_X,
                std::sin(angle) * SF_CENTER_X + SF_CENTER_Y
            );
}

void EndState::updateVerticesColor(bool win)
{
    m_buffer.clear();
    sf::Vector2f center(SF_CENTER_X, SF_CENTER_Y);
    for(std::size_t i = 0; i < triangleNumber; ++i){
        sf::Color centerColor = win ? cc::Colors::endWinColor[i&1] : cc::Colors::endLoseColor[i&1];
        sf::Color outColor = centerColor;
        outColor.a = 0;
        m_buffer.append({center, centerColor});
        m_buffer.append({toVertexPosition(i), outColor});
        m_buffer.append({toVertexPosition(i+1), outColor});
    }

}

void EndState::goToMenu()
{
    pr::stateMachine().slideTo<MenuState>(cc::SLIDE_DIRECTION::SLIDE_RIGHT);
}

void EndState::render(Renderer& renderer) const
{
    static const sf::Vector2f centerPoint(SF_CENTER_X, SF_CENTER_Y);
    renderer.push()
            .scale(m_scale.get(), centerPoint)
            .rotateAround(centerPoint, m_angle)
            .draw(m_buffer)
            .pop()
            .push()
            .scale(M_TO_P)
            .blend(sf::BlendAdd)
            .render(m_particleGenerator)
            .pop()
            .render(m_menu);
}


void EndState::handleEvent(const sf::Event& ev)
{
    //When escape pressed, go to menu
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        goToMenu();
    }else{
        m_menu.handleEvent(ev);
    }
}

void EndState::onBeforeEnter()
{
    m_scale = twin::makeTwin(0.f, 1.f, sf::milliseconds(1000), twin::easing::circOut);
    m_particleGenerator.clear();
}

void EndState::onEnter(int playerNum)
{
    GAME_MODE gm = pr::game().gameMode();
    if(gm == GAME_MODE::SOLO_1V1){
        pr::soundEngine().playSound(Assets::Sounds::Win);
        int numWinner = pr::game().getNumWinner().value_or(0);
        sf::String res = "Player " + std::to_string(numWinner) + " ";
        auto winnerPlayer = pr::game().getWinner();
        sf::String score = "";
        if(winnerPlayer.has_value()){
            score = "\n Score : " + std::to_string(winnerPlayer->get().getScore());
        }
        m_content.setString({res, "won", score});
        updateVerticesColor(true);
    } else {
        int numWinner = pr::game().getNumWinner().value_or(0);
        bool winner = numWinner == playerNum;
        const Player& p = playerNum == 1 ? pr::game().getPlayer1() : pr::game().getPlayer2();
        std::string yourScore =  " \n Score : " + std::to_string(p.getScore());
        pr::soundEngine().playSound(winner ? Assets::Sounds::Win : Assets::Sounds::Loose);
        updateVerticesColor(winner);
        m_content.setString({winner ? "you_won" : "you_lost", yourScore});
    }
    math::centerOrigin(m_content);
    m_content.setPosition(SF_CENTER_X, SF_CENTER_Y);
    pr::game().reset();
}

void EndState::update(const sf::Time &elapsed)
{
    if(!pr::stateMachine().currentIs<EndState>()) return;
    m_menu.update(elapsed);
    m_angle += elapsed.asSeconds();
    m_scale.step(elapsed);
    if(m_particleGenerator.update(elapsed)){
        pr::soundEngine().playSound(Assets::Sounds::Firework3);
    }

    int explode = math::rrand(0,100);
    if(explode == 0){
        float xPos = math::rrand(0, static_cast<int>(ARENA_WIDTH));
        float yPos = math::rrand(0, static_cast<int>(ARENA_HEIGHT));
        m_particleGenerator.firework(sf::Vector2f(xPos, yPos));
        pr::soundEngine().playSound(Assets::Sounds::Firework2);
    }
}

}

