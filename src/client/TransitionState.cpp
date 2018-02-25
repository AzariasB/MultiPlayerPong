/*
 * The MIT License
 *
 * Copyright 2017 azarias.
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

#include "TransitionState.hpp"
#include "Provider.hpp"
#include "../Config.hpp"


const sf::Time TransitionState::mStartingTime = sf::seconds(0.5f);


TransitionState::TransitionState()
{

}


void TransitionState::draw(Renderer &renderer) const
{
    float remainingTime = ((mStartingTime - mTransitionTime)/mStartingTime.asSeconds()).asSeconds();
    float lessX = ARENA_WIDTH * remainingTime;

    float exitingXCenter = ARENA_WIDTH/2.f + lessX;

    float enteringXCenter = (-ARENA_WIDTH + ARENA_WIDTH/2.f) + lessX;

    sf::Vector2f exitingCenter(exitingXCenter, ARENA_HEIGHT/2.f);
    sf::Vector2f enteringCenter(enteringXCenter, ARENA_HEIGHT/2.f);

    sf::Vector2f size(ARENA_WIDTH, ARENA_HEIGHT);

    sf::View exitingView(exitingCenter, size);
    sf::View enteringView(enteringCenter, size);

    renderer.setView(exitingView);
    pr::stateMachine().getStateAt(mExitingStateLabel).draw(renderer);

    renderer.setView(enteringView);
    pr::stateMachine().getStateAt(mEnteringStateLabel).draw(renderer);

    renderer.resetView();
}

void TransitionState::update(const sf::Time &elapsed)
{
    mTransitionTime -= elapsed;
    if(mTransitionTime <= sf::Time::Zero){
        pr::stateMachine().setCurrentState(mEnteringStateLabel);
    }
}

void TransitionState::onEnter(BaseStateData *data)
{
    StateData<TransitionData*> *stData  = 0;
    if(!(stData = dynamic_cast<StateData<TransitionData*>*>(data)))return;

    mTransitionTime = mStartingTime;
    mEnteringStateLabel = stData->data()->enteringStateLabel;
    mExitingStateLabel = stData->data()->exitingStatelabel;
}

void TransitionState::onLeave()
{

}

void TransitionState::handleEvent(const sf::Event &ev)
{

}
