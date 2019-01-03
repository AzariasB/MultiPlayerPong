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
 * File:   BallTrailParticle.hpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "Particle.hpp"
#include "src/lib/twin.hpp"
#include "src/client/ColorTweening.hpp"

namespace sf {
class Time;
}

namespace mp {

/**
 * @brief The BallTrailParticle class
 * particle used to show a trail behind the ball
 * it looks a bit like dust smoke
 */
class BallTrailParticle : public Particle
{
public:
    /**
     * @brief BallTrailParticle constructor
     */
    BallTrailParticle();

    /**
     * @brief update overriden function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief isFinished whenever this particle is over
     * @return when the radius of this particle is zero, it can be destroyed
     */
    bool isFinished() const override;

    /**
     * @brief init
     * @param center center point of the trail
     * @param lifeTime lifetime of the trail
     * @param startRadius starting radius of the trail
     * @param color color of the trail
     */
    void init(const sf::Vector2f &center, const sf::Time &lifeTime, float startRadius, const sf::Color &color);

    /**
     * @brief render draws the particle
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    void test(const std::string &str) const;

private:
    /**
     * @brief m_center center point of the particle
     */
    sf::Vector2f m_center;

    /**
     * @brief m_twin tweening for the radius
     */
    twin::Twin<float> m_twin;

    ColorTweening m_alphaTwin;

    sf::Time m_lifeTime;

    /**
     * @brief m_angle current rotating angle
     */
    float m_angle = 0;

    /**
     * @brief m_shape save the shape to draw
     * to avoid instanciate it at every frame
     */
    sf::CircleShape m_shape;
};




}

