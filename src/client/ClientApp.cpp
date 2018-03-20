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
 * File:   ClientApp.cpp
 * Author: azarias
 *
 * Created on 9 octobre 2017, 18:06
 */

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <QDebug>

#include "ClientApp.hpp"
#include "states/PlayMultiplayerState.hpp"
#include "states/PlaySoloState.hpp"
#include "states/WaitingState.hpp"
#include "states/EndState.hpp"
#include "states/MenuState.hpp"
#include "states/OptionState.hpp"
#include "states/KeyBindingState.hpp"
#include "states/TransitionState.hpp"
#include "ClientConf.hpp"


ClientApp &ClientApp::getInstance()
{
    static ClientApp instance;
    return instance;
}

ClientApp::ClientApp() :
    window(sf::VideoMode(SF_ARENA_WIDTH,  SF_ARENA_HEIGHT), "Pong", sf::Style::Default),
    renderer(window),
    game(),
    stateMachine(),
    m_sEngine(rManager),
    m_keyBinding()
{
    //Textures
    rManager.registerTexture(":/icons.png", "icons");
    rManager.registerTexture(":/sketchy.jpg","sketchy");
    //rManager.registerShader(":/shaders/wobble.frag","main"); /* shader not working on me computer :( */
    rManager.registerTexture(":/animations/paddle_extend","paddle_extend");
    rManager.registerTexture(":/animations/paddle_retract","paddle_retract");
    rManager.registerTexture(":/animations/ball_extend","ball_extend");
    rManager.registerTexture(":/animations/ball_retract","ball_retract");

    socket.setBlocking(false);
    m_sEngine.saveSound(SoundEngine::BOUNCE, ":/bounce.wav");
    window.setKeyRepeatEnabled(false);
}

ClientApp::~ClientApp()
{
}

void ClientApp::initStates()
{
    stateMachine.addState<WaitingState>(cc::WAITING);
    stateMachine.addState<PlayMultiplayerState>(cc::PLAY_MULTIPLAYER);
    stateMachine.addState<EndState>(cc::FINISHED);
    stateMachine.addState<MenuState>(cc::MENU);
    stateMachine.addState<OptionState>(cc::OPTIONS);
    stateMachine.addState<KeyBindingState>(cc::KEY_BINDINGS);
    stateMachine.addState<TransitionState>(cc::TRANSITION);
    stateMachine.addState<PlaySoloState>(cc::PLAY_SOLO);
}

void ClientApp::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed) {
        window.close();
    } else if(event.type == sf::Event::Resized){
        resizeEvent(event);
    } else {
        stateMachine.getCurrentState().handleEvent(event);
    }
}

void ClientApp::resizeEvent(const sf::Event &event)
{
    float width = event.size.width;
    float height = event.size.height;
    sf::Vector2u minSize(width, height);
    if(width < SF_ARENA_WIDTH)
        minSize.x = SF_ARENA_WIDTH;
    if(height < SF_ARENA_HEIGHT)
        minSize.y = SF_ARENA_HEIGHT;

    window.setSize(minSize);


    float nwX = (width - SF_ARENA_WIDTH) /2.f;
    float nwY = (height - SF_ARENA_HEIGHT)/2.f;

    float nwXRatio = nwX / width;
    float nwYRatio = nwY / height;
    sf::FloatRect visibleArea(nwXRatio, nwYRatio, 1 , 1 );

    sf::View view(sf::FloatRect(0,0, width, height));
    view.setViewport(visibleArea);
    window.setView(view);
}

void ClientApp::run(int argc, char** argv)
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    stateMachine.setCurrentState(cc::MENU);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev))
            handleEvent(ev);

        window.clear(sf::Color::Black);

        sf::Time elapsed = clock.restart();
        renderer.update(elapsed);
        stateMachine.getCurrentState().update(elapsed);
        stateMachine.getCurrentState().draw(renderer);

        window.display();
    }
    socket.disconnect();
    stateMachine.getCurrentState().onLeave(); //Close last threads
}

void ClientApp::quit()
{
    window.close();
}

const Player& ClientApp::getPlayer() const
{
    if (!hasPNumber())throw std::out_of_range("player number is out of range equals (" + std::to_string(m_number) + ")");
    return m_number == 1 ? game.getPlayer1() : game.getPlayer2();
}

Player& ClientApp::getPlayer()
{
    if (!hasPNumber())throw std::out_of_range("player number is out of range equals (" + std::to_string(m_number) + ")");
    return m_number == 1 ? game.getPlayer1() : game.getPlayer2();
}

bool ClientApp::isWinner() const
{
    return hasPNumber() && getPlayer().isWinner();
}

void ClientApp::setPNumber(int pNumber)
{
    m_number = pNumber;
}

bool ClientApp::hasPNumber() const
{
    return m_number == 1 || m_number == 2;
}

Renderer& ClientApp::getRenderer()
{
    return renderer;
}

const Game& ClientApp::getGame() const
{
    return game;
}

Game& ClientApp::getGame()
{
    return game;
}

sf::TcpSocket& ClientApp::getSocket()
{
    return socket;
}

StateMachine& ClientApp::getStateMachine()
{
    return stateMachine;
}

SoundEngine& ClientApp::getSoundEngine()
{
    return m_sEngine;
}

const SoundEngine& ClientApp::getSoundEngine() const
{
    return m_sEngine;
}

ParticleGenerator &ClientApp::getParticleGenerator()
{
    return m_particleGenerator;
}

sf::RenderWindow &ClientApp::getWindow()
{
    return window;
}

KeyBinding &ClientApp::getKeyBindings()
{
    return m_keyBinding;
}

const ParticleGenerator &ClientApp::getParticleGenerator() const
{
    return m_particleGenerator;
}

const sf::RenderWindow &ClientApp::getWindow() const
{
    return window;
}

const ResourcesManager& ClientApp::getResourcesManager()
{
    return rManager;
}

const KeyBinding &ClientApp::getKeyBindings() const
{
    return m_keyBinding;
}

