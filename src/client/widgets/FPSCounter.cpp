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
 * File:   FPSCounter.cpp
 * Author: azarias
 *
 * Created on 24/5/2018
 */
#include "FPSCounter.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/Renderer.hpp"

namespace mp {


FPSCounter::FPSCounter(const sf::Font &font):
    m_text("0", font, 20),
    m_timer(sf::seconds(1), true)
{
    m_text.setPosition(10, 10);
    m_timer.setCallback([this](){
        m_text.setString(std::to_string(m_calls));
        m_calls = 0;
    });
}

void FPSCounter::update(const sf::Time &elapsed)
{
    m_timer.update(elapsed);
    m_calls++;
}

void FPSCounter::render(Renderer &renderer) const
{
    renderer.draw(m_text);
}

void FPSCounter::handleEvent(const sf::Event &ev)
{

}



}
