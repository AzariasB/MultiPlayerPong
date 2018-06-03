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
 * File:   ContactListener.hpp
 * Author: azarias
 *
 * Created on 12/3/2018
 */
#pragma once

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <SFML/Config.hpp>

namespace mp {



class EventManager;
class PhysicObject;

/**
 * @brief The ContactListener class class used
 * to interface with box2d and listen for any
 * contact between two physicobjects,
 * and send an event on the event manager
 * whenever it happends
 */
class ContactListener : public b2ContactListener
{
public:
    /**
     * @brief ContactListener constructor
     * @param evManager eventmanager to use to
     * trigger the different collisions events
     */
    ContactListener(EventManager &evManager);

    /**
     * @brief BeginContact overriden function
     * @param contact contact data between two fixtures
     */
    void BeginContact(b2Contact *contact) override;

    virtual ~ContactListener();

private:
    /**
     * @brief m_evManager event manager used to trigger
     * the collisions events
     */
    EventManager &m_evManager;

    /**
     * @brief userDataIsBall given two phyisics objects, check if one of them is the ball
     * @param objA first physic object
     * @param objB second physic object
     * @return wether one of the two given object is a ball
     */
    bool userDataIsBall(PhysicObject &objA, PhysicObject &objB) const;

public:
    const sf::Int64 ballHitWallEvent;
    const sf::Int64 ballHitPaddleEvent;
};


}
