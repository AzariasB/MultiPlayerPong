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
 * File:   Loading.cpp
 * Author: azarias
 *
 * Created on 14/7/2018
 */
#include "Loading.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/ClientConf.hpp"
#include "src/common/Math.hpp"

namespace mp {

Loading::Loading(const sf::Vector2f &center, float width):
    m_timer(sf::milliseconds(500), true)
{
    float step = width / SQUARES;
    sf::Vector2f startPos(center.x - width / 2.f, center.y);
    for(std::size_t i = 0; i < SQUARES; ++i){
       m_squares[i].setPosition(startPos);
       startPos.x += step;
    }

    m_timer.setCallback([this](){nextSquare();});
}

void Loading::setState(LD_STATE nwState)
{
    m_state = nwState;
    m_timer.setTime(sf::milliseconds(nwState == LD_INACTIVE ? 500 : 100 ));
}

void Loading::nextSquare()
{
    m_currentSquare = (m_currentSquare + 1) % m_squares.size();
    m_squares[m_currentSquare].on(m_state == LD_ACTIVE);
}

void Loading::render(Renderer &renderer) const
{
    for(const Square &s : m_squares)
        s.render(renderer);
}

bool Loading::update(const sf::Time &delta)
{
    m_timer.update(delta);
    for(Square &s : m_squares) s.update(delta);
    return true;
}

bool Loading::handleEvent(const sf::Event&)
{
    return false;
}

Loading::Square::Square():
    m_color(sf::Color::White)
{
}

Loading::Square::Square(const sf::Vector2f &center):
    m_innerRect(sf::Vector2f(SQ_SIDE, SQ_SIDE)),
    m_color(sf::Color::White)
{
    setPosition(center);
}

void Loading::Square::setPosition(const sf::Vector2f &center)
{
    m_innerRect.setPosition(center);
    math::centerOrigin(m_innerRect);
}

void Loading::Square::off(bool fast)
{
    m_color = ColorTweening(m_color.get(), sf::Color::White, sf::seconds(fast ? 0.3f : 0.5f), twin::easing::linear);
}

void Loading::Square::on(bool fast)
{
    m_color = ColorTweening(m_color.get(), cc::Colors::endWinColor[0], sf::seconds(fast ? 0.2f : 0.5f), twin::easing::quartOut, [this, fast](){off(fast);});
}

void Loading::Square::update(const sf::Time &delta)
{
    m_color.update(delta);
    m_innerRect.setFillColor(m_color.get());
}

void Loading::Square::render(Renderer &renderer) const
{
    renderer.draw(m_innerRect);
}


}
