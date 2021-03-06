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
 * File:   BallTrailParticle.cpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Time.hpp>

#include "src/client/Renderer.hpp"
#include "BallTrailParticle.hpp"

#include <iostream>

namespace mp {

BallTrailParticle::BallTrailParticle():
    Particle(this)
{
}

void BallTrailParticle::init(const sf::Vector2f &center, const sf::Time &lifeTime, float startRadius, const sf::Color &color)
{
    m_center = center;
    m_twin = twin::makeTwin(startRadius, 0.f, lifeTime, twin::cubicOut);
    m_alphaTwin = ColorTweening(color, sf::Color(255, 255, 255, 0), lifeTime, twin::expoOut);
    m_lifeTime = lifeTime;
    m_shape = sf::CircleShape(startRadius, 5);
    m_shape.setPosition(m_center.x - startRadius, m_center.y - startRadius);
    m_shape.setFillColor(color);
}

void BallTrailParticle::update(const sf::Time &elapsed)
{
    m_twin.step(elapsed);
    m_alphaTwin.update(elapsed);
    float radius = m_twin.get();
    m_lifeTime -= elapsed;

    m_angle += 5.f;
    m_shape.setRadius(radius);
    m_shape.setPosition(m_center.x - radius, m_center.y - radius);
    m_shape.setFillColor(m_alphaTwin.get());
}

bool BallTrailParticle::isFinished() const
{
    return m_alphaTwin.isFinished();
}

void BallTrailParticle::render(Renderer &renderer) const
{
    sf::Vector2f center = m_shape.getPosition();
    center.x += m_shape.getRadius();
    center.y += m_shape.getRadius();

    renderer.rotateAround(center, m_angle);
    renderer.draw(m_shape);
    renderer.rotateAround(center, -m_angle);

}

}

