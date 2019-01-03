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

    enum LD_STATE { LD_INACTIVE, LD_ACTIVE };

    Loading(const sf::Vector2f &center, float width);

    void render(Renderer &renderer) const override;

    bool update(const sf::Time &delta) override;

    bool handleEvent(const sf::Event &) override;

    void setState(LD_STATE nwState);

private:

    void nextSquare();

    class Square
    {
    public:
        Square(const sf::Vector2f &center);

        void on(bool fast);

        void off(bool fast);

        void update(const sf::Time &delta);

        void render(Renderer &renderer) const;

    private:
        sf::RectangleShape m_innerRect;

        ColorTweening m_color;

    };

    Timer m_timer;

    std::vector<Square> m_squares;

    int m_currentSquare = 0;

    LD_STATE m_state = LD_INACTIVE;
};


}

