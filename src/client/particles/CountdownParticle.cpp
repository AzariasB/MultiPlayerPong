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
 * File:   CoundtownParticle.cpp
 * Author: azarias
 *
 * Created on 2/5/2018
 */
#include "CountdownParticle.hpp"

#include "src/client/Provider.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/ResourcesManager.hpp"

#include "src/common/VectorsUtils.hpp"

namespace mp {

CountdownParticle::CountdownParticle():
    Particle(PARTICLE_TYPE::Countdown)
{
}

void CountdownParticle::init(const std::string &text, const sf::Vector2f &position, const sf::Time &lifetime)
{
    m_textScale = twin::makeTwin(0.1f, 1.f, lifetime, twin::linear);
    m_textAlpha = twin::makeTwin((sf::Uint8)255, (sf::Uint8)0, lifetime, twin::linear);
    m_text = sf::Text(text, pr::resourceManager().getFont(), 60);
    math::centerOrigin(m_text).setPosition(position);
    m_textColor = m_text.getFillColor();
}

void CountdownParticle::update(const sf::Time &elapsed)
{
    m_textScale.step(elapsed);
    m_textAlpha.step(elapsed);
    m_textColor.a = m_textAlpha.get();
    m_text.setFillColor(m_textColor);
}

void CountdownParticle::render(Renderer &renderer) const
{
    renderer
            .push()
            .scale(P_TO_M)
            .translate(m_text.getPosition())
            .scale(m_textScale.get())
            .translate(-m_text.getPosition())
            .draw(m_text)
            .pop();
}

bool CountdownParticle::isFinished() const
{
    return m_textScale.progress() == 1.f;
}

}
