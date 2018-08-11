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
 * File:   StateMachine.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 19:04
 */

#include "StateMachine.hpp"
#include "SoundEngine.hpp"
#include "Renderer.hpp"

namespace mp {

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
}

void StateMachine::initiliaze()
{
    m_background = BackgroundParallax(pr::resourceManager().getTexture(Assets::Icons::Blackboard), sf::Vector2f(SF_ARENA_WIDTH, SF_ARENA_HEIGHT));
}

State &StateMachine::getStateAt(int index) const
{
    if(states.find(index) == states.end())
        throw std::out_of_range("Index not found");

    auto found = states.find(index);
    if(found == states.end()) throw "State index not found";
    return *found->second;
}

const State &StateMachine::getCurrentState() const
{
    if (currentStateIndex < 0)throw std::out_of_range("The current state index is not set");
    auto found = states.find(currentStateIndex);
    if(found == states.end()) throw std::out_of_range("The given state index does not exist");
    return *found->second;
}

void StateMachine::translate(float nwX, float nwY)
{
    m_background.translate(nwX / 5.f, nwY / 5.f);
}

State &StateMachine::getCurrentState()
{
    if (currentStateIndex < 0)throw std::out_of_range("The current state index is not set");
    auto found = states.find(currentStateIndex);
    if(found == states.end()) throw std::out_of_range("The given state index does not exist");
    return *found->second;
}

void StateMachine::render(Renderer &renderer) const
{
    //find start x, start y translations

    // push
    // for y in all ys
    // for x in all xs
    // translate the sprite
    // draw it

    // end for / end for
    // pop

   renderer
           .render(m_background)
           .render(getCurrentState());
}

void StateMachine::setCurrentState(int stateLabel)
{
    m_background.setOffset();
    if (currentStateIndex > -1)
        states[currentStateIndex]->onBeforeLeaving();
    currentStateIndex = stateLabel;
    BaseStateData dat;
    states[currentStateIndex]->onEnter(&dat);
}

void StateMachine::fadeTo(int stateLabel)
{
    getStateAt(stateLabel).onBeforeEnter();
    TransitionData td;
    td.enteringStateLabel = stateLabel;
    td.exitingStateLabel = currentStateIndex;
    setCurrentState(cc::TRANSITION_FADE, &td);
}

void StateMachine::slideTo(int statelabel, SlideData::SLIDE_DIRECTION dir)
{
    getStateAt(statelabel).onBeforeEnter();
    SlideData td;
    td.enteringStateLabel = statelabel;
    td.exitingStateLabel = currentStateIndex;
    td.direction = dir;
    setCurrentState(cc::TRANSITION_SLIDE, &td);
    pr::soundEngine().playSound(Assets::Sounds::Rollover1);
}

}
