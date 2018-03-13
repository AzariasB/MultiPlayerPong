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
 * File:   ParticleExplosion.h
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#ifndef PARTICLEEXPLOSION_H
#define PARTICLEEXPLOSION_H

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "Particle.hpp"

class ExplosionParticle : public Particle
{
public:
    ExplosionParticle(const sf::Vector2f &origin, std::size_t particleNumber, sf::Time maxLifeTime);

    bool isFinished() const override;

    void render(Renderer &renderer) const override;

    void update(const sf::Time &elapsed) override;

private:
	void createParticles(const sf::Vector2f &origin, std::size_t particleNumber);

    struct Line{
		sf::Vector2f velocity;
		sf::Time lifeTime;

		bool isOver() const{
			return lifeTime <= sf::Time::Zero;
		}
	};

    std::vector<Line> m_particles;

	sf::Time m_maxLifeTime;

	sf::VertexArray m_vertices;
};

#endif // PARTICLEEXPLOSION_H
