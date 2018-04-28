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


/**
 * @brief The TransitionState class
 * state used when a transition is happening
 * between two states, in order to create
 * an animation
 */
class TransitionState : public State
{
public:
    TransitionState();

    void draw(Renderer &renderer) const override;

    void update(const sf::Time &elapsed) override;

    void onEnter(BaseStateData *data) override;

    void onBeforeLeaving() override;

    void handleEvent(const sf::Event &ev) override;
private:
    int mExitingStateLabel = -1,
        mEnteringStateLabel = -1;
    bool m_tickEnteringState = false,
         m_tickExistingState = false;


    sf::Vector2f mEnteringTranslate;
    sf::Vector2f mExitingTranslate;

    void updateCenters();

    TransitionData::DIRECTION mDirection;

    twin::Twin<float, sf::Int32> mTweening;

    std::unique_ptr<BaseStateData> mEnteringData = {};

    static const sf::Int32 mTransitionDuration;
};


