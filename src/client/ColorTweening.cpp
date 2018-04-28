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
 * File:   ColorTweening.cpp
 * Author: azarias
 *
 * Created on 26/3/2018
 */
#include "ColorTweening.hpp"

ColorTweening::ColorTweening()
{
    m_running = false;
}

ColorTweening::ColorTweening(const sf::Color &defaultColor):
    m_color(defaultColor)
{
    m_running = false;
}

ColorTweening::ColorTweening(const sf::Color &from, const sf::Color &to, float duration, twin::easing easing):
    m_color(from)
{
    m_colorsTwin[0] = twin::makeTwin(from.r, to.r, duration, easing);
    m_colorsTwin[1] = twin::makeTwin(from.g, to.g, duration, easing);
    m_colorsTwin[2] = twin::makeTwin(from.b, to.b, duration, easing);
    m_colorsTwin[3] = twin::makeTwin(from.a, to.a, duration, easing);

    m_running = true;
}



const sf::Color &ColorTweening::get() const
{
    return m_color;
}

void ColorTweening::update(float deltaTime)
{
    if(!m_running)return;

    for(auto &tw : m_colorsTwin)
        tw.step(deltaTime);

    m_color = sf::Color(m_colorsTwin[0].get(), m_colorsTwin[1].get(), m_colorsTwin[2].get(), m_colorsTwin[3].get());
    m_running = m_colorsTwin[0].progress() < 1.f;
}

