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
 * File:   Provider.cpp
 * Author: azarias
 *
 * Created on 18/11/2017
 */
#include "Provider.hpp"
#include "ClientApp.hpp"
#include "particles/ParticleGenerator.hpp"
#include "Renderer.hpp"
#include "Translator.hpp"
#include "SoundEngine.hpp"
#include "src/common/Game.hpp"
#include "src/common/Player.hpp"

namespace mp {

Game &pr::game()
{
    return ClientApp::getInstance().getGame();
}

const ResourcesManager &pr::resourceManager()
{
    return ClientApp::getInstance().getResourcesManager();
}

StateMachine &pr::stateMachine()
{
    return ClientApp::getInstance().getStateMachine();
}

sf::Vector2f pr::mapPixelToCoords(const sf::Vector2i &coords)
{
    return ClientApp::getInstance().getWindow().mapPixelToCoords(coords);
}

SoundEngine &pr::soundEngine()
{
    return ClientApp::getInstance().getSoundEngine();
}

Renderer &pr::renderer()
{
    return ClientApp::getInstance().getRenderer();
}

sf::TcpSocket &pr::socket()
{
    return ClientApp::getInstance().getSocket();
}

Player &pr::player()
{
    return ClientApp::getInstance().getPlayer();
}

DialogManager &pr::dialogManager()
{
    return ClientApp::getInstance().getDialogManager();
}

Translator &pr::translator()
{
    return ClientApp::getInstance().getTranslator();
}

}
