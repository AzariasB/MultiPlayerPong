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
 * File:   Jay.cpp
 * Author: azarias
 *
 * Created on 07/01/2019
 */

#include "Jay.hpp"
#include "src/common/Game.hpp"

namespace mp {

Jay::Jay(b2Body *body):
    m_body(body)
{

}

Jay &Jay::addCircleFixture(const b2Vec2 &offset, float radius, float restitution, float friction, float density)
{
    b2CircleShape shape;
    shape.m_p.Set(offset.x, offset.y);
    shape.m_radius = radius;

    b2FixtureDef def;
    def.shape = &shape;
    def.restitution = restitution;
    def.friction = friction;
    def.density = density;
    m_body->CreateFixture(&def);

    return *this;
}

Jay &Jay::addBoxFixture(float width, float height, float restitution, float friction, float density)
{
    b2PolygonShape shape;
    shape.SetAsBox(width, height);

    b2FixtureDef def;
    def.shape = &shape;
    def.restitution = restitution;
    def.friction = friction;
    def.density = density;
    m_body->CreateFixture(&def);

    return *this;
}

b2Body *Jay::body()
{
    return m_body;
}

Jay Jay::define(const Game &game, const b2Vec2 &position, b2BodyType type, bool fixedRotation)
{
    b2BodyDef def;
    def.position = position;
    def.type = type;
    def.fixedRotation = fixedRotation;

    return Jay(game.world().CreateBody(&def));
}

}
