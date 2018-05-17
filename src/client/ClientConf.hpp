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
 * File:   ClientConf.hpp
 * Author: azarias
 *
 * Created on 20/3/2018
 */
#pragma once

#include <SFML/Graphics/Color.hpp>


namespace mp
{

    constexpr int SF_DIALOG_WIDTH = 700;
    constexpr int SF_DIALOG_HEIGHT = 200;

    //Dimensions (all in meters)
    //Arena
    constexpr int SF_ARENA_WIDTH = 800;
    constexpr int SF_ARENA_HEIGHT = 600;


    namespace cc//namespace client conf
    {
        /**
 * @brief The STATE_TYPE enum associate with each state, an int (enum)
 * to store these in the state machine, and retrieve them later
 */
        enum STATE_TYPE {
            MENU,//First state
            PLAY_MULTIPLAYER,
            PLAY_SOLO,
            PAUSE,
            CREDITS,
            OPTIONS,
            KEY_BINDINGS,
            WAITING,
            FINISHED,
            TRANSITION
        };

        namespace colors {
            const sf::Color backgroundColor = sf::Color(0,10, 30);
            const sf::Color dialogBackgroundColor = sf::Color(0,20, 50);
            const sf::Color dialogOutlineColor = sf::Color(220, 220, 220);
            const sf::Color fontColor = sf::Color(220, 220, 220);
            const sf::Color paddleColor = sf::Color(128, 255, 0);
            const sf::Color ballColor = sf::Color(226, 88, 34);
            const sf::Color wallColor = sf::Color(200,200,200);
        }

    }


}


