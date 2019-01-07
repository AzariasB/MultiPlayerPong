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
 * File:   Jay.hpp
 * Author: azarias
 *
 * Created on 07/01/2019
 */

#pragma once

#include <Box2D/Dynamics/b2Body.h>

namespace mp {

class Game;

/**
 * @brief The Jay class : alias : the BodyBuilder
 */
class Jay
{
public:

    /**
     * @brief body
     * @return the constructed body
     */
    b2Body *body();

    /**
     * @brief addCircleFixture adds a fixture with a shape of a circle
     * @param offset center offset
     * @param radius radius of the circle
     * @param restitution restition of the circle
     * @param friction friction of the circle
     * @param density density of the circle
     * @return the body builder
     */
    Jay &addCircleFixture(const b2Vec2 &offset, float radius, float restitution, float friction, float density = 0.f);

    /**
     * @brief addBoxFixture adds a fixture with a shape of a box to the current body
     * @param width the width of the box
     * @param height the height of the box
     * @param restitution restitution of the box
     * @param friction friction of the box
     * @param density density of the box
     * @return the body builder
     */
    Jay &addBoxFixture(float width, float height, float restitution, float friction, float density = 0.f);

    /**
     * @brief define creates a new Jay object, and init it with the given parameters
     * @param game game, contains the world to create a new body
     * @param position position of the body
     * @param type type of the body
     * @param fixedRotation fixed rotation of the body
     * @return the BodyBuilder
     */
    static Jay define(const Game &game, const b2Vec2 &position, b2BodyType type, bool fixedRotation = false);

private:
    Jay(b2Body *body);

    b2Body *m_body;

};


}

