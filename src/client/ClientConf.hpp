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
 * File:   ClientConf.hpp
 * Author: azarias
 *
 * Created on 20/3/2018
 */
#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Time.hpp>
#include "src/common/Config.hpp"
#include "src/common/Math.hpp"

namespace mp
{
    //Dimensions (all in meters)
    //Arena
    constexpr int SF_ARENA_WIDTH = ARENA_WIDTH * M_TO_P;
    constexpr int SF_ARENA_HEIGHT = ARENA_HEIGHT * M_TO_P;

    constexpr int SF_DIALOG_WIDTH =  4 * SF_ARENA_WIDTH / 5;
    constexpr int SF_DIALOG_HEIGHT = SF_ARENA_HEIGHT / 3.f;

    constexpr float SF_CENTER_X = SF_ARENA_WIDTH  / 2.f;
    constexpr float SF_CENTER_Y = SF_ARENA_HEIGHT / 2.f;

    constexpr float MAX_ICON_WIDTH = 70.f;
    constexpr float MAX_ICON_HEIGHT = 70.f;

    constexpr int SF_BUTTON_BORDER = 2;

    constexpr int SF_BUTTON_MARGIN = SF_BUTTON_BORDER * 2;

    constexpr int MAX_INPUT_CHARS = 65;


    namespace cc//namespace client conf
    {
        struct Colors {
            static const sf::Color backgroundColor;
            static const sf::Color buttonColor;
            static const sf::Color buttonBorderColor;
            static const sf::Color buttonClickedColor;
            static const sf::Color dialogBackgroundColor;
            static const sf::Color dialogOutlineColor;
            static const sf::Color fontColor;
            static const sf::Color higlithColor;
            static const sf::Color paddleColor;
            static const sf::Color ballColor;
            static const sf::Color wallColor;

            static const sf::Color endWinColor[2];
            static const sf::Color endLoseColor[2];
        };

        struct Times {
            static const sf::Time transitionTime;
            static const sf::Time gainPointLifeTime;
            static const sf::Time explosionLifeTime;
            static const sf::Time trailLifeTime;
            static const sf::Time trailCountdownTime;
        };

    }


}


