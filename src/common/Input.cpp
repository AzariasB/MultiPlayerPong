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
 * File:   Input.cpp
 * Author: azarias
 *
 * Created on 15/7/2018
 */
#include "Input.hpp"
#include <SFML/Window/Event.hpp>
#include <vector>
#include <iostream>

namespace mp {

const std::array<Input::I_AXIS_DIRECTION, 4> Input::allActions = {Input::Y_AXIS_1_DOWN, Input::Y_AXIS_1_UP, Input::Y_AXIS_2_DOWN, Input::Y_AXIS_2_UP };

Input::Input()
{
    resetBindings();
}

void Input::handleEvent(const sf::Event &ev)
{
    switch (ev.type) {
    case sf::Event::KeyPressed:
        handleKeyChange(ev, 1);
        break;
    case sf::Event::KeyReleased:
        handleKeyChange(ev, 0);
        break;
    case sf::Event::JoystickMoved:
        handleJoystick(ev);
        break;
    default:
        break;
    }
}

sf::Keyboard::Key Input::getAxisKey(Input::I_AXIS_DIRECTION dir) const
{
    auto found = m_bindings.find(dir);
    return found == m_bindings.end() ? sf::Keyboard::Unknown : found->second;
}

sf::Event Input::toBaseEvent(const sf::Event &ev, int playerNum) const
{
    if(ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased)
    {
        sf::Event realEv = ev;
        for(const auto &it : m_bindings){
            if(ev.key.code == it.second){
                if(playerNum == 1){
                    realEv.key.code = static_cast<sf::Keyboard::Key>(it.first);
                    return realEv;
                } else {
                    realEv.key.code = getP2Equivalent(it.first);
                    return realEv;
                }
            }
        }
    }
    return ev;
}

sf::Keyboard::Key Input::getP2Equivalent(Input::I_AXIS_DIRECTION dir) const
{
    if(dir == Input::Y_AXIS_1_DOWN) {
        return static_cast<sf::Keyboard::Key>(m_bindings.find(Input::Y_AXIS_2_DOWN)->first);
    } else if(dir == Input::Y_AXIS_1_UP){
        return static_cast<sf::Keyboard::Key>(m_bindings.find(Input::Y_AXIS_2_UP)->first);
    }
    return {};
}

void Input::handleJoystick(const sf::Event &ev)
{
    if(ev.joystickMove.axis != sf::Joystick::Y) return;

    if(ev.joystickMove.joystickId == 0){
        m_axes[Y_AXIS_1] = (ev.joystickMove.position / 100.f);
    } else if (ev.joystickMove.joystickId == 1) {
        m_axes[Y_AXIS_2] = (ev.joystickMove.position / 100.f);
    }
}

void Input::handleKeyChange(const sf::Event &ev, int nwValue)
{
    for(auto it : m_bindings){
        if(it.second == ev.key.code){
            setAxisValue(it.first, nwValue);
        }
    }
}

void Input::setAxisValue(I_AXIS_DIRECTION d, int value)
{
    switch (d) {
    case Y_AXIS_1_UP:
        m_axes[Y_AXIS_1] = -value;
        break;
    case Y_AXIS_2_UP:
        m_axes[Y_AXIS_2] = -value;
        break;
    case Y_AXIS_1_DOWN:
        m_axes[Y_AXIS_1] = value;
        break;
    case Y_AXIS_2_DOWN:
        m_axes[Y_AXIS_2] = value;
        break;
    }
}

void Input::resetBindings()
{
    std::vector<I_AXIS_DIRECTION> dirs = {Y_AXIS_1_UP, Y_AXIS_1_DOWN, Y_AXIS_2_DOWN, Y_AXIS_2_UP};
    for(auto d : dirs)
        m_bindings[d] = static_cast<sf::Keyboard::Key>(d);
}

void Input::setAxisButton(I_AXIS_DIRECTION dir, sf::Keyboard::Key k)
{
    m_bindings[dir] = k;
}

float Input::getAxis(I_AXIS axis) const
{
    auto f = m_axes.find(axis);
    return f == m_axes.end() ? 0 : f->second;
}

}
