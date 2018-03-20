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
#include "src/client/Provider.hpp"
#include "src/Config.hpp"
#include "src/client/StateMachine.hpp"

const sf::Int32 TransitionState::mTransitionDuration = 500;


TransitionState::TransitionState()
{
}


void TransitionState::draw(Renderer &renderer) const
{
    renderer.push();
    renderer.translate(mExitingTranslate);
    //translate
    pr::stateMachine().getStateAt(mExitingStateLabel).draw(renderer);
    renderer.pop();

    renderer.push();
    //translate
    renderer.translate(mEnteringTranslate);
    pr::stateMachine().getStateAt(mEnteringStateLabel).draw(renderer);
    renderer.pop();
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
    }else{
       updateCenters();
    }

}

void TransitionState::updateCenters()
{
    float tVal = mTweening.get();
    if(mDirection == TransitionData::GO_UP || mDirection == TransitionData::GO_DOWN){
        int vertMult = mDirection == TransitionData::GO_UP ? 1 : -1;
        mExitingTranslate.y = vertMult * tVal;
        mEnteringTranslate.y = vertMult *(-SF_ARENA_HEIGHT + tVal);
    }else{
        float horiztontalMult = mDirection == TransitionData::GO_LEFT ? 1.f : -1.f;
        mExitingTranslate.x = horiztontalMult * tVal;
        mEnteringTranslate.x = horiztontalMult * (-SF_ARENA_WIDTH + tVal);
    }

}

void TransitionState::onEnter(BaseStateData *data)
{
    mEnteringTranslate = sf::Vector2f();
    mExitingTranslate = sf::Vector2f();
    StateData<TransitionData*> *stData  = 0;
    if(!(stData = dynamic_cast<StateData<TransitionData*>*>(data)))return;

    TransitionData &transition = *stData->data();
    TransitionData::DIRECTION dir = transition.direction;

    std::pair<float,float> tweening = {0,0};

    if(dir == TransitionData::GO_RIGHT || dir == TransitionData::GO_LEFT){
        tweening.second = SF_ARENA_WIDTH;
    }else if(dir == TransitionData::GO_DOWN || dir == TransitionData::GO_UP){
        tweening.second = SF_ARENA_HEIGHT;
    }

    mTweening = twin::makeTwin(tweening.first, tweening.second, mTransitionDuration, twin::easing::backInOut);

    mEnteringStateLabel = stData->data()->enteringStateLabel;
    mExitingStateLabel = stData->data()->exitingStateLabel;
    mEnteringData.swap(stData->data()->enteringData);
    mDirection = dir;
    updateCenters();
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
