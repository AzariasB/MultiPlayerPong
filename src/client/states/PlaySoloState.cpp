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
 * File:   PlaySoloState.cpp
 * Author: azarias
 *
 * Created on 12/03/2018
 */

#include "PlaySoloState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientApp.hpp"


namespace mp {


PlaySoloState::PlaySoloState():
    PlayState()
{
}

void PlaySoloState::onBeforeEnter()
{
    PlayState::onBeforeEnter();

    if(ClientApp::getInstance().getPNumber() == 3) {
        pr::game().getPlayer2().getPaddle().setIsAI(false);
    } else {
        pr::game().getPlayer2().getPaddle().setIsAI(true);
    }

    pr::game().countdownEndedSignal.add([](){pr::game().setGameState(GAMESTATE::PLAYING);});

    pr::game().lostSignal.add([](int looser){
        bool amWinner = looser == 2;
        pr::game().getPlayer1().setIsWinner(amWinner);
        pr::game().getPlayer2().setIsWinner(!amWinner);
    });

    pr::game().hitPaddleSignal.add([](std::size_t pNum, b2Vec2){
        (pNum == 1 ? pr::game().getPlayer1() : pr::game().getPlayer2()).gainPoint();
    });
}

void PlaySoloState::onAfterLeaving()
{
    PlayState::onAfterLeaving();

    pr::game().countdownEndedSignal.clear();
    pr::game().lostSignal.clear();
}

void PlaySoloState::handleEvent(const sf::Event &ev)
{
    PlayState::handleEvent(ev);
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::stateMachine().fadeTo(cc::PAUSE);
    }
}

PlaySoloState::~PlaySoloState()
{

}

}
