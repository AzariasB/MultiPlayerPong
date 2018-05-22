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

namespace mp {

CountdownParticle::CountdownParticle(const std::string &text, const sf::Vector2f &positon):
    Particle(),
    m_textSize(twin::makeTwin(10, 50, 1000.f, twin::linear)),
    m_textAlpha(twin::makeTwin(255, 0, 1000.f, twin::linear)),
    m_text(text, pr::resourceManager().getFont())
{
    m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height / 2.f);
    m_text.setPosition(positon);
    m_textColor = m_text.getColor();
}

void CountdownParticle::update(const sf::Time &elapsed)
{
    m_textSize.step(elapsed.asMilliseconds());
    m_textAlpha.step(elapsed.asMilliseconds());
    m_text.setCharacterSize(m_textSize.get());
    m_textColor.a = m_textAlpha.get();
    m_text.setColor(m_textColor);
}

void CountdownParticle::render(Renderer &renderer) const
{
    renderer.scale(P_TO_M);
    renderer.render(m_text);
    renderer.scale(M_TO_P);
}

bool CountdownParticle::isFinished() const
{
    return m_textSize.progress() == 1.f;
}

}
