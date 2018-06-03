/*
 * The MIT License
 *
 * Copyright 2017 azarias.
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
 * File:   FPSCounter.hpp
 * Author: azarias
 *
 * Created on 24/5/2018
 */

#pragma once

#include "Widget.hpp"
#include "src/common/Timer.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>

namespace mp {

class Renderer;

class FPSCounter : public Widget
{
public:
    FPSCounter(const sf::Font &font);

    /**
     * @brief update inherited function
     * @param elapsed
     */
    void update(const sf::Time &elapsed);

    /**
     * @brief draw inherited function
     * @param renderer
     */
    void draw(Renderer &renderer) const;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    void handleEvent(const sf::Event &ev);

private:
    sf::Text m_text;

    Timer m_timer;

    int m_calls = 0;
};

}
