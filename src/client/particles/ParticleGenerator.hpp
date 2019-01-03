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
#include "src/client/Renderable.hpp"

namespace mp {
class Renderer;
class ExplosionParticle;
class BallTrailParticle;
class GainPointParticle;
class CountdownParticle;

/**
 * @brief The ParticleGenerator class
 * the entry point for the particles
 * can create different types of particles
 */
class ParticleGenerator : public Renderable
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
    void render(Renderer &renderer) const override;

    /**
     * @brief update updates all the sub-particles of this generator
     * @param elapsed time elapsed since the last frame
     */
    void update(const sf::Time &elapsed);

    /**
     * @brief clear removes all the particles of this generator
     */
    void clear();

private:

    /**
     * @brief findUnusedParticle tries to find an unused particle
     * of the given type, if the particle is found, will return the
     * pointer and remove the particle from the 'unused particles' array
     * @param type the type of the particle to find
     * @return the particle if one was found, nullptr otherwise
     */
    template<typename PARTICLE>
    std::unique_ptr<Particle> &findUnusedParticle()
    {
        const std::type_info &target = typeid (PARTICLE);
        for(auto &p: m_particles)
            if(!p->isUsed && p->type == target) return p;

        return m_emptyParticle;
    }

    template<typename PARTICLE, typename ...Args>
    void instanciateParticle(Args ...argp)
    {
        auto &p = findUnusedParticle<PARTICLE>();
        if(p == m_emptyParticle) return;

        PARTICLE *part = static_cast<PARTICLE*>(p.get());

        part->init(argp...);
        part->isUsed = true;
    }

    template<typename PARTICLE, std::size_t COUNT>
    void fillParticles()
    {
        for(std::size_t i = 0; i < COUNT; ++i){
            m_particles.emplace_back(std::make_unique<PARTICLE>());
        }
    }

    /**
     * @brief m_particles all the particles
     * a unique_ptr is used here because the particle
     * is an abstract class
     */
    std::vector<std::unique_ptr<Particle> > m_particles;

    /**
     * @brief m_emptyParticle pointer to an empty particle
     */
    std::unique_ptr<Particle> m_emptyParticle;
};



}
