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
 * File:   ClientApp.cpp
 * Author: azarias
 *
 * Created on 9 octobre 2017, 18:06
 */

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/Packet.hpp>
#include <iostream>

#include "ClientApp.hpp"
#include "ClientConf.hpp"
#include "Assets.hpp"

#include "states/PlayMultiplayerState.hpp"
#include "states/PlaySoloState.hpp"
#include "states/WaitingState.hpp"
#include "states/EndState.hpp"
#include "states/MenuState.hpp"
#include "states/PauseState.hpp"
#include "states/OptionState.hpp"
#include "states/KeyBindingState.hpp"
#include "states/CreditsState.hpp"
#include "states/SplashScreenState.hpp"

namespace mp {


ClientApp &ClientApp::getInstance()
{
    static ClientApp instance;
    return instance;
}

ClientApp::ClientApp() :
    window(new sf::RenderWindow(sf::VideoMode(SF_ARENA_WIDTH, SF_ARENA_HEIGHT),
           "Pong",
           sf::Style::Default)),
    m_cursor(),
    rManager(),
    m_translator(),
    m_renderer(window),
    game(),
    stateMachine(),
    m_sEngine(rManager),
    m_dialogManager(),
    m_counter(cRManager().get<const sf::Font&>())
{
    socket.setBlocking(false);

    sf::Image img = cRManager().get<const sf::Texture&>(Assets::Icons::Cursor).copyToImage();
    m_cursor.loadFromPixels(img.getPixelsPtr(), img.getSize(), sf::Vector2u(img.getSize().x / 2, img.getSize().y / 2));
    configureWindow();
}

void ClientApp::configureWindow()
{
    window->setFramerateLimit(120);
    window->setMouseCursor(m_cursor);
    window->setKeyRepeatEnabled(false);

    sf::Image img = cRManager().get<const sf::Texture&>(Assets::Icons::Sfml32x32).copyToImage();
    window->setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
}

ClientApp::~ClientApp()
{
    delete window;
}

void ClientApp::initStates()
{
    stateMachine.initiliaze();

    stateMachine.addState<WaitingState>();
    stateMachine.addState<PlayMultiplayerState>();
    stateMachine.addState<EndState>();
    stateMachine.addState<MenuState>();
    stateMachine.addState<OptionState>();
    stateMachine.addState<KeyBindingState>();
    stateMachine.addState<SlideTransition>();
    stateMachine.addState<FadeTransition>();
    stateMachine.addState<PlaySoloState>();
    stateMachine.addState<PauseState>();
    stateMachine.addState<CreditsState>();
    stateMachine.addState<SplashScreenState>();

    OptionState &os = static_cast<OptionState&>(stateMachine.get<OptionState>());
    os.fullScreenSignal.add([this](){this->toggleFullScreen();});
    os.soundSignal.add([this](){
        m_sEngine.isSoundMuted() ? m_sEngine.unmuteSound() : m_sEngine.muteSound();
    });
    os.musicSignal.add([this](){
        m_sEngine.isMusicStoped() ? m_sEngine.startMusic() : m_sEngine.stopMusic();
    });
}

void ClientApp::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed) {
        window->close();
    } else if(event.type == sf::Event::Resized){
        resizeEvent(event);
    } else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F11) {
        static_cast<OptionState&>(stateMachine.get<OptionState>()).toggleFullScreen();
    } else {
        if(!m_dialogManager.handleEvent(event))
            stateMachine.getCurrentState().handleEvent(event);
    }
}

