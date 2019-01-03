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

#pragma once

#include "src/client/State.hpp"


namespace mp {

/**
 * @brief The TransitionState class
 * state used when a transition is happening
 * between two states, in order to create
 * an animation
 */
class Transition : public State
{
public:
    /**
     * @brief TransitionState constructor
     */
    Transition();

    /**
     * @brief draw draws the two currently transitioning states
     * @param renderer
     */
   virtual  void render(Renderer &renderer) const override = 0;

    /**
     * @brief update updates the current transition
     * @param elapsed time elapsed since last frame
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief progress method that must be delcared
     * in the sub-functions in order to progress
     * the transition state, it must
     * return a boolean to tell wether the progress is finished
     * @param elapsed
     * @return true when the transition is over
     */
    virtual bool progress(const sf::Time &elapsed) = 0;

    /**
     * @brief handleEvent handles the event : the entering state is the one handling the event
     * @param ev
     */
    virtual void handleEvent(const sf::Event &ev) override;

    /**
     * @brief onEnter inherited function
     * @param data
     */
    void setup(TransitionData &data);

    /**
     * @brief onBeforeLeaving inherited function
     */
    virtual void onBeforeLeaving() override;
protected:
    /**
     * @brief mExitingStateLabel label of the state
     * that is going to leave the scene
     */
    int m_exitingStateLabel = -1,
    /**
     * @brief mEnteringStateLabel label of the state
     * that is going to enter on the scene
     */
    m_enteringStateLabel = -1;

    /**
     * @brief m_tickEnteringState if we need to start
     * updating the state that's going to enter
     * same for the exiting state
     */
    bool m_tickEnteringState = false,
    m_tickExistingState = false;


    /**
      * data to pass to the entering state
      */
    std::unique_ptr<BaseStateData> m_enteringData = {};
};


}

