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
 * File:   ParticleGenerator.h
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "Particle.hpp"

class Renderer;

class ParticleGenerator
{
public:
	ParticleGenerator();

	void explode(const sf::Vector2f &explosionPosition);

    void ballTrail(const sf::Vector2f &ballCenter);

    void draw(Renderer &renderer) const;

    void update(const sf::Time &elapsed);

private:
    std::list<std::unique_ptr<Particle> > m_particles;
};

#endif // PARTICLEGENERATOR_H