/*
 * The MIT License
 *
 * Copyright 2017-2018 azarias.
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
 * File:   Score.cpp
 * Author: azarias
 *
 * Created on 15/1/2019
 */
#include <SFML/System/Vector2.hpp>

#include "src/client/Provider.hpp"
#include "src/common/Math.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/particles/ParticleGenerator.hpp"
#include "src/client/ResourcesManager.hpp"
#include "Score.hpp"

namespace mp
{

Score::Score(ParticleGenerator &particleGen, const sf::Vector2f &position):
    m_particleGenerator(particleGen),
    m_text("0", pr::resourceManager().get<const sf::Font&>())
{
    m_text.setPosition(position);
    math::centerOrigin(m_text);
}

bool Score::update(const sf::Time &time)
{
    m_fontSize.step(time);
    m_text.setCharacterSize(m_fontSize.get());

    return true;
}

void Score::render(Renderer &target) const
{
    target.draw(m_text);
}

int Score::getScore() const
{
    return m_score;
}

void Score::setScore(int nwScore)
{
    m_score = nwScore;
}

void Score::gainPoint()
{
    std::function<void()> callback = [this](){
        m_particleGenerator.gainPoint(m_text.getPosition());
        m_fontSize = twin::makeTwin(50u, 30u, sf::milliseconds(100), twin::easing::expoInOut);
    };

    m_fontSize = twin::makeTwin(30u, 50u, sf::milliseconds(100), twin::easing::expoInOut, std::move(callback));
}


}
