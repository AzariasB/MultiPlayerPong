
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
 * File:   Assets.hpp
 * Author: azarias
 *
 * Created on 21/5/2018
 */
/*
 * This file is automatically generated
 * All modifications done to this file may be lost
 */

#pragma once

#include <unordered_map>

namespace mp{

class Assets
{
public:
  
    enum Fonts {Whateverittakes = 1, Whateverittakesbold = 2, Quicksand = 3};
    static const std::unordered_map<Fonts, std::string> fonts;

    enum Sounds {Bounce = 4, Click1 = 5, Rollover1 = 6, PingPong8bitBiiip = 7, Click3 = 8, Click4 = 9, Click2 = 10, PingPong8bitBeeep = 11, Click5 = 12};
    static const std::unordered_map<Sounds, std::string> sounds;

    enum Animations {BallRetract = 13, BallExtend = 14, PaddleExtend = 15, PaddleRetract = 16};
    static const std::unordered_map<Animations, std::string> animations;

    enum Icons {Forward = 17, Gear = 18, Information = 19, Return = 20, Sound = 21, Arrowup = 22, Exitleft = 23, Larger = 24, Wrench = 25, Cross = 26, Arrowdown = 27, Singleplayer = 28, Power = 29, Multiplayer = 30};
    static const std::unordered_map<Icons, std::string> icons;


private:
    Assets();

};

}
