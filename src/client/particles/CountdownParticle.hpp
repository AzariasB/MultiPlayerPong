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
 * File:   CoundtownParticle.hpp
 * Author: azarias
 *
 * Created on 2/5/2018
 */

#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Particle.hpp"
#include "src/lib/twin.hpp"


namespace mp {

/**
 * @brief The CoundtownParticle class
 * particle used when doing the countdown
 * before a game, in order to have
 * a stylized countdown
 */
class CountdownParticle : public Particle
{
public:
    CountdownParticle(const std::string &text, const sf::Vector2f &positon);

    void update(const sf::Time &elapsed) override;

    void render(Renderer &renderer) const override;

    bool isFinished() const override;

private:

    twin::Twin<int, float> m_textSize;
    twin::Twin<int, float> m_textAlpha;

    sf::Text m_text;
    sf::Color m_textColor;
};

}
