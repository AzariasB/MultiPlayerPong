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

#include "Transition.hpp"

#include "src/common/Config.hpp"
#include "src/client/Provider.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/StateMachine.hpp"

#include "src/common/VectorsUtils.hpp"

namespace mp {

Transition::Transition()
{
}

void Transition::update(const sf::Time &elapsed)
{
    if(progress(elapsed)){
        if(m_enteringData){
            pr::stateMachine().setStateFromId(m_enteringStateLabel, *m_enteringData);
        }else{
            pr::stateMachine().setStateFromId(m_enteringStateLabel);
        }
        pr::stateMachine().getStateFromId(m_exitingStateLabel).onAfterLeaving();
    }
}

void Transition::setup(TransitionData &data)
{
    m_enteringStateLabel = data.enteringStateLabel;
    m_exitingStateLabel = data.exitingStateLabel;
    m_tickEnteringState = data.updateEnteringState;
    m_tickExistingState = data.updateExistingState;
    m_enteringData.swap(data.enteringData);
}

void Transition::onBeforeLeaving()
{
    m_enteringData = {};
}

void Transition::handleEvent(const sf::Event &ev)
{
    if(m_enteringStateLabel != 0)
        pr::stateMachine().getStateFromId(m_enteringStateLabel).handleEvent(ev);
}

State &Transition::enteringState() const
{
    return pr::stateMachine().getStateFromId(m_enteringStateLabel);
}

State &Transition::exitingState() const
{
    return pr::stateMachine().getStateFromId(m_exitingStateLabel);
}


}
