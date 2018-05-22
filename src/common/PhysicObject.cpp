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
 * File:   PhysicObject.cpp
 * Author: azarias
 *
 * Created on 12/3/2018
 */

#include <Box2D/Common/b2Math.h>

#include "PhysicObject.hpp"
#include "Game.hpp"

namespace mp {

PhysicObject::PhysicObject(const Game &game, PO_TYPE poType):
    type(poType),
    mGame(game)
{
}


const b2Vec2 &PhysicObject::getPosition() const
{
    return mBody->GetPosition();
}

bool PhysicObject::isStatic() const
{
    return (mBody && mBody->GetType() == b2_staticBody);
}

PhysicObject::~PhysicObject()
{
    mGame.world().DestroyBody(mBody);
    mBody = 0;
}

}
