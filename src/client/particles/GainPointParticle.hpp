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
 * File:   GainPointParticle.hpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#pragma once

#include <SFML/Graphics/Text.hpp>

#include "src/lib/twin.hpp"
#include "Particle.hpp"

namespace sf {
class Time;
}


namespace mp {

/**
 * @brief The GainPointParticle class
 * whenever a paddle hit the ball, this particle
 * is created next to the points counting
 */
class GainPointParticle : public Particle
{
public:
    /**
     * @brief GainPointParticle constructor
     * @param position starting position of the particle
     * @param lifeTime lifetime of this particle
     */
    GainPointParticle(const sf::Vector2f &position, const sf::Time &lifeTime);

    /**
     * @brief render overriden function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief update overriden function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief isFinished whenever the particle is finished
     * @return when the the animation is over (and alpha = 0)
     */
    bool isFinished() const override;

private:
    /**
     * @brief m_positionTwin tweening for the position
     */
    twin::Twin<float> m_positionTwin;

    /**
     * @brief m_alphaTwin tweening for the alpha color
     */
    twin::Twin<sf::Uint8> m_alphaTwin;

    /**
     * @brief m_text "+1" text
     */
    sf::Text m_text;
};



}

