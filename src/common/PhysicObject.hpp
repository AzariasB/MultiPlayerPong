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
 * File:   PhysicObject.hpp
 * Author: azarias
 *
 * Created on 12/3/2018
 */
#pragma once

#include <SFML/System/Vector2.hpp>
#include <typeinfo>

class b2Body;
class b2Vec2;

namespace mp {

class Game;

/**
 * @brief The PhysicObject class a physicobject
 * is an object with a body, that can collide
 */
class PhysicObject
{
public:

    /**
     * @brief PhysicObject constructor
     * @param game the game in which the object is added
     * @param poType the type of physic object this represents
     */
    template<typename TYPE>
    PhysicObject(const Game& game, const TYPE *):
        type(typeid(TYPE)),
        mGame(game)
    {

    }

    /**
     * @brief getPosition the current position of the body
     * @return
     */
    const b2Vec2 &getPosition() const;

    /**
     * @brief isStatic if the body of this object is static
     * @return
     */
    bool isStatic() const;

    const std::type_info &type;

    virtual ~PhysicObject();
protected:
    /**
     * @brief mGame game this object is in
     */
    const Game &mGame;

    /**
     * @brief mBody body of the object
     */
    b2Body *mBody;
};


}
