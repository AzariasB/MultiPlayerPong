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

#pragma once

#include <SFML/System/Vector2.hpp>
#include "src/client/State.hpp"
#include "src/lib/twin.hpp"
#include <queue>


namespace mp {

/**
 * @brief The TransitionState class
 * state used when a transition is happening
 * between two states, in order to create
 * an animation
 */
class TransitionState : public State
{
public:
    /**
     * @brief TransitionState constructor
     */
    TransitionState();

    /**
     * @brief draw draws the two currently transitioning states
     * @param renderer
     */
    void draw(Renderer &renderer) const override;

    /**
     * @brief update updates the current transition
     * @param elapsed time elapsed since last frame
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief onEnter setup data for the transition
     * @param data data to use for the transition
     */
    void onEnter(BaseStateData *data) override;

    /**
     * @brief onBeforeLeaving before leaving this state
     * (whenever the transition is over)
     */
    void onBeforeLeaving() override;

    /**
     * @brief handleEvent handles the event : the entering state is the one handling the event
     * @param ev
     */
    void handleEvent(const sf::Event &ev) override;
private:
    /**
     * @brief mExitingStateLabel label of the state
     * that is going to leave the scene
     */
    int mExitingStateLabel = -1,
    /**
     * @brief mEnteringStateLabel label of the state
     * that is going to enter on the scene
     */
    mEnteringStateLabel = -1;

    /**
     * @brief m_tickEnteringState if we need to start
     * updating the state that's going to enter
     * same for the exiting state
     */
    bool m_tickEnteringState = false,
    m_tickExistingState = false;


    /**
     * @brief mEnteringTranslate current translating of the
     * entering state
     */
    sf::Vector2f mEnteringTranslate;

    /**
     * @brief mExitingTranslate current translating
     * of the exiting state
     */
    sf::Vector2f mExitingTranslate;

    /**
     * @brief updateCenters called to update
     * the translation of the transitionning
     * states
     */
    void updateCenters();

    /**
     * @brief mDirection the direction of the transition
     */
    TransitionData::DIRECTION mDirection;

    /**
     * @brief mTweening tweening for the
     * center position of the states
     */
    twin::Twin<float> mTweening;

    /**
      * data to pass to the entering state
      */
    std::unique_ptr<BaseStateData> mEnteringData = {};
};


}

