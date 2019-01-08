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
 * File:   SplashScreenState.cpp
 * Author: azarias
 *
 * Created on 5/6/2018
 */
#include <SFML/Window/Event.hpp>

#include "SplashScreenState.hpp"
#include "MenuState.hpp"

#include "src/client/Provider.hpp"
#include "src/client/StateMachine.hpp"
#include "src/client/Renderer.hpp"

namespace mp {

SplashScreenState::SplashScreenState():
    m_timer(sf::seconds(2)),
    m_games("GAMES", pr::resourceManager().get<const sf::Font&>(), 100),
    m_ema("AME", pr::resourceManager().get<const sf::Font&>(), 100),
    m_emaPos(twin::makeTwin(SF_ARENA_HEIGHT / 2.f, SF_ARENA_HEIGHT / 2.f, sf::seconds(0), twin::quadInOut )),
    m_emaScale(twin::makeTwin(1.f,1.f, sf::milliseconds(1), twin::linear))
{

    m_timer.setCallback([this](){
        m_emaPos = twin::makeTwin(SF_ARENA_HEIGHT / 2.f, SF_ARENA_HEIGHT / 2.f - 100, sf::seconds(1), twin::quadInOut);
        m_emaPos.setCallback([this](){
            m_emaScale = twin::makeTwin(1.f, -1.f, sf::seconds(1), twin::quadInOut);
        });
        m_timer.setTime(sf::seconds(5));
        m_timer.restart();

        m_timer.setCallback([](){
            pr::stateMachine().slideTo<MenuState>(SlideData::GO_RIGHT);
        });
    });

    sf::FloatRect rect = m_ema.getLocalBounds();
    m_ema.setOrigin(rect.width / 2.f, rect.height / 2.f);
    m_ema.setPosition(SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT / 2.f);

    rect = m_games.getLocalBounds();
    m_games.setOrigin(rect.width / 2.f, rect.height / 2.f);
    m_games.setPosition(SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT / 2.f);

    //SFML icon
    insertSprite(Assets::Icons::Sfml, SF_ARENA_WIDTH / 2.f - 150);
    insertSprite(Assets::Icons::Qt, SF_ARENA_WIDTH  / 2.f);
    insertSprite(Assets::Icons::Box2d, SF_ARENA_WIDTH /  2.f + 150);
}

sf::Sprite &SplashScreenState::insertSprite(const sf::Uint64 &id, float xCenter)
{
    m_sprites.emplace_back(pr::resourceManager().get<const sf::Texture&>(id));
    sf::Sprite &inserted = m_sprites.back();
    sf::Vector2f bounds(inserted.getGlobalBounds().width, inserted.getGlobalBounds().height);
    float scale = std::min(MAX_ICON_HEIGHT / bounds.y, MAX_ICON_WIDTH / bounds.x);
    inserted.setScale(scale, scale);
    bounds = {inserted.getGlobalBounds().width, inserted.getGlobalBounds().height};
    inserted.setOrigin(0, inserted.getLocalBounds().height);
    inserted.setPosition(xCenter , SF_ARENA_HEIGHT - 50);
    return inserted;
}

void SplashScreenState::update(const sf::Time &elapsed)
{
    if(!pr::stateMachine().currentIs<SplashScreenState>())return;

    m_timer.update(elapsed);
    m_emaPos.step(elapsed);
    m_ema.setPosition(m_ema.getPosition().x, m_emaPos.get());
    m_emaScale.step(elapsed);
    m_ema.setScale(m_emaScale.get(), 1);
}

void SplashScreenState::render(Renderer &renderer) const
{
    for(const auto &it : m_sprites)
        renderer.draw(it);

    renderer
            .draw(m_games)
            .draw(m_ema);
}

void SplashScreenState::handleEvent(const sf::Event &ev)
{    
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::stateMachine().slideTo<MenuState>(SlideData::GO_RIGHT);
    }
}


}

