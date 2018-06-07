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
 * File:   ClientConf.cpp
 * Author: azarias
 *
 * Created on 19/5/2018
 */

#include "ClientConf.hpp"

namespace mp {

//Colors
const sf::Color cc::Colors::backgroundColor = sf::Color(0,10, 30);
const sf::Color cc::Colors::buttonColor = sf::Color(10, 40, 120);
const sf::Color cc::Colors::buttonBorderColor = sf::Color(230, 230, 230);
const sf::Color cc::Colors::buttonClickedColor = sf::Color(60, 90, 170);
const sf::Color cc::Colors::dialogBackgroundColor = sf::Color(0,20, 50);
const sf::Color cc::Colors::dialogOutlineColor = sf::Color(220, 220, 220);
const sf::Color cc::Colors::fontColor = sf::Color(220, 220, 220);
const sf::Color cc::Colors::higlithColor = sf::Color(255, 89, 84);
const sf::Color cc::Colors::paddleColor = sf::Color(128, 255, 0);
const sf::Color cc::Colors::ballColor = sf::Color(226, 88, 34);
const sf::Color cc::Colors::wallColor = sf::Color(200,200,200);

const sf::Color cc::Colors::endWinColor[2] =  {sf::Color(108, 191, 46), sf::Color(72, 127, 31)};
const sf::Color cc::Colors::endLoseColor[2] = {sf::Color(191, 63, 61), sf::Color(124, 42, 41) };


//Times
const sf::Time cc::Times::transitionTime = sf::milliseconds(500);
const sf::Time cc::Times::gainPointLifeTime = sf::seconds(2);
const sf::Time cc::Times::explosionLifeTime = sf::milliseconds(500);
const sf::Time cc::Times::trailLifeTime = sf::milliseconds(1000);
const sf::Time cc::Times::trailCountdownTime = sf::milliseconds(10);

}
