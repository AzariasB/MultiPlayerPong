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
 * File:   ParticleExplosion.h
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#pragma once


#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "Particle.hpp"

namespace mp {

/**
 * @brief The ExplosionParticle class
 * whenever a paddle hist the ball, an explosion
 * is created, this explosion is composed of several lines
 * going away from the impact point
 */
class ExplosionParticle : public Particle
{
public:
    /**
     * @brief ExplosionParticle constructor
     * @param origin the collision point
     * @param particleNumber number of lines to draw
     * @param maxLifeTime max lifetime of a single line
     */
    ExplosionParticle();

    /**
     * @brief isFinished overriden function
     * @return when all the lines are 'dead'
     */
    bool isFinished() const override;

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
     * @brief init initializes the particles
     * @param origin center point of the expolosion
     * @param particleNumber number of rays to draw
     * @param maxLifeTime max lifetime of the particle
     */
    void init(const sf::Vector2f &origin, std::size_t particleNumber, const sf::Time &maxLifeTime);

private:
    /**
     * @brief createParticles creates the lines
     * @param origin where the lines starts from
     * @param particleNumber number of line to create
     */
    void createParticles(const sf::Vector2f &origin, std::size_t particleNumber);

    /**
     * @brief The Line struct
     * structure holding data
     * about a single line
     */
    struct Line{
        sf::Vector2f velocity;
        sf::Time lifeTime;

        bool isOver() const{
            return lifeTime <= sf::Time::Zero;
        }
    };

    /**
     * @brief m_particles all the lines to draw
     */
    std::vector<Line> m_particles;

    /**
     * @brief m_maxLifeTime
     * max lifetime of a line
     */
    sf::Time m_maxLifeTime;

    /**
     * @brief m_vertices the
     * vertex array containing the lines to draw
     */
    sf::VertexArray m_vertices;
};



}

