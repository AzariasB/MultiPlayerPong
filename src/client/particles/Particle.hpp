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
 * File:   Particle.hpp
 * Author: azarias
 *
 * Created on 13/3/2018
 */
#pragma once

#include <typeindex>
#include <typeinfo>
#include "src/client/Renderable.hpp"

namespace sf {
    class Time;
}

namespace mp {

class Renderer;


/**
 * @brief The Particle class
 * abstract class to represent a particle
 * a particle must have the 'update' function,
 * the 'render' function and the 'isFinished' function
 */
class Particle : public Renderable
{
public:

    /**
     * @brief Particle empty constructor
     */
    template<typename PARTICLE>
    Particle(const PARTICLE *): type(typeid (PARTICLE))
    {
    }

    /**
     * @brief update called to update the position and the
     * animation of the particle
     * @param elapsed the time elapsed since the last frame
     */
    virtual void update(const sf::Time &elapsed) = 0;

    /**
     * @brief isFinished helper to tell the particle manager whenever
     * this particle is finished, and can be destroyed
     * @return
     */
    virtual bool isFinished() const = 0;


    /**
     * @brief ~Particle virtual destructor
     */
    virtual ~Particle()
    {

    }

    /**
     * @brief type store the underlying type
     * of this particle
     */
    const std::type_info& type;

    bool isUsed = false;
};



}

