
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
#include <SFML/Config.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace mp{

class Assets
{
public:
  
    enum Fonts {Whateverittakes = 1, Whateverittakesbold = 2, Quicksand = 3};
    static const std::unordered_map<sf::Uint64, std::string> fonts;

    enum Sounds {Bounce = 4, Loose = 5, Click1 = 6, Rollover1 = 7, PingPong8bitBiiip = 8, Win = 9, Click3 = 10, Click4 = 11, Click2 = 12, PingPong8bitBeeep = 13, Click5 = 14};
    static const std::unordered_map<sf::Uint64, std::string> sounds;

    enum Animations {BallRetract = 15, BallExtend = 16, PaddleExtend = 17, PaddleRetract = 18};
    static const std::unordered_map<sf::Uint64, std::string> animations;

      class IconAtlas {
        public:
          struct Holder {
            const int textureId = 19;
            const sf::IntRect bounds;
          };

          static const Holder arrowDownIcon;
          static const Holder arrowLeftIcon;
          static const Holder arrowRightIcon;
          static const Holder arrowUpIcon;
          static const Holder audioOffIcon;
          static const Holder audioOnIcon;
          static const Holder barsHorizontalIcon;
          static const Holder barsVerticalIcon;
          static const Holder button1Icon;
          static const Holder button2Icon;
          static const Holder button3Icon;
          static const Holder buttonAIcon;
          static const Holder buttonBIcon;
          static const Holder buttonLIcon;
          static const Holder buttonL1Icon;
          static const Holder buttonL2Icon;
          static const Holder buttonRIcon;
          static const Holder buttonR1Icon;
          static const Holder buttonR2Icon;
          static const Holder buttonSelectIcon;
          static const Holder buttonStartIcon;
          static const Holder buttonXIcon;
          static const Holder buttonYIcon;
          static const Holder checkmarkIcon;
          static const Holder contrastIcon;
          static const Holder crossIcon;
          static const Holder downIcon;
          static const Holder downLeftIcon;
          static const Holder downRightIcon;
          static const Holder exclamationIcon;
          static const Holder exitIcon;
          static const Holder exitLeftIcon;
          static const Holder exitRightIcon;
          static const Holder exportIcon;
          static const Holder fastForwardIcon;
          static const Holder gamepadIcon;
          static const Holder gamepad1Icon;
          static const Holder gamepad2Icon;
          static const Holder gamepad3Icon;
          static const Holder gamepad4Icon;
          static const Holder gearIcon;
          static const Holder homeIcon;
          static const Holder importIcon;
          static const Holder informationIcon;
          static const Holder joystickIcon;
          static const Holder joystickLeftIcon;
          static const Holder joystickRightIcon;
          static const Holder joystickUpIcon;
          static const Holder largerIcon;
          static const Holder leaderboardsComplexIcon;
          static const Holder leaderboardsSimpleIcon;
          static const Holder leftIcon;
          static const Holder lockedIcon;
          static const Holder massiveMultiplayerIcon;
          static const Holder medal1Icon;
          static const Holder medal2Icon;
          static const Holder menuGridIcon;
          static const Holder menuListIcon;
          static const Holder minusIcon;
          static const Holder mouseIcon;
          static const Holder movieIcon;
          static const Holder multiplayerIcon;
          static const Holder musicOffIcon;
          static const Holder musicOnIcon;
          static const Holder nextIcon;
          static const Holder openIcon;
          static const Holder pauseIcon;
          static const Holder phoneIcon;
          static const Holder plusIcon;
          static const Holder powerIcon;
          static const Holder previousIcon;
          static const Holder questionIcon;
          static const Holder returnIcon;
          static const Holder rewindIcon;
          static const Holder rightIcon;
          static const Holder saveIcon;
          static const Holder scrollHorizontalIcon;
          static const Holder scrollVerticalIcon;
          static const Holder share1Icon;
          static const Holder share2Icon;
          static const Holder shoppingBasketIcon;
          static const Holder shoppingCartIcon;
          static const Holder siganl1Icon;
          static const Holder signal2Icon;
          static const Holder signal3Icon;
          static const Holder singleplayerIcon;
          static const Holder smallerIcon;
          static const Holder starIcon;
          static const Holder stopIcon;
          static const Holder tabletIcon;
          static const Holder targetIcon;
          static const Holder trashcanIcon;
          static const Holder trashcanOpenIcon;
          static const Holder trophyIcon;
          static const Holder unlockedIcon;
          static const Holder upIcon;
          static const Holder upLeftIcon;
          static const Holder upRightIcon;
          static const Holder videoIcon;
          static const Holder warningIcon;
          static const Holder wrenchIcon;
          static const Holder zoomIcon;
          static const Holder zoomDefaultIcon;
          static const Holder zoomInIcon;
          static const Holder zoomOutIcon;
      };

    enum Atlases {Icon = 19};
    static const std::unordered_map<sf::Uint64, std::string> atlases;


private:
    Assets();

};

}
