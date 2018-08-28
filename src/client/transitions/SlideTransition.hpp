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
 * File:   SlideTransition.hpp
 * Author: azarias
 *
 * Created on 11/8/2018
 */
#pragma once

#include "Transition.hpp"
#include <SFML/System/Vector2.hpp>
#include "src/lib/twin.hpp"

namespace mp
{

class Renderer;

/**
 * @brief The SlideTransition class used
 * to create a sliding transition between two states
 * the transition receives the direction data
 * with the 'onEnter' method
 */
class SlideTransition  : public Transition
{
public:
    /**
     * @brief SlideTransition empty constructor
     */
    SlideTransition();

    /**
     * @brief render renders the current sliding transition
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief progress moves the current transition
     * @param elapsed
     * @return
     */
    bool progress(const sf::Time &elapsed) override;

    /**
     * @brief onEnter function called when starting the transition
     * @param data containing the information about where to slide
     * and what data to pass to the next state
     */
    void onEnter(BaseStateData *data) override;

private:


    /**
     * @brief mEnteringTranslate current translating of the
     * entering state
     */
    sf::Vector2f m_enteringTranslate;

    /**
     * @brief mExitingTranslate current translating
     * of the exiting state
     */
    sf::Vector2f m_exitingTranslate;

    /**
     * @brief updateCenters called to update
     * the translation of the transitionning
     * states
     */
    void updateCenters();


    /**
     * @brief mTweening tweening for the
     * center position of the states
     */
    twin::Twin<float> m_tweening;

    /**
     * @brief m_direction direction of the slide
     */
    SlideData::SLIDE_DIRECTION m_direction;
};


}
