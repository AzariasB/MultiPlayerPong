

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
 * File:   Assets.cpp
 * Author: azarias
 *
 * Created on 04/07/2018
 */
/*
 * This file is automatically generated
 * All modifications done to this file may be lost
 */
	

#include "Assets.hpp"

namespace mp{

const std::unordered_map<sf::Uint64, std::string> Assets::fonts = {
{ Assets::Fonts::Whateverittakes, ":/fonts/whateverittakes.ttf" },
{ Assets::Fonts::Whateverittakesbold, ":/fonts/whateverittakesbold.ttf" },
{ Assets::Fonts::Quicksand, ":/fonts/quicksand.otf" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::sounds = {
{ Assets::Sounds::Bounce, ":/sounds/bounce.wav" },
{ Assets::Sounds::Loose, ":/sounds/loose.wav" },
{ Assets::Sounds::Click1, ":/sounds/click1.wav" },
{ Assets::Sounds::Rollover1, ":/sounds/rollover1.wav" },
{ Assets::Sounds::PingPong8bitBiiip, ":/sounds/ping_pong_8bit_biiip.wav" },
{ Assets::Sounds::Win, ":/sounds/win.wav" },
{ Assets::Sounds::Click3, ":/sounds/click3.wav" },
{ Assets::Sounds::Click4, ":/sounds/click4.wav" },
{ Assets::Sounds::Click2, ":/sounds/click2.wav" },
{ Assets::Sounds::PingPong8bitBeeep, ":/sounds/ping_pong_8bit_beeep.ogg" },
{ Assets::Sounds::Click5, ":/sounds/click5.wav" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::shaders = {
{ Assets::Shaders::Alpha, ":/shaders/alpha.frag" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::animations = {
{ Assets::Animations::BallRetract, ":/animations/ball_retract.png" },
{ Assets::Animations::BallExtend, ":/animations/ball_extend.png" },
{ Assets::Animations::PaddleExtend, ":/animations/paddle_extend.png" },
{ Assets::Animations::PaddleRetract, ":/animations/paddle_retract.png" }
};

const std::unordered_map<sf::Uint64, std::string> Assets::icons = {
{ Assets::Icons::Qt, ":/icons/qt.png" },
{ Assets::Icons::Box2d, ":/icons/box2d.png" },
{ Assets::Icons::Sfml32x32, ":/icons/sfml32x32.png" },
{ Assets::Icons::Sfml, ":/icons/sfml.png" },
{ Assets::Icons::Cursor, ":/icons/cursor.png" }
};

const Assets::IconAtlas::Holder Assets::IconAtlas::arrowDownIcon = {25, sf::IntRect(0, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::arrowLeftIcon = {25, sf::IntRect(0, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::arrowRightIcon = {25, sf::IntRect(0, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::arrowUpIcon = {25, sf::IntRect(0, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::audioOffIcon = {25, sf::IntRect(0, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::audioOnIcon = {25, sf::IntRect(0, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::barsHorizontalIcon = {25, sf::IntRect(0, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::barsVerticalIcon = {25, sf::IntRect(0, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::button1Icon = {25, sf::IntRect(0, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::button2Icon = {25, sf::IntRect(0, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::button3Icon = {25, sf::IntRect(0, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonAIcon = {25, sf::IntRect(0, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonBIcon = {25, sf::IntRect(0, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonLIcon = {25, sf::IntRect(200, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonL1Icon = {25, sf::IntRect(500, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonL2Icon = {25, sf::IntRect(500, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonRIcon = {25, sf::IntRect(500, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonR1Icon = {25, sf::IntRect(500, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonR2Icon = {25, sf::IntRect(400, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonSelectIcon = {25, sf::IntRect(400, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonStartIcon = {25, sf::IntRect(400, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonXIcon = {25, sf::IntRect(400, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::buttonYIcon = {25, sf::IntRect(400, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::checkmarkIcon = {25, sf::IntRect(400, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::contrastIcon = {25, sf::IntRect(400, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::crossIcon = {25, sf::IntRect(400, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::downIcon = {25, sf::IntRect(400, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::downLeftIcon = {25, sf::IntRect(400, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::downRightIcon = {25, sf::IntRect(400, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exclamationIcon = {25, sf::IntRect(400, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exitIcon = {25, sf::IntRect(400, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exitLeftIcon = {25, sf::IntRect(400, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exitRightIcon = {25, sf::IntRect(400, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::exportIcon = {25, sf::IntRect(400, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::fastForwardIcon = {25, sf::IntRect(400, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepadIcon = {25, sf::IntRect(400, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad1Icon = {25, sf::IntRect(400, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad2Icon = {25, sf::IntRect(400, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad3Icon = {25, sf::IntRect(300, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gamepad4Icon = {25, sf::IntRect(300, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::gearIcon = {25, sf::IntRect(300, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::homeIcon = {25, sf::IntRect(300, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::importIcon = {25, sf::IntRect(300, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::informationIcon = {25, sf::IntRect(300, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickIcon = {25, sf::IntRect(300, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickLeftIcon = {25, sf::IntRect(300, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickRightIcon = {25, sf::IntRect(300, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::joystickUpIcon = {25, sf::IntRect(300, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::largerIcon = {25, sf::IntRect(300, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::leaderboardsComplexIcon = {25, sf::IntRect(300, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::leaderboardsSimpleIcon = {25, sf::IntRect(300, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::leftIcon = {25, sf::IntRect(300, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::lockedIcon = {25, sf::IntRect(300, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::massiveMultiplayerIcon = {25, sf::IntRect(300, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::medal1Icon = {25, sf::IntRect(300, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::medal2Icon = {25, sf::IntRect(300, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::menuGridIcon = {25, sf::IntRect(300, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::menuListIcon = {25, sf::IntRect(300, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::minusIcon = {25, sf::IntRect(200, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::mouseIcon = {25, sf::IntRect(200, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::movieIcon = {25, sf::IntRect(200, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::multiplayerIcon = {25, sf::IntRect(200, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::musicOffIcon = {25, sf::IntRect(200, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::musicOnIcon = {25, sf::IntRect(200, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::nextIcon = {25, sf::IntRect(200, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::openIcon = {25, sf::IntRect(500, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::pauseIcon = {25, sf::IntRect(200, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::phoneIcon = {25, sf::IntRect(200, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::plusIcon = {25, sf::IntRect(200, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::powerIcon = {25, sf::IntRect(200, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::previousIcon = {25, sf::IntRect(200, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::questionIcon = {25, sf::IntRect(200, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::returnIcon = {25, sf::IntRect(200, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::rewindIcon = {25, sf::IntRect(200, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::rightIcon = {25, sf::IntRect(200, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::saveIcon = {25, sf::IntRect(200, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::scrollHorizontalIcon = {25, sf::IntRect(200, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::scrollVerticalIcon = {25, sf::IntRect(200, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::share1Icon = {25, sf::IntRect(100, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::share2Icon = {25, sf::IntRect(100, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::shoppingBasketIcon = {25, sf::IntRect(100, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::shoppingCartIcon = {25, sf::IntRect(100, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::siganl1Icon = {25, sf::IntRect(100, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::signal2Icon = {25, sf::IntRect(100, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::signal3Icon = {25, sf::IntRect(100, 1300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::singleplayerIcon = {25, sf::IntRect(100, 1200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::smallerIcon = {25, sf::IntRect(100, 1100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::starIcon = {25, sf::IntRect(100, 1000, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::stopIcon = {25, sf::IntRect(100, 900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::tabletIcon = {25, sf::IntRect(100, 800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::targetIcon = {25, sf::IntRect(100, 700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::trashcanIcon = {25, sf::IntRect(100, 600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::trashcanOpenIcon = {25, sf::IntRect(100, 500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::trophyIcon = {25, sf::IntRect(100, 400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::unlockedIcon = {25, sf::IntRect(100, 300, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::upIcon = {25, sf::IntRect(100, 200, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::upLeftIcon = {25, sf::IntRect(100, 100, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::upRightIcon = {25, sf::IntRect(100, 0, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::videoIcon = {25, sf::IntRect(0, 1900, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::warningIcon = {25, sf::IntRect(0, 1800, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::wrenchIcon = {25, sf::IntRect(0, 1700, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomIcon = {25, sf::IntRect(0, 1600, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomDefaultIcon = {25, sf::IntRect(0, 1500, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomInIcon = {25, sf::IntRect(0, 1400, 100, 100) };
const Assets::IconAtlas::Holder Assets::IconAtlas::zoomOutIcon = {25, sf::IntRect(0, 1300, 100, 100) };

const std::unordered_map<sf::Uint64, std::string> Assets::atlases = {
{ Assets::Atlases::Icon , ":/atlases/icon.png" }
};

}

