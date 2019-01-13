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
 * File:   Game.h
 * Author: azarias
 *
 * Created on 11 octobre 2017, 10:09
 */

#pragma once


#include <SFML/Network/Packet.hpp>
#include <SFML/System/Time.hpp>
#include <Box2D/Box2D.h>

#include "Wall.hpp"
#include "Input.hpp"
#include "Config.hpp"
#include "Paddle.hpp"
#include "Player.hpp"
#include "Signal.hpp"
#include "ContactListener.hpp"

namespace sf {
class Event;
}

namespace mp {

/**
 * @brief The GAMESTATE enum current state of the game
 */
enum GAMESTATE{
    COUNTDOWN,
    PLAYING,
};

/**
 * @brief The Game class one of the main classes of the app
 * Contains all the data relative to the game : it's component
 * and the resources necessary for these components to work
 * (like the event manager)
 * this class is supposed to be thread safe
 */
class Game {
public:
    /**
     * @brief Game constructor
     */
    Game();

    virtual ~Game();

    /**
     * @brief update updates the game states, and all it's sub-components
     * @param dtS the time since the last update
     */
    void update(const sf::Time &elapsed);

    /**
     * @brief handleEvent handles the given event, trigerred by the given player
     * @param ev the sfml event
     * @param player the player who trigerred the event
     */
    void handleEvent(const sf::Event &ev);

    /**
     * @brief getBall const reference to the ball object
     * @return const reference to the ball object
     */
    const Ball& getBall() const;

    /**
     * @brief getPlayer1 const reference to the first player
     * @return const reference to the first player
     */
    const Player &getPlayer1() const;

    /**
     * @brief getPlayer1 reference to the first player
     * @return reference to the first player
     */
    Player &getPlayer1();

    /**
     * @brief getPlayer2 reference to the second player
     * @return reference to the second player
     */
    Player &getPlayer2();

    /**
     * @brief mUpperWall gets the upper wall of the arena
     * @return
     */
    const Wall &upperWall() const;

    /**
     * @brief mLowerWall gets the lower wall of the arena
     * @return
     */
    const Wall &lowerWall() const;

    /**
     * @brief getPlayer2 const reference to the second player
     * @return const reference to the second player
     */
    const Player &getPlayer2() const;

    /**
     * @brief setGameState changes the current game state
     * @param gameState the new game state
     */
    void setGameState(GAMESTATE gameState);

    /**
     * @brief reset resets the inner state of the game object
     */
    void reset();


    /**
     * @brief operator << serialize the game to a sf::Packet
     * @param packet the packet in which to serialize the game object
     * @param game the game to serialize
     * @return the packet with the serialize game object
     */
    friend sf::Packet &operator<<(sf::Packet &packet, Game &game);

    /**
     * @brief operator >> deserializes the game object using the given packet
     * @param packet the packet from where to retrieve the data
     * @param game the game to init with the packet's data
     * @return
     */
    friend sf::Packet &operator>>(sf::Packet &packet, Game &game);

    /**
     * @brief playerWon wether one player won the match
     * @return wether one player won the match
     */
    bool playerWon() const;

    /**
     * @brief getNumWinner
     * @return the number of the winner (-1) if no one won
     */
    int getNumWinner() const;

    const Player &getWinner() const;

    /**
     * @brief isCountingDown
     * @return wether the game is currently doing the countdown before the start
     */
    bool isCountingDown() const;

    /**
     * @brief getCountdownTime the countdown timer
     * @return
     */
    const sf::Time &getCountdownTime() const;


    /**
     * @brief world non-const reference to the box2dWorld
     * @return
     */
    b2World &world() const;

    /**
     * @brief input gets the input to change/get its values
     * @return the input manager of the game
     */
    Input &input();

    /**
     * @brief setGameMode setter for the game mode
     * @param mode
     */
    void setGameMode(GAME_MODE mode);

    /**
     * @brief gameMode getter for the game mode
     * @return
     */
    GAME_MODE gameMode() const;


private:
    /**
     * @brief updateCountdown updates the game when in countdown mode
     * @param elapsed time elapsed since last update
     */
    void updateCountdown(const sf::Time &elapsed);

    /**
     * @brief updatePlaying updates the game when in playing mode
     * @param elapsed time elapsed since last update
     */
    void updatePlaying(const sf::Time &elapsed);

    /**
     * @brief gravity world gravity
     */
    b2Vec2 m_gravity = b2Vec2(0.f,0.f);


    /**
     * @brief mPhysicWorld the box2d world
     */
    mutable b2World m_physicWorld;

    /**
     * @brief mainBall the ball object for the game
     */
    Ball m_ball;

    /**
     * @brief p1 the first player
     */
    Player m_p1;

    /**
     * @brief p2 the second player
     */
    Player m_p2;

    /**
     * @brief upperWall upper wall of the arena
     */
    Wall m_upperWall;

    /**
     * @brief lowerWall lower wall of the arena
     */
    Wall m_lowerWall;

    /**
     * @brief m_countDownTime time before we can start the game
     */
    sf::Time m_countDownTime;

    /**
     * @brief m_state current state of the game
     */
    GAMESTATE m_state;

    /**
     * @brief mContactListener
     * listens at the contacts between
     * the bodies in the world
     */
    ContactListener m_contactListener;

    /**
     * @brief m_input input manager
     * for the game, contains the bindings
     */
    Input m_input;

    /**
     * @brief m_gameMode current game mode
     */
    GAME_MODE m_gameMode;

    //"signals"
public:
    Signal<std::size_t, b2Vec2> hitPaddleSignal;
    Signal<int> lostSignal;
    Signal<> countdownEndedSignal;
};

}
