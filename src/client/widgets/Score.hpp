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
 * File:   Score.hpp
 * Author: azarias
 *
 * Created on 15/1/2019
 */
#pragma once

#include <SFML/Graphics/Text.hpp>
#include "src/lib/twin.hpp"

#include "Widget.hpp"


namespace mp
{

class Renderer;
class ParticleGenerator;

class Score : public Widget
{
public:
    Score(ParticleGenerator &particleGen, const sf::Vector2f &position);

    void render(Renderer &target) const override;

    bool handleEvent(const sf::Event &) override{ return false;}

    bool update(const sf::Time &time) override;

    void setScore(int nwScore);

    int getScore() const;

    void gainPoint();

    virtual ~Score() override
    {

    }
private:
    ParticleGenerator &m_particleGenerator;

    int m_score = 0;

    sf::Text m_text;

    twin::Twin<int, std::function<void()>> m_fontSize;

};


}
