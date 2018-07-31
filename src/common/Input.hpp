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
 * File:   Input.hpp
 * Author: azarias
 *
 * Created on 15/7/2018
 */
#pragma once

#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

namespace sf {
    class Event;
}

namespace mp {

/**
 * @brief The Input class used to
 * easily handle inputs, axes, multiplayer inputs
 * is created to handle a local 1v1 game
 */
class Input
{
public:

    /**
     * @brief The I_AXIS enum to represent the two possible axis to play for
     * the axis_X is for player X
     */
    enum I_AXIS { Y_AXIS_1, Y_AXIS_2 };

    /**
     * @brief The I_AXIS_DIRECTION enum the differente directions for each axis
     * is also used as an enum for all the possible actions
     */
    enum I_AXIS_DIRECTION {
        Y_AXIS_1_UP = sf::Keyboard::Up, Y_AXIS_1_DOWN = sf::Keyboard::Down,
        Y_AXIS_2_UP = sf::Keyboard::E, Y_AXIS_2_DOWN = sf::Keyboard::D
    };

    /**
     * @brief Input constructor
     */
    Input();

    /**
     * @brief resetBindings sets all the bindings to the defaults ones
     */
    void resetBindings();

    /**
     * @brief handleEvent handles an event and update its internal state
     * @param ev the evenement trigerred by the user
     */
    void handleEvent(const sf::Event &ev);

    /**
     * @brief toBaseEvent used in multiplayer to change the given event
     * into an event that will be understood by the server, no matter what the key binding is
     * @param ev the base event trigerred by the user
     * @param playerNum the number of the player who trigerred the event
     * @return an event understandable by the server
     */
    sf::Event toBaseEvent(const sf::Event &ev, int playerNum) const;

    /**
     * @brief getAxis used to get the value of a given axis
     * @param axis the axis to get the value from
     * @return the axis value (between 0 and 1), when a keyboard is used
     * it's 0 or 1, but when a joystick is used, it can varry between all the possible
     * float value between 0 and 1
     */
    float getAxis(I_AXIS axis) const;

    /**
     * @brief setAxisButton changes the binding for and axis direction
     * @param dir the direction to change the binding for
     * @param k the new keyboard to bind the axis to
     */
    void setAxisButton(I_AXIS_DIRECTION dir, sf::Keyboard::Key k);

    /**
     * @brief getAxisKey returns the binding for the given direction
     * @param dir the direction to get the binding for
     * @return the key code associated with the given direction
     */
    sf::Keyboard::Key getAxisKey(I_AXIS_DIRECTION dir) const;

    /**
     * @brief allActions array of all the possible actions that the user can trigger
     */
    static const std::array<I_AXIS_DIRECTION, 4> allActions;
private:
    /**
     * @brief handleKeyChange when a key is released or pressed, update the internal axis value
     * @param ev the event
     * @param nwValue the new value (0 when released, 1 when pressed)
     */
    void handleKeyChange(const sf::Event &ev, int nwValue);

    /**
     * @brief handleJoystick when a joystick axis is changed
     * @param ev the joystick event
     */
    void handleJoystick(const sf::Event &ev);

    /**
     * @brief setAxisValue sets the value of the given axis
     * @param d the axis
     * @param value the value of the axis
     */
    void setAxisValue(I_AXIS_DIRECTION d, int value);

    /**
     * @brief getP2Equivalent when the player is in multiplayer
     * and plays with the solo keybaord binding, we need to change
     * it so the server sees it as player 2 playing
     * @param dir the direction to find an adequate for
     * @return the new keyboard binding
     */
    sf::Keyboard::Key getP2Equivalent(I_AXIS_DIRECTION dir) const;

    /**
     * @brief m_axes value of each axes
     */
    std::unordered_map<I_AXIS, float> m_axes;

    /**
     * @brief m_bindings binding for each axis direction
     */
    std::unordered_map<I_AXIS_DIRECTION, sf::Keyboard::Key> m_bindings;
};


}