void ClientApp::toggleFullScreen()
{
    if(window)delete window;
    if(m_isFullscreen){
        window = new sf::RenderWindow(sf::VideoMode(SF_ARENA_WIDTH,  SF_ARENA_HEIGHT),
                                      "Pong",
                                      sf::Style::Default,
                                      sf::ContextSettings(0,0,8));
    }else{
        sf::VideoMode fsMode = sf::VideoMode::getFullscreenModes()[0];
        window = new sf::RenderWindow(fsMode,
                                      "Pong",
                                      sf::Style::Fullscreen);
        float left = ((fsMode.width - SF_ARENA_WIDTH) / 2.f) / fsMode.width;
        float top = ((fsMode.height - SF_ARENA_HEIGHT) / 2.f) / fsMode.height;
        float width = (static_cast<float>(SF_ARENA_WIDTH) / fsMode.width);
        float height = (static_cast<float>(SF_ARENA_HEIGHT) / fsMode.height);
        sf::View v(sf::Vector2f(SF_ARENA_WIDTH / 2.f, SF_ARENA_HEIGHT / 2.f), sf::Vector2f(SF_ARENA_WIDTH, SF_ARENA_HEIGHT));
        v.setViewport(sf::FloatRect(left, top, width, height));
        window->setView(v);
    }
    configureWindow();
    m_renderer.updateRenderTarget(window);

    m_isFullscreen = !m_isFullscreen;
}

void ClientApp::resizeEvent(const sf::Event &event)
{
    float width = event.size.width;
    float height = event.size.height;

    if(height < SF_ARENA_HEIGHT || width < SF_ARENA_WIDTH){
        window->setSize(sf::Vector2u(SF_ARENA_WIDTH, SF_ARENA_HEIGHT));
        return;//do not update the view
    }

    float nwX = (width - SF_ARENA_WIDTH) /2.f;
    float nwY = (height - SF_ARENA_HEIGHT)/2.f;

    float nwXRatio = nwX / width;
    float nwYRatio = nwY / height;
    sf::FloatRect visibleArea(nwXRatio, nwYRatio, 1 - (nwXRatio * 2), 1 - (nwYRatio * 2));


    sf::View view(sf::FloatRect(0,0, SF_ARENA_WIDTH, SF_ARENA_HEIGHT));
    view.setViewport(visibleArea);
    window->setView(view);
}

void ClientApp::run(int argc, char** argv)
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    this->setLocale();
    static_cast<OptionState&>(stateMachine.get<OptionState>()).updateLangButtonsIcon();
    stateMachine.setCurrentState<MenuState>();
    sf::Clock clock;

    //temp rect
    sf::RectangleShape rect(sf::Vector2f(SF_ARENA_WIDTH - 4 , SF_ARENA_HEIGHT - 4));
    rect.setOutlineColor(sf::Color::White);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(2);
    rect.setPosition(2, 2);
    //m_sEngine.startMusic();

    while (window->isOpen()) {
        sf::Event ev;
        while (window->pollEvent(ev)) handleEvent(ev);

        window->clear(cc::Colors::backgroundColor);

        sf::Time elapsed = clock.restart();
        m_counter.update(elapsed);
        m_renderer.update(elapsed);
        m_dialogManager.update(elapsed);
        // m_sEngine.update(elapsed);

        stateMachine.getCurrentState().update(elapsed);

        m_renderer
                .render(stateMachine)
                .render(m_dialogManager)
                //.render(m_counter)
                .draw(rect);

        window->display();
    }
    socket.disconnect();
}

void ClientApp::setLocale()
{
    std::string lName = std::locale("").name();
    std::string target = "en";
    auto begin = lName.find("=");
    auto end = lName.find("_");
    if(begin != std::string::npos && end != std::string::npos){
        target = lName.substr(begin + 1, end);
        auto &translations = Assets::I18N::translations;
        if(translations.find(target) == translations.end()){
            target = "en";
        }
    }
    m_translator.setCurrentTranslation(target);
}

void ClientApp::quit()
{
    window->close();
}



bool ClientApp::isFullScreen() const
{
    return m_isFullscreen;
}

Renderer& ClientApp::getRenderer()
{
    return m_renderer;
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

sf::RenderWindow &ClientApp::getWindow()
{
    return *window;
}


DialogManager &ClientApp::getDialogManager()
{
    return m_dialogManager;
}

const sf::RenderWindow &ClientApp::getWindow() const
{
    return *window;
}

const ResourcesManager& ClientApp::getResourcesManager()
{
    return rManager;
}

Translator &ClientApp::getTranslator()
{
    return m_translator;
}

}
