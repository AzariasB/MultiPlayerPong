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

#include "TransitionState.hpp"

#include "src/common/Config.hpp"
#include "src/client/Provider.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/StateMachine.hpp"

#include "src/common/VectorsUtils.hpp"

namespace mp {

TransitionState::TransitionState()
{
}


void TransitionState::render(Renderer &renderer) const
{
    renderer.push()
            .translate(mExitingTranslate)
            .render(pr::stateMachine().getStateAt(mExitingStateLabel))
            .pop()
            .push()
            .translate(mEnteringTranslate)
            .render(pr::stateMachine().getStateAt(mEnteringStateLabel))
            .pop();
}

void TransitionState::update(const sf::Time &elapsed)
{
    mTweening.step(elapsed);
    if(mTweening.progress() == 1.f){
        if(mEnteringData){
            pr::stateMachine().setCurrentState(mEnteringStateLabel, *mEnteringData);
        }else{
            pr::stateMachine().setCurrentState(mEnteringStateLabel);
        }
        pr::stateMachine().getStateAt(mExitingStateLabel).onAfterLeaving();
    }else{
        pr::stateMachine().getStateAt(mExitingStateLabel).update(elapsed);
        pr::stateMachine().getStateAt(mEnteringStateLabel).update(elapsed);
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
        pr::stateMachine().translate(0, vertMult * tVal);
    }else{
        int horiztontalMult = mDirection == TransitionData::GO_LEFT ? 1 : -1;
        mExitingTranslate.x = horiztontalMult * tVal;
        mEnteringTranslate.x = horiztontalMult * (-SF_ARENA_WIDTH + tVal);
        pr::stateMachine().translate(horiztontalMult * tVal, 0);
    }

}

void TransitionState::onEnter(BaseStateData *data)
{
    mEnteringTranslate = sf::Vector2f();
    mExitingTranslate = sf::Vector2f();
    StateData<TransitionData*> *stData  = nullptr;
    if(!(stData = dynamic_cast<StateData<TransitionData*>*>(data)))return;

    TransitionData &transition = *stData->data();
    TransitionData::DIRECTION dir = transition.direction;

    std::pair<float,float> tweening = {0,0};

    if(dir == TransitionData::GO_RIGHT || dir == TransitionData::GO_LEFT){
        tweening.second = SF_ARENA_WIDTH;
    }else if(dir == TransitionData::GO_DOWN || dir == TransitionData::GO_UP){
        tweening.second = SF_ARENA_HEIGHT;
    }

    mTweening = twin::makeTwin(tweening.first, tweening.second, cc::Times::transitionTime, twin::easing::backInOut);

    mEnteringStateLabel = transition.enteringStateLabel;
    mExitingStateLabel = transition.exitingStateLabel;
    m_tickEnteringState = transition.updateEnteringState;
    m_tickExistingState = transition.updateExistingState;
    mEnteringData.swap(transition.enteringData);
    mDirection = dir;
    updateCenters();
}

void TransitionState::onBeforeLeaving()
{
    mEnteringData = {};
}

void TransitionState::handleEvent(const sf::Event &ev)
{
    if(mEnteringStateLabel != -1)
        pr::stateMachine().getStateAt(mEnteringStateLabel).handleEvent(ev);
}


}
