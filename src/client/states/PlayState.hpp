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
 * File:   PlayState.hpp
 * Author: azarias
 *
 * Created on 12/03/2018
 */

#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>

#include "src/client/State.hpp"
#include "src/client/particles/ParticleGenerator.hpp"
#include "src/common/Timer.hpp"
#include "src/lib/twin.hpp"

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
    virtual void render(Renderer &renderer) const override;

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

    /**
     * @brief onBeforeEnter inherited function
     */
    virtual void onBeforeEnter() override;

    /**
     * @brief onAfterLeaving inherited function
     * clears out the particles
     */
    virtual void onAfterLeaving() override;

    /**
     * @brief playerNum getting the number of the player
     * @return
     */
    virtual int playerNum() = 0;

    virtual ~PlayState() override;

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
     * @brief lastCountdownValue last countdown displayed value
     */
    int m_lastCountdownValue = -1;

    /**
     * @brief m_nextParticle time until next particle spawn
     */
    Timer m_nextParticle;

    /**
     * @brief m_particleGenerator used to generate
     * all the particles
     * related to the game
     */
    ParticleGenerator m_particleGenerator;

    /**
     * @brief gameFinisehd wether the game ended
     */
    bool gameFinisehd = false;

};


}

