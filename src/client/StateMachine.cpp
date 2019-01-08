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
    m_background = BackgroundParallax(
                pr::resourceManager().get<const sf::Texture&>(Assets::Icons::Blackboard),
                sf::Vector2f(SF_ARENA_WIDTH, SF_ARENA_HEIGHT)
    );
}


const State &StateMachine::getCurrentState() const
{
    if (m_currentState == 0)throw std::out_of_range("The current state index is not set");
    auto found = m_states.find(m_currentState);
    if(found == m_states.end()) throw std::out_of_range("The given state index does not exist");
    return *found->second;
}

void StateMachine::translate(float nwX, float nwY)
{
    m_background.translate(nwX / 5.f, nwY / 5.f);
}

State &StateMachine::getCurrentState()
{
    if (m_currentState == 0)throw std::out_of_range("The current state index is not set");
    auto found = m_states.find(m_currentState);
    if(found == m_states.end()) throw std::out_of_range("The given state index does not exist");
    return *found->second;
}

void StateMachine::setStateFromId(std::size_t classId)
{
    m_background.setOffset();
    m_states[m_currentState]->onBeforeLeaving();
    m_currentState = classId;
    m_states[m_currentState]->onEnter(nullptr);
}

void StateMachine::render(Renderer &renderer) const
{
   renderer
           .render(m_background)
           .render(getCurrentState());
}

State &StateMachine::getStateFromId(std::size_t index) const
{
    if(m_states.find(index) == m_states.end())
        throw std::out_of_range("Index not found");

    auto found = m_states.find(index);
    if(found == m_states.end()) throw "State index not found";
    return *found->second;
}

}
