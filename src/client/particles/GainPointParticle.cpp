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
 * File:   GainPointParticle.cpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#include <SFML/System/Time.hpp>

#include "src/common/Math.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/Renderer.hpp"
#include "GainPointParticle.hpp"


namespace mp {

GainPointParticle::GainPointParticle():
    Particle(this)
{
}

void GainPointParticle::init(const sf::Vector2f &position, const sf::Time &lifetime)
{
    m_positionTwin = twin::makeTwin(position.y, position.y - 20.f, lifetime, twin::linear);
    m_alphaTwin = twin::makeTwin((sf::Uint8)255, (sf::Uint8)0, lifetime, twin::linear);
    m_text = sf::Text("+1", pr::resourceManager().get(Assets::Fonts::Quicksand), 20);
    m_text.setPosition(position);
}

bool GainPointParticle::isFinished() const
{
    return m_positionTwin.progress() == 1.f &&
            m_alphaTwin.progress() == 1.f;
}

void GainPointParticle::render(Renderer &renderer) const
{
    renderer
            .push()
            .scale(P_TO_M)
            .draw(m_text)
            .pop();
}

void GainPointParticle::update(const sf::Time &elapsed)
{
    m_positionTwin.step(elapsed);
    m_alphaTwin.step(elapsed);

    sf::Color textColor = m_text.getFillColor();
    textColor.a = m_alphaTwin.get();
    m_text.setFillColor(textColor);
    m_text.setPosition(m_text.getPosition().x, m_positionTwin.get());
}


}
