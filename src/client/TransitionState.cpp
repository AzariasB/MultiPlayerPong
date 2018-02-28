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
#include <tweeny/tweeny.h>


const sf::Int32 TransitionState::mTransitionDuration = 100;


TransitionState::TransitionState()
{
}


void TransitionState::draw(Renderer &renderer) const
{
    int horiztontalMult = mDirection == TransitionData::GO_LEFT ? -1 : 1;
    float exitingXCenter = ARENA_WIDTH/2.f + horiztontalMult * mTweening.peek();

    float enteringXCenter = ( (-horiztontalMult) * ARENA_WIDTH + ARENA_WIDTH/2.f ) + horiztontalMult *  mTweening.peek();

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
    mTweening.step(elapsed.asMilliseconds());
    if(mTweening.progress() == 1.f){
        if(mEnteringData){
            pr::stateMachine().setCurrentState(mEnteringStateLabel, *mEnteringData);
        }else{
            pr::stateMachine().setCurrentState(mEnteringStateLabel);
        }
    }


}

void TransitionState::onEnter(BaseStateData *data)
{
    StateData<TransitionData*> *stData  = 0;
    if(!(stData = dynamic_cast<StateData<TransitionData*>*>(data)))return;

    TransitionData &transition = *stData->data();
    TransitionData::DIRECTION dir = transition.direction;

    std::pair<int,int> tweening = {0,0};

    if(dir == TransitionData::GO_RIGHT || dir == TransitionData::GO_LEFT){
        tweening.first = 0;
        tweening.second = ARENA_WIDTH;
    }else if(dir == TransitionData::GO_DOWN || dir == TransitionData::GO_UP){
        tweening.first = 0;
        tweening.second = ARENA_HEIGHT;
    }

    mTweening = tweeny::from(tweening.first)
                    .to(tweening.second)
                    .during(mTransitionDuration)
                    .via(tweeny::easing::backInOut);

    mEnteringStateLabel = stData->data()->enteringStateLabel;
    mExitingStateLabel = stData->data()->exitingStateLabel;
    mEnteringData.swap(stData->data()->enteringData);
    mDirection = dir;
}

void TransitionState::onLeave()
{
    mEnteringStateLabel = -1;
    mExitingStateLabel = -1;
    mEnteringData = {};
}

void TransitionState::handleEvent(const sf::Event &ev)
{
    if(mEnteringStateLabel != -1)
        pr::stateMachine().getStateAt(mEnteringStateLabel).handleEvent(ev);
}
