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
 * File:   ColorTweening.hpp
 * Author: azarias
 *
 * Created on 26/3/2018
 */
#pragma once

#include <functional>
#include <SFML/Graphics/Color.hpp>
#include "src/lib/twin.hpp"

namespace mp {



class ColorTweening
{
public:
    /**
     * @brief ColorTweening empty constructor
     */
    ColorTweening();

    /**
     * @brief ColorTweening no tweening, just a color
     * @param defaultColor
     */
    ColorTweening(const sf::Color &defaultColor);


    /**
     * @brief ColorTweening constructor
     * @param from the original color
     * @param to the color to reach
     * @param duration the duration of the transition
     * @param easing the easing to use
     */
    ColorTweening(const sf::Color &from, const sf::Color &to, const sf::Time &duration, twin::easing easing, const std::function<void()> &callback = {});

    /**
    * @brief get the current color depending on the progress
    * @return
    */
    const sf::Color &get() const;

    /**
     * @brief update updates all the colors of this object
     * @param deltaTime time since last update
     */
    void update(const sf::Time &deltaTime);

    /**
     * @brief isFinished if the transition is done
     * @return
     */
    bool isFinished() const;

    /**
     * @brief progress current progress of the tweening
     * @return
     */
    float progress() const;

private:

    /**
     * @brief running wether we actually need to update the colors
     */
    bool m_running;

    sf::Color m_color;

    /**
     * @brief m_colorsTwin array of 4 tweening, in order, it contains:
     *  - the red value tweening
     *  - the green value tweening
     *  - the blue value tweening
     *  - the alpha value tweening
     */
    std::array<twin::Twin<sf::Uint8>, 4> m_colorsTwin;
};


}
