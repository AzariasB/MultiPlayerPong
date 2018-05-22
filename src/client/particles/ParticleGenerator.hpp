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
 * File:   ParticleGenerator.h
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#pragma once


#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Particle.hpp"

namespace mp {
class Renderer;

/**
 * @brief The ParticleGenerator class
 * the entry point for the particles
 * can create different types of particles
 */
class ParticleGenerator
{
public:
    /**
     * @brief ParticleGenerator empty constructor
     */
    ParticleGenerator();

    /**
     * @brief explode create an 'explosion' partcile
     * @param explosionPosition starting point of the explosion
     */
    void explode(const sf::Vector2f &explosionPosition);

    /**
     * @brief ballTrail generates a ball trail
     * @param ballCenter the position of the ball
     */
    void ballTrail(const sf::Vector2f &ballCenter);

    /**
     * @brief gainPoint gain point particle
     * @param position position where to generate the particle
     */
    void gainPoint(const sf::Vector2f &position);

    /**
     * @brief countdown countdonw particle
     * @param countdownValue the text to display inside the counter
     * @param position position of the counter
     */
    void countdown(const std::string &countdownValue, const sf::Vector2f &position);

    /**
     * @brief draw draws all the particles of the generator
     * @param renderer renderer to use
     */
    void draw(Renderer &renderer) const;

    /**
     * @brief update updates all the sub-particles of this generator
     * @param elapsed time elapsed since the last frame
     */
    void update(const sf::Time &elapsed);

private:
    /**
     * @brief m_particles all the particles
     * a unique_ptr is used here because the particle
     * is an abstract class
     */
    std::vector<std::unique_ptr<Particle> > m_particles;
};



}
