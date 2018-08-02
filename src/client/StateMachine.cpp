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
    m_blackboard = sf::Sprite(pr::resourceManager().getTexture(Assets::Icons::Blackboard));
    m_blackboard.setPosition(SF_CENTER_X, SF_CENTER_Y);
    math::centerOrigin(m_blackboard);
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
           .push()
            .draw(m_blackboard)
            .translate(sf::Vector2f(m_blackboard.getGlobalBounds().width, 0))
            .draw(m_blackboard)
            .translate(sf::Vector2f(m_blackboard.getGlobalBounds().width, 0))
            .draw(m_blackboard)
            .translate(sf::Vector2f(m_blackboard.getGlobalBounds().width, 0))
            .draw(m_blackboard)
           .pop()
            .render(getCurrentState());
}

void StateMachine::setCurrentState(int stateLabel)
{
    if (currentStateIndex > -1)
        states[currentStateIndex]->onBeforeLeaving();
    currentStateIndex = stateLabel;
    BaseStateData dat;
    states[currentStateIndex]->onEnter(&dat);
}

void StateMachine::goToState(int statelabel, TransitionData::DIRECTION dir)
{
    getStateAt(statelabel).onBeforeEnter();
    TransitionData td;
    td.enteringStateLabel = statelabel;
    td.exitingStateLabel = currentStateIndex;
    td.direction = dir;
    setCurrentState(cc::TRANSITION, &td);
    pr::soundEngine().playSound(Assets::Sounds::Rollover1);
}

}
