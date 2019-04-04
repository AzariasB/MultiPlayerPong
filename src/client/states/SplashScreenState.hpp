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
 * File:   SplashScreenState.hpp
 * Author: azarias
 *
 * Created on 5/6/2018
 */
#pragma once

#include "src/client/State.hpp"
#include "src/common/Timer.hpp"
#include "src/lib/twin.hpp"

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "src/client/Assets.hpp"


namespace mp {


/**
 * @brief The SplashScreenState class state used
 * to show differents informations about the game
 * and the techs used
 */
class SplashScreenState : public State
{
public:
    /**
     * @brief SplashScreenState constructor
     */
    SplashScreenState();

    /**
     * @brief update overriden method
     * @param elapsed time since last update
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief render overriden method
     * @param renderer object to draw object on screen
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief handleEvent overriden method
     * @param ev event trigerred by the user
     */
    void handleEvent(const sf::Event &ev) override;

private:
    /**
     * @brief insertSprite adds a sprite to draw
     * @param id id of the texture to use
     * @param xCenter center of the sprite
     * @return
     */
    sf::Sprite &insertSprite(const Assets::Icons &id, float xCenter);

    /**
     * @brief m_timer timer to do different action within the splashscreen state
     */
    Timer m_timer;

    /**
      * The sprites to draw an screen
      */
    std::vector<sf::Sprite> m_sprites = {};

    /**
     * @brief m_games text for 'games' text
     */
    sf::Text m_games;

    /**
     * @brief m_ema text for 'ema' text
     */
    sf::Text m_ema;

    /**
     * @brief m_emaPos tweening for the position of 'ema' text
     */
    twin::Twin<float> m_emaPos;

    /**
     * @brief m_emaScale tweening for the scale of 'ema' text
     */
    twin::Twin<float> m_emaScale;
};


}
