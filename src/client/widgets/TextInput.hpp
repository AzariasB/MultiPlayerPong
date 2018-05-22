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
    void draw(Renderer &renderer) const;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    void handleEvent(const sf::Event& ev) override;

    /**
     * @brief setText sets the text inside the text input
     * @param str the new text
     */
    void setText(const std::string &str);

    /**
     * @brief getText a reference to the text entered by the user
     * @return the text entered by the user
     */
    const std::string &getText() const;

    virtual ~TextInput();
private:
    /**
     * @brief updatePipePos update the blinking pipe position
     */
    void updatePipePos();

    /**
     * @brief m_text the text to draw showing what the user typed
     */
    sf::Text m_text;

    /**
     * @brief m_pipe the blinking pipe at the end of the text entered
     */
    sf::Text m_pipe;

    /**
     * @brief m_typed the actual text entered by the user
     */
    std::string m_typed;

    /**
     * @brief m_background background of the text input
     */
    sf::RectangleShape m_background;

    /**
     * @brief m_clock a mutable object in order to make the pipe blink
     */
    mutable sf::Clock m_clock;

};

}



