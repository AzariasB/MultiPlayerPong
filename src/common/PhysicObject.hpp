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
 * File:   PhysicObject.hpp
 * Author: azarias
 *
 * Created on 12/3/2018
 */
#ifndef PHYSICOBJECT_HPP
#define PHYSICOBJECT_HPP

#include <SFML/System/Vector2.hpp>

class b2Body;
class b2Vec2;
class Game;

class PhysicObject
{
public:
    const enum PO_TYPE{WALL, BALL, PADDLE} type;

    PhysicObject(const Game& game, PO_TYPE poType);

    const b2Vec2 &getPosition() const;

    virtual sf::Vector2f topLeftPosition() const = 0;

    virtual ~PhysicObject();
protected:
    const Game &mGame;

    b2Body *mBody;
};

#endif // PHYSICOBJECT_HPP
