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

#include <SFML/Window/Event.hpp>
#include <limits>

#include "src/client/StateMachine.hpp"

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
        m_switchState();
    }
}


void Transition::onBeforeLeaving()
{
    m_switchState = {};
}

void Transition::handleEvent(const sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        progress(sf::seconds(700.f));
    }
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
