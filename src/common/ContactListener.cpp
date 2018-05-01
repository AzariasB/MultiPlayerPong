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
 * File:   ContactListener.cpp
 * Author: azarias
 *
 * Created on 12/3/2018
 */
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "ContactListener.hpp"
#include "EventManager.hpp"
#include "Paddle.hpp"
#include "PhysicObject.hpp"


namespace mp {

class Ball;

ContactListener::ContactListener(EventManager &evManager):
    m_evManager(evManager),
    ballHitPaddleEvent(evManager.nextEventCode()),
    ballHitWallEvent(evManager.nextEventCode())
{

}

bool ContactListener::userDataIsBall(PhysicObject &objA, PhysicObject &objB) const
{
    if(objA.type == PhysicObject::BALL){
        if(objB.type == PhysicObject::PADDLE){
            Paddle &paddle = static_cast<Paddle&>(objB);
            std::size_t v = paddle.getNum();
            m_evManager.trigger(ballHitPaddleEvent,paddle.getNum(), objA.getPosition());
        }else{
            m_evManager.trigger(ballHitWallEvent, objA.getPosition());
        }

        return true;
    }
    return false;
}


void ContactListener::BeginContact(b2Contact *contact)
{
    PhysicObject &objA = *static_cast<PhysicObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
    PhysicObject &objB = *static_cast<PhysicObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

    if(userDataIsBall(objA, objB))return;

    userDataIsBall(objB, objA);
}

}
