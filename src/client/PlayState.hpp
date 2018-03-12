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
 * File:   PlayState.hpp
 * Author: azarias
 *
 * Created on 12/03/2018
 */

#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "State.hpp"

class Player;

class PlayState : public State
{
public:
    PlayState();

    virtual void draw(Renderer &renderer) const override;

    virtual void update(const sf::Time &elapsed) override;

    virtual void handleEvent(const sf::Event &ev) override;

    virtual void onEnter(BaseStateData *data) override;

    virtual void onLeave() override;

    virtual ~PlayState();

private:


    /**
     * @brief m_p1ScoreText score of the player1
     */
    sf::Text m_p1ScoreText;
    /**
     * @brief m_p2ScoreText score of the player2
     */
    sf::Text m_p2ScoreText;

    /**
     * @brief m_countdownText text displayed for
     * the countdown
     */
    sf::Text m_countdownText;

    /**
     * @brief gameFinisehd wether the game ended
     */
    bool gameFinisehd = false;
};

#endif // PLAYSTATE_HPP
