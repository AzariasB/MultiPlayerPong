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
 * File:   SlideTransition.cpp
 * Author: azarias
 *
 * Created on 11/8/2018
 */
#include "src/client/StateMachine.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/Provider.hpp"
#include "src/client/StateMachine.hpp"

namespace mp
{

SlideTransition::SlideTransition()
{

}


void SlideTransition::render(Renderer &renderer) const
{
    renderer.push()
            .translate(m_exitingTranslate)
            .render(exitingState())
            .pop()
            .push()
            .translate(m_enteringTranslate)
            .render(enteringState())
            .pop();
}


bool SlideTransition::progress(const sf::Time &elapsed)
{
    m_tweening.step(elapsed);
    exitingState().update(elapsed);
    enteringState().update(elapsed);
    updateCenters();
    return m_tweening.progress() == 1.f;
}

void SlideTransition::updateCenters()
{
    float tVal = m_tweening.get();
    if(m_direction == cc::SLIDE_DIRECTION::SLIDE_UP || m_direction == cc::SLIDE_DIRECTION::SLIDE_DOWN){
        int vertMult = m_direction == cc::SLIDE_DIRECTION::SLIDE_UP ? 1 : -1;
        m_exitingTranslate.y = vertMult * tVal;
        m_enteringTranslate.y = vertMult *(-SF_ARENA_HEIGHT + tVal);
        pr::stateMachine().translate(0, vertMult * tVal);
    }else{
        int horiztontalMult = m_direction == cc::SLIDE_DIRECTION::SLIDE_LEFT ? 1 : -1;
        m_exitingTranslate.x = horiztontalMult * tVal;
        m_enteringTranslate.x = horiztontalMult * (-SF_ARENA_WIDTH + tVal);
        pr::stateMachine().translate(horiztontalMult * tVal, 0);
    }

}

}
