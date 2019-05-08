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
 * File:   Fireworkparticle.hpp
 * Author: azarias
 *
 * Created on 08/05/2019
 */
#pragma once

#include "Particle.hpp"
#include "src/lib/twin.hpp"
#include <SFML/Graphics/VertexArray.hpp>

namespace mp {

class FireworkParticle : public Particle
{
public:
    FireworkParticle();

    /**
     * @brief isFinished overriden function
     * @return
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
     * @brief init inits all the variables of the particles
     * @param target where to explode
     * @param climbTime time it takes to go to the place to explode
     */
    void init(const sf::Vector2f &target, const sf::Time &climbTime);

    /**
     * @brief getExplosionPosition getter to know where to create the explosion
     * @return
     */
    const sf::Vector2f &getExplosionPosition() const;

private:

    sf::VertexArray m_line;

    twin::Twin<float> m_yPos;

    twin::Twin<float> m_length;

    sf::Vector2f m_target;
};


}
