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
 * File:   State.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:20
 */

#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include <qglobal.h>
#include "Renderable.hpp"
#include "ClientConf.hpp"

namespace sf {
class Event;
class Time;
}


namespace mp {

class Renderer;

template<typename STATE, typename ...Args>
struct TransitionData {

    TransitionData(Args&&... data):
        enteringData(std::forward<Args>(data)...)
    {
    }

    std::size_t enteringStateLabel, exitingStateLabel;
    bool updateEnteringState = false,
    updateExistingState = false;

    std::tuple<Args...> enteringData;//data to pass to the entering state
};

template<typename STATE, typename ...Args>
struct SlideData : public TransitionData<STATE, Args...> {

    SlideData(Args&& ...data):
        TransitionData<STATE, Args...> (std::forward<Args>(data)...)
    {
    }

    cc::SLIDE_DIRECTION direction;
};

/**
 * @brief The State class is a virtual class
 * that must be inherited by all the states of the game
 * It introduces several virtual functions that must be overriden
 * by the subclasses.
 */
class State : public sf::NonCopyable, public Renderable {
public:

    /**
     * @brief State constructor
     * @param client a reference to the client application
     */
    State()
    {

    }

    /**
     * @brief update updates the State, is called on a regular basis, must be used to update the intern state of the state.
     * @param elapsed the time elapsed since the last update occured, passed in as a SFML time object
     */
    virtual void update(const sf::Time &elapsed) = 0;

    virtual void render(Renderer &renderer) const override = 0;

    /**
     * @brief handleEvent handles the event sent by the renderwindow (mouse move, key pressed, ...)
     * @param ev the sfml object for the event
     */
    virtual void handleEvent(const sf::Event &ev) = 0;


    virtual void onBeforeEnter()
    {

    }


    /**
     * @brief onEnter function called when the state becomes the current state of the application,
     * is used to init some data
     * @param data data passed by the previous state (if any) can be null
     */
    template<typename ...Args>
    void onEnter(Args&&...)
    {
    }

    /**
     * @brief onLeave function called when the states looses the focus to let another state enters
     * this function is not the destructor, the state could be used another time during the app's lifetime
     */
    virtual void onBeforeLeaving()
    {

    }

    /**
     * @brief onAfterLeaving function called when the transition if finished, can
     * be used to hide stuff once the camera is not filming
     * is not pure because it might not be used for usefull
     * purpose
     */
    virtual void onAfterLeaving()
    {

    }

    virtual ~State() override
    {
    }

};

}
