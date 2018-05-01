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

/*
 * File:   PlayState.hpp
 * Author: azarias
 *
 * Created on 12/03/2018
 */

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include "src/client/State.hpp"

namespace mp {

class Player;

/**
 * @brief The PlayState class
 * abstract class used by multiplayer and solo states
 * performs all the commons parts of rendering, handling
 * events, state switching and point managment
 */
class PlayState : public State
{
public:
    /**
     * @brief PlayState constructor
     */
    PlayState();

    /**
     * @brief draw draws all the entity of the stage
     * @param renderer
     */
    virtual void draw(Renderer &renderer) const override;

    /**
     * @brief update updates all the entities of the stage
     * @param elapsed
     */
    virtual void update(const sf::Time &elapsed) override;

    /**
     * @brief handleEvent handles the player event
     * @param ev sfml event
     */
    virtual void handleEvent(const sf::Event &ev) override;

    virtual ~PlayState();

private:
    void bounced(std::size_t pNum, sf::Vector2f position);

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
     * @brief m_nextParticle time until next particle spawn
     */
    sf::Time m_nextParticle;

    /**
     * @brief gameFinisehd wether the game ended
     */
    bool gameFinisehd = false;
};


}

