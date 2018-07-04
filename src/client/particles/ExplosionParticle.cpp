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
 * File:   ParticleExplosion.cpp
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#include "ExplosionParticle.hpp"
#include <algorithm>
#include <math.h>
#include <iostream>
#include "src/common/VectorsUtils.hpp"
#include "src/client/Renderer.hpp"


namespace mp {

ExplosionParticle::ExplosionParticle():
    Particle(PARTICLE_TYPE::Explosion)
{
}

void ExplosionParticle::init(const sf::Vector2f &origin, std::size_t particleNumber, const sf::Time &maxLifeTime)
{
    m_vertices = sf::VertexArray(sf::PrimitiveType::Lines, particleNumber * 2);
    m_maxLifeTime = maxLifeTime;
    m_particles = std::vector<Line>(particleNumber);
    createParticles(origin, particleNumber);
}

void ExplosionParticle::createParticles(const sf::Vector2f &origin, std::size_t particleNumber)
{
    for(std::size_t i = 0; i < particleNumber;i++){
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 100) * 0.01f;
        m_particles[i].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[i].lifeTime = sf::milliseconds(std::rand()%m_maxLifeTime.asMilliseconds() + (m_maxLifeTime.asMilliseconds()/2));
        m_vertices[(i*2)].position = origin;
        m_vertices[(i*2)+1].position = origin + m_particles[i].velocity;
    }
}

bool ExplosionParticle::isFinished() const
{
    return std::all_of(m_particles.begin(), m_particles.end(), [](const Line &p){return p.isOver();} );
}


void ExplosionParticle::update(const sf::Time &elapsed)
{
    for(std::size_t i = 0; i < m_particles.size(); i++){
        Line &p = m_particles[i];
        p.lifeTime -= elapsed;

        if(p.lifeTime <= sf::Time::Zero)continue;

        sf::Vector2f increment = p.velocity * elapsed.asSeconds();
        m_vertices[(i*2)].position += increment;
        m_vertices[(i*2)+1].position += increment;

        float ratio = p.lifeTime.asSeconds() / m_maxLifeTime.asSeconds();
        sf::Uint8 alpha = static_cast<sf::Uint8>(ratio * 255);

        m_vertices[(i*2)].color.a = alpha;
        m_vertices[(i*2)+1].color.a = alpha;
    }
}

void ExplosionParticle::render(Renderer &renderer) const
{
    renderer.draw(m_vertices);
}

}

