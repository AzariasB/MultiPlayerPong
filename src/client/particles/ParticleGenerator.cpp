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
 * File:   ParticleGenerator.cpp
 * Author: azarias
 *
 * Created on 30/10/2017
 */
#include <algorithm>

#include "src/common/Config.hpp"
#include "ParticleGenerator.hpp"
#include "ExplosionParticle.hpp"
#include "BallTrailParticle.hpp"
#include "GainPointParticle.hpp"
#include "CountdownParticle.hpp"

namespace mp {

ParticleGenerator::ParticleGenerator()
{

}

void ParticleGenerator::explode(const sf::Vector2f &explosionPosition)
{
    m_particles.emplace_back(
         std::make_unique<ExplosionParticle>(explosionPosition, (std::rand()%10) + 10 , sf::milliseconds(500))
    );
}


void ParticleGenerator::ballTrail(const sf::Vector2f &ballCenter)
{
    m_particles.emplace_back(
        std::make_unique<BallTrailParticle>(ballCenter, sf::milliseconds((std::rand() % 500) + 100), (float)BALL_RADIUS, sf::Color::White)
    );
}

void ParticleGenerator::gainPoint(const sf::Vector2f &position)
{
    m_particles.emplace_back(
        std::make_unique<GainPointParticle>(position, sf::milliseconds(500))
    );
}

void ParticleGenerator::countdown(const std::string & countdownValue, const sf::Vector2f &position)
{
    m_particles.emplace_back(
        std::make_unique<CountdownParticle>(countdownValue, position)
    );
}

void ParticleGenerator::draw(Renderer &renderer) const
{
    for(const auto&part : m_particles){
        part->render(renderer);
    }
}

void ParticleGenerator::update(const sf::Time &elapsed)
{
    for(auto it = m_particles.begin(); it != m_particles.end();){
        (*it)->update(elapsed);
        if((*it)->isFinished()){
            it = m_particles.erase(it);
        }else{
            ++it;
        }
    }
}


}
