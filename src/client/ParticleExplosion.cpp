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
 * File:   ParticleExplosion.cpp
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#include "ParticleExplosion.hpp"
#include <algorithm>
#include <math.h>


ParticleExplosion::ParticleExplosion(const sf::Vector2f &origin, std::size_t particleNumber, sf::Time maxLifeTime):
m_maxLifeTime(maxLifeTime),
m_vertices(sf::PrimitiveType::Points, particleNumber),
m_particles(particleNumber)
{
	createParticles(origin, particleNumber);
}

void ParticleExplosion::createParticles(const sf::Vector2f &origin, std::size_t particleNumber)
{
	for(std::size_t i = 0; i < particleNumber;i++){
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 100) + 10.f;
		m_particles[i].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[i].lifeTime = sf::milliseconds(std::rand()%m_maxLifeTime.asMilliseconds() + (m_maxLifeTime.asMilliseconds()/2));
		m_vertices[i].position = origin;
	}
}

bool ParticleExplosion::isFinisehd() const
{
	return std::all_of(m_particles.begin(), m_particles.end(), [](const Particle &p){return p.isOver();} );
}


void ParticleExplosion::update(sf::Time elapsed)
{
	for(std::size_t i = 0; i < m_particles.size(); i++){
		Particle &p = m_particles[i];
		p.lifeTime -= elapsed;

		if(p.lifeTime <= sf::Time::Zero)continue;

		m_vertices[i].position += p.velocity * elapsed.asSeconds();

		float ratio = p.lifeTime.asSeconds() / m_maxLifeTime.asSeconds();
		m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
	}
}

void ParticleExplosion::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;


	target.draw(m_vertices, states);
}
