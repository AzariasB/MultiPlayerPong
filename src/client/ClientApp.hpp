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
 * File:   ClientApp.h
 * Author: azarias
 *
 * Created on 9 octobre 2017, 18:06
 */

#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <deque>

#include "src/common/Application.hpp"
#include "src/common/Game.hpp"
#include "Renderer.hpp"
#include "StateMachine.hpp"
#include "ResourcesManager.hpp"
#include "SoundEngine.hpp"
#include "particles/ParticleGenerator.hpp"
#include "KeyBinding.hpp"
#include "widgets/DialogManager.hpp"
#include "widgets/FPSCounter.hpp"


namespace mp {

/**
 * @brief The ClientApp class the client application
 * contains the game, and all the data necessary for the client
 * to run (the socket, the rendrer, the resource manager, the soundEngine, ...)
 * Could be designed as a Singleton. Is passed to all the sub-instances of the widgets
 */
class ClientApp : public Application {
public:

    static ClientApp &getInstance();

    /**
     * @brief run starts the main loop, until the window closes
     * @param argc the number of argument received
     * @param argv the arguments
     */
    void run(int argc, char** argv) override;

    /**
     * @brief initStates adds all the states
     * Cannot be called in the constructor, since the state
     * needs the ClientApp to be fully constructed
     */
    void initStates();

    /**
     * @brief getGame the game object
     * @return the game object
     */
    Game& getGame();

    /**
     * @brief getGame const version of getGame
     * @return a const reference to the game
     */
    const Game &getGame() const;

    /**
     * @brief getRenderer the renderer
     * @return the renderer
     */
    Renderer &getRenderer();

    /**
     * @brief getPlayer the player for this client application (could be player1 or player2 of the
     * game object)
     * @return the player associated with this application
     */
    Player &getPlayer();

    /**
     * @brief getPlayer const version of getPlayer
     * @return a const reference to the player
     */
    const Player &getPlayer() const;

    /**
     * @brief getSocket reference to the client's socket
     * @return a reference to the socket
     */
    sf::TcpSocket &getSocket();

    /**
     * @brief setPNumber sets the player number (1 or 2)
     * @param pNumber the number of the player
     */
    void setPNumber(int pNumber);

    /**
     * @brief getStateMachine reference to the state machine
     * @return a reference to the state machine
     */
    StateMachine &getStateMachine();

    /**
     * @brief getSoundEngine reference to the sound engine
     * @return a reference to the sound engine
     */
    SoundEngine &getSoundEngine();

    /**
     * @brief getSoundEngine const reference to const sound engine
     * @return const reference to const sound engine
     */
    const SoundEngine &getSoundEngine() const;

    /**
     * @brief getParticleGenerator reference to the particle generator
     * @return a reference to the particle generator
     */
    ParticleGenerator &getParticleGenerator();

    /**
     * @brief getParticleGenerator const reference to the particle generator
     * @return a const reference to the particle generator
     */
    const ParticleGenerator &getParticleGenerator() const;


    sf::RenderWindow &getWindow();

    /**
     * @brief getWindow const reference to the renderWindow
     * @return a const reference to the render window
     */
    const sf::RenderWindow &getWindow() const;

    /**
     * @brief getResourcesManager const reference to the resource manager
     * @return const reference to the resource manager
     */
    const ResourcesManager &getResourcesManager();


    /**
     * @brief getKeyBindings access to the keybinding options
     * @return a reference to the client's key binding
     */
    KeyBinding &getKeyBindings();

    /**
     * @brief getKeyBindings const access to key binding
     * @return a const reference to the client's key bindings
     */
    const KeyBinding &getKeyBindings() const;


    /**
     * @brief getDialogManager access to the dialogmanager
     * @return reference to the client's dialog manager
     */
    DialogManager &getDialogManager();

    /**
     * @brief isWinner wether the app's client is the winner (false if the game is still running)
     * @return wether the app's client won the game
     */
    bool isWinner() const;

    /**
     * @brief isFullScreen if the window is fullscreen
     * @return
     */
    bool isFullScreen() const;

    /**
     * @brief quit closes the window to finish the main loop
     */
    void quit();

    /**
     * @brief toggleFullScreen toggles the
     * fullscreen window
     */
    void toggleFullScreen();

    virtual ~ClientApp();

    ClientApp(const ClientApp &) = delete;
    void operator=(const ClientApp &) = delete;

private:
    /**
     * @brief ClientApp default constructor, no data to input
     */
    ClientApp();

    /**
     * @brief hasPNumber if the current number of the app is 1 or 2
     * @return wether the client number is a valid client number
     */
    bool hasPNumber() const;

    /**
     * @brief handleEvent handles the sfml event (closes the window if necessary)
     * otherwise, call the event handler of the current state
     * @param event the event to handle
     */
    void handleEvent(const sf::Event &event);

    /**
     * @brief resizeEvent when the window is resized
     * @param event the event object
     */
    void resizeEvent(const sf::Event &event);

    /**
     * @brief window window to use to get events
     * and render stuff
     */
    sf::RenderWindow *window;

    /**
     * @brief m_isFullscreen wether the current window
     * is fullscreen
     */
    bool m_isFullscreen = false;

    /**
     * @brief renderer Object to use to render the game objects,
     * and all the drawable objects
     */
    Renderer renderer;

    /**
     * @brief game the game
     */
    Game game;

    /**
     * @brief stateMachine the state machine, in which we'll store
     * all our states
     */
    StateMachine stateMachine;

    /**
     * @brief m_number the number of the player
     * is sent by the server
     */
    int m_number = -1;

    /**
     * @brief socket the socket used to connect to the
     * server
     */
    sf::TcpSocket socket;

    /**
     * @brief rManager the resource manager, holds all the data
     * used for the graphics and the sound (client related)
     */
    ResourcesManager rManager;

    /**
     * @brief m_sEngine the sound engine : to have an easy
     * access to play sounds
     */
    SoundEngine m_sEngine;

    /**
     * @brief m_particleGenerator particle generator
     * used to create explosions effects an such
     */
    ParticleGenerator m_particleGenerator;

    /**
     * @brief m_keyBinding the objects that contains all
     * the key bindings
     */
    KeyBinding m_keyBinding;

    /**
     * @brief m_dialogManager the dialog manager
     * used to create different types of dialogs
     */
    DialogManager m_dialogManager;

    /**
     * @brief m_counter counter to show
     * the game's fps
     */
    FPSCounter m_counter;

};

}

