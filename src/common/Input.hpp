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

class Input
{
public:

    enum I_AXIS { Y_AXIS_1, Y_AXIS_2 };

    enum I_AXIS_DIRECTION {
        Y_AXIS_1_UP = sf::Keyboard::Up, Y_AXIS_1_DOWN = sf::Keyboard::Down,
        Y_AXIS_2_UP = sf::Keyboard::E, Y_AXIS_2_DOWN = sf::Keyboard::D
    };

    Input();

    void resetBindings();

    void handleEvent(const sf::Event &ev);

    float getAxis(I_AXIS axis) const;

    void setAxisButton(I_AXIS_DIRECTION dir, sf::Keyboard::Key k);

private:
    void handleKeyChange(const sf::Event &ev, int nwValue);

    void handleJoystick(const sf::Event &ev);

    void setAxisValue(I_AXIS_DIRECTION d, int value);

    std::unordered_map<I_AXIS, float> m_axes;

    std::unordered_map<I_AXIS_DIRECTION, sf::Keyboard::Key> m_bindings;
};


}

