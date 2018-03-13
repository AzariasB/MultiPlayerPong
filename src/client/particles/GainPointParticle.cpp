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
 * File:   GainPointParticle.cpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#include <SFML/System/Time.hpp>

#include "src/client/Provider.hpp"
#include "GainPointParticle.hpp"

GainPointParticle::GainPointParticle(const sf::Vector2f &position, const sf::Time &lifeTime):
    Particle(),
    m_positionTwin(twin::makeTwin(position.y, position.y - 5.f, lifeTime.asMilliseconds(), twin::linear)),
    m_alphaTwin(twin::makeTwin(static_cast<sf::Uint8>(0), static_cast<sf::Uint8>(255), lifeTime.asMilliseconds(), twin::linear ))
{

}

bool GainPointParticle::isFinished() const
{
    return m_positionTwin.progress() == 1.f;
}

void GainPointParticle::render(Renderer &renderer) const
{
    renderer.render(m_text);
}

void GainPointParticle::update(const sf::Time &elapsed)
{
    m_positionTwin.step(elapsed.asMilliseconds());
    m_alphaTwin.step(elapsed.asMilliseconds());

    sf::Color textColor = m_text.getColor();
    textColor.a = m_alphaTwin.get();
    m_text.setColor(textColor);
    m_text.setPosition(m_text.getPosition().x, m_positionTwin.get());
}
