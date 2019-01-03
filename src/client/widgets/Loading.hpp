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
 * File:   Loading.hpp
 * Author: azarias
 *
 * Created on 14/7/2018
 */
#pragma once

#include "Widget.hpp"
#include "src/client/ColorTweening.hpp"
#include "src/common/Timer.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

namespace sf {
    class Time;
    class Event;
}

namespace mp {
class Renderer;

constexpr int SQUARES = 5;
constexpr float SQ_SIDE = 30.f;
constexpr float SQ_RADIUS = 5.f;

/**
 * @brief The Loading class
 * The loading widget is used when the user
 * tries to connect to the server and waits
 * for an oponent, the wiget has two state
 * 'inactive' and 'active' these can be used
 * however the programmer wants
 */
class Loading : public Widget
{
public:
    /**
     * @brief The LD_STATE enum
     * The possible states of the loading widget
     */
    enum LD_STATE { LD_INACTIVE, LD_ACTIVE };

    /**
     * @brief Loading constructor
     * @param center center point of the widget
     * @param width the total width available for the widget
     */
    Loading(const sf::Vector2f &center, float width);

    /**
     * @brief render overriden function
     * @param renderer object to use to render the widget
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief update overriden function
     * @param delta time elapsed since last update
     * @return if the widget still needs to be updated
     */
    bool update(const sf::Time &delta) override;

    /**
     * @brief handleEvent overriden function
     * @return
     */
    bool handleEvent(const sf::Event &) override;

    /**
     * @brief setState changes the state of the loading bar
     * @param nwState nw satet
     */
    void setState(LD_STATE nwState);

private:

    /**
     * @brief nextSquare higlights the next square
     */
    void nextSquare();

    /**
     * @brief The Square class private utility class
     * to display a single part of the widget
     */
    class Square
    {
    public:
        /**
         * @brief Square default constructor
         */
        Square();

        /**
         * @brief Square constructor
         * @param center center point of the square
         */
        Square(const sf::Vector2f &center);

        /**
         * @brief on turns on the square
         * @param fast if it must be turned on 'fast'
         */
        void on(bool fast);

        /**
         * @brief off turns off the square
         * @param fast if it must be turned off 'fast'
         */
        void off(bool fast);

        /**
         * @brief update updates the squares color
         * @param delta time since last update
         */
        void update(const sf::Time &delta);

        /**
         * @brief render renders the square
         * @param renderer the objec to use to render it
         */
        void render(Renderer &renderer) const;

        void setPosition(const sf::Vector2f &center);

    private:
        /**
         * @brief m_innerRect shape of the square
         */
        sf::RectangleShape m_innerRect;

        /**
         * @brief m_color current color of the square
         */
        ColorTweening m_color;

    };

    /**
     * @brief m_timer to regularly move to the next square to draw
     */
    Timer m_timer;

    /**
     * @brief m_squares all the squares to be drawn
     */
    std::array<Square, SQUARES> m_squares;

    /**
     * @brief m_currentSquare square that is hilighted
     */
    std::size_t m_currentSquare = 0;

    /**
     * @brief m_state current state of the widget
     */
    LD_STATE m_state = LD_INACTIVE;
};


}

