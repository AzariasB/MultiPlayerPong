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
 * File:   Provider.hpp
 * Author: azarias
 *
 * Created on 18/11/2017
 */
#pragma once

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Network/TcpSocket.hpp>

namespace mp {

class Game;
class StateMachine;
class EventManager;
class KeyBinding;
class SoundEngine;
class ParticleGenerator;
class Renderer;
class Player;
class ResourcesManager;
class DialogManager;
class Translator;


namespace pr {
Game &game();

StateMachine &stateMachine();

const ResourcesManager &resourceManager();

sf::Vector2f mapPixelToCoords(const sf::Vector2i &coords);

SoundEngine &soundEngine();

Renderer &renderer();

sf::TcpSocket &socket();

Player &player();

DialogManager &dialogManager();

Translator &translator();

}//namespace pr


}//namespace mp
