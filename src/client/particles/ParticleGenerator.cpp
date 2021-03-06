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
#include "FireworkParticle.hpp"

#include "src/client/ClientConf.hpp"

namespace mp {

ParticleGenerator::ParticleGenerator()
{
    fillParticles<ExplosionParticle, 10>();
    fillParticles<BallTrailParticle, 200>();
    fillParticles<GainPointParticle, 2>();
    fillParticles<CountdownParticle, 2>();
    fillParticles<FireworkParticle, 10>();
}

void ParticleGenerator::firework(const sf::Vector2f &target)
{
    instanciateParticle<FireworkParticle>(target, cc::Times::fireworkClimbTime);
}

void ParticleGenerator::explode(const sf::Vector2f &explosionPosition)
{    
   instanciateParticle<ExplosionParticle>(explosionPosition, (std::rand()%10) + 10 , cc::Times::explosionLifeTime);
}


void ParticleGenerator::ballTrail(const sf::Vector2f &ballCenter)
{
    instanciateParticle<BallTrailParticle>(ballCenter, cc::Times::trailLifeTime, BALL_RADIUS, sf::Color::White);
}

void ParticleGenerator::gainPoint(const sf::Vector2f &position)
{
    instanciateParticle<GainPointParticle>(position, cc::Times::gainPointLifeTime);
}

void ParticleGenerator::countdown(const std::string & countdownValue, const sf::Vector2f &position)
{
    instanciateParticle<CountdownParticle>(countdownValue, position, sf::seconds(1));
}


void ParticleGenerator::render(Renderer &renderer) const
{
    for(const auto&part : m_particles){
        if(part->isUsed) part->render(renderer);
    }
}

void ParticleGenerator::clear()
{
    for(const auto &part : m_particles) part->isUsed = false;
}

bool ParticleGenerator::update(const sf::Time &elapsed)
{
    bool didExplode = false;
    const auto &fireworkType = typeid (FireworkParticle);
    for(auto &p : m_particles){
        if(p->isUsed){
            p->update(elapsed);
            if(p->isFinished()) {
                if(p->type == fireworkType){
                    explode(static_cast<FireworkParticle*>(p.get())->getExplosionPosition());
                    didExplode = true;
                }
                p->isUsed = false;
            }
        }
    }
    return didExplode;
}


}
