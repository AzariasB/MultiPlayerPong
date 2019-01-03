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
 * File:   TextInput.h
 * Author: azarias
 *
 * Created on 22 octobre 2017, 16:29
 */

#pragma once


#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Widget.hpp"
#include "src/common/Timer.hpp"

namespace mp {

class Renderer;

/**
 * @brief The TextInput class a widget used to enter text
 * and get the text entered when needed
 */
class TextInput : public Widget {
public:
    /**
     * @brief TextInput constructor
     * @param app a reference to the client's app
     */
    TextInput(const sf::Vector2f &position);

    /**
     * @brief draw inherited function
     * @param target
     * @param states
     */
    void render(Renderer &renderer) const;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    bool handleEvent(const sf::Event& ev) override;

    /**
     * @brief update inherited function (used to update the
     * blinking pipe at the end)
     * @param elapsed
     */
    bool update(const sf::Time &elapsed) override;

    /**
     * @brief setText sets the text inside the text input
     * @param str the new text
     */
    void setText(const sf::String &str);

    /**
     * @brief getText a reference to the text entered by the user
     * @return the text entered by the user
     */
    const sf::String &getText() const;

    virtual ~TextInput();
private:
    /**
     * @brief movePipe moves the pipe in the given direction, while keeping it in the bounds
     * @param direction direction of the pipe
     */
    bool movePipe(int direction);

    /**
     * @brief addString adds the given string to the actual string, without
     * adding more than the maximum limit
     * @param toAdd the string to append to the current one
     */
    void addString(const sf::String &toAdd);

    /**
     * @brief removeLastChar clears out the last char
     * of the string (if there's any)
     */
    void removeChar();

    /**
     * @brief supprChar clears the character located
     * after the curosr (if any)
     */
    bool supprChar();

    /**
     * @brief m_text the text to draw showing what the user typed
     */
    sf::Text m_text;

    /**
     * @brief m_pipe the blinking pipe at the end of the text entered
     */
    sf::RectangleShape m_pipe;

    std::size_t m_pipeIndex = 0;

    /**
     * @brief m_typed the actual text entered by the user
     */
    sf::String m_typed;

    /**
     * @brief m_background background of the text input
     */
    sf::RectangleShape m_background;

    /**
     * @brief m_clock a mutable object in order to make the pipe blink
     */
    Timer m_timer;
};

}




