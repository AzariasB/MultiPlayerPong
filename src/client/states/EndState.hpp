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
 * File:   EndState.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:50
 */

#pragma once

#include "src/client/State.hpp"
#include "src/client/widgets/Menu.hpp"
#include "src/lib/twin.hpp"

#include <SFML/Graphics/VertexBuffer.hpp>


namespace mp {

constexpr std::size_t triangleNumber = 10;

class Dialog;

/**
 * @brief The EndState class this state
 * is used when a game ends. It shows the result of the
 * game (win/loose) and the points gained during
 * the match
 */
class EndState : public State {
public:
    /**
     * @brief EndState constructor
     * @param app reference to the application
     */
    EndState();

    /**
     * @brief draw inherited function
     * @param renderer
     */
    void render(Renderer& renderer) const override;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    void handleEvent(const sf::Event& ev) override;

    /**
     * @brief update inherited function
     * @param dtS
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief onEnter inherited function
     * @param data
     */
    void onEnter(int playerNum = 0);

    /**
     * @brief onBeforeEnter inherited function
     * intialize all the drawing stuff
     */
    void onBeforeEnter() override;

    /**
     * @brief backButtonPressed when the "ok" or the cross of the dialog is pressed,
     * goes back to the main menu
     */
    void goToMenu();

    virtual ~EndState() override;

private:
    void updateVerticesColor(bool win);

    sf::Vector2f toVertexPosition(std::size_t index) const;

    /**
     * @brief m_menu the menu of the state, to show
     * the texts and the "back" button menu
     */
    Menu m_menu;

    /**
     * @brief m_content reference
     * to the "content" text, to show the text "win"
     * or "loose"
     */
    I18NText &m_content;

    /**
     * @brief m_buffer buffer for the animation
     */
    sf::VertexArray m_buffer;

    /**
     * @brief m_angle the current rotation angle
     */
    float m_angle;

    /**
     * @brief m_scale scale of the background spinner
     */
    twin::Twin<float> m_scale;
};



}
