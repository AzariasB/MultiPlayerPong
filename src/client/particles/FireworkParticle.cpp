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
 * File:   Fireworkparticle.cpp
 * Author: azarias
 *
 * Created on 08/05/2019
 */

#include "FireworkParticle.hpp"
#include "src/client/Renderer.hpp"
#include "src/common/Config.hpp"

namespace mp {

FireworkParticle::FireworkParticle():
    Particle (this),
    m_line(sf::PrimitiveType::Lines, 2)
{
}

const sf::Vector2f &FireworkParticle::getExplosionPosition() const
{
    return m_target;
}

void FireworkParticle::init(const sf::Vector2f &target, const sf::Time &climbTime)
{
    m_target = target;
    const sf::Time added = sf::milliseconds(static_cast<sf::Int32>(ARENA_HEIGHT - target.y)) * ARENA_HEIGHT;
    m_length = twin::makeTwin(10.f, 0.f, added + climbTime, twin::easing::quadIn);
    m_yPos = twin::makeTwin(ARENA_HEIGHT, target.y, added + climbTime, twin::easing::quadOut);

    m_line[0] = sf::Vertex(sf::Vector2f(m_target.x, ARENA_HEIGHT), sf::Color::White);
    m_line[1] = sf::Vertex(sf::Vector2f(m_target.x, ARENA_HEIGHT) , sf::Color::Transparent);
}

bool FireworkParticle::isFinished() const
{
    return m_yPos.progress() == 1.f;
}

void FireworkParticle::render(Renderer &renderer) const
{
    renderer.draw(m_line);
}

void FireworkParticle::update(const sf::Time &elapsed)
{
    m_length.step(elapsed);
    m_yPos.step(elapsed);
    const float yPos = m_yPos.get();

    m_line[0].position.y = yPos;
    m_line[1].position.y = yPos + m_length.get();
}




}
