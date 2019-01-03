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
 * File:   Powerup.hpp
 * Author: azarias
 *
 * Created on 09/03/2018
 */

#include <SFML/System/Vector2.hpp>
#include <Box2D/Dynamics/b2Body.h>
#include <limits>

#include "Wall.hpp"
#include "Game.hpp"

namespace mp {

Wall::Wall(const Game &g, const b2Vec2 &startingPos):
    PhysicObject(g, this)
{
    b2BodyDef def;
    def.position = startingPos;
    def.type = b2_staticBody;
    def.fixedRotation = true;
    mBody = mGame.world().CreateBody(&def);
    mBody->SetUserData(this);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(WALL_WITDH/2.f, WALL_HEIGHT/2.f);

    b2FixtureDef fixture;
    fixture.restitution = 0.f;
    fixture.friction = 0.f;
    fixture.shape = &boxShape;

    mBody->CreateFixture(&fixture);
}

Wall::~Wall()
{
}

}
