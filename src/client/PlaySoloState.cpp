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

/*
 * File:   PlaySoloState.cpp
 * Author: azarias
 *
 * Created on 12/03/2018
 */

#include "PlaySoloState.hpp"
#include "Provider.hpp"

PlaySoloState::PlaySoloState():
    PlayState()
{
    pr::connect(pr::game().countdownEndedEvent, &Game::setGameState, &pr::game(), GAMESTATE::PLAYING);
    pr::game().getPlayer2().getPaddle().setIsAI(true);
    pr::connect(pr::game().lostEvent, &PlaySoloState::handleLoss, this);
}

void PlaySoloState::handleEvent(const sf::Event &ev)
{
    PlayState::handleEvent(ev);
}

void PlaySoloState::handleLoss(int looser)
{
    bool playerWon = looser == 2;
    pr::game().getPlayer1().setIsWinner(playerWon);
    pr::game().getPlayer2().setIsWinner(!playerWon);
}

PlaySoloState::~PlaySoloState()
{

}
