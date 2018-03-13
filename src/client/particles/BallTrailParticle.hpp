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
 * File:   BallTrailParticle.hpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#ifndef BALLTRAILPARTICLE_HPP
#define BALLTRAILPARTICLE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>

#include "Particle.hpp"
#include "src/lib/twin.hpp"

namespace sf {
    class Time;
}

class BallTrailParticle : public Particle
{
public:
    BallTrailParticle(const sf::Vector2f &center, const sf::Time &lifeTime, float startRadius, sf::Color color);

    void update(const sf::Time &elapsed) override;

    bool isFinished() const override;

    void render(Renderer &renderer) const override;

private:
    sf::Vector2f m_center;

    twin::Twin<float, sf::Int32> m_twin;

    sf::Time m_lifeTime;

    sf::Color m_color;
};

#endif // BALLTRAILPARTICLE_HPP
