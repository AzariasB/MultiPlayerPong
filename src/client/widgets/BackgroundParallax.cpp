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
 * File:   BackgroundParallax.cpp
 * Author: azarias
 *
 * Created on 3/8/2018
 */
#include "BackgroundParallax.hpp"
#include "src/client/Renderer.hpp"
#include "src/common/VectorsUtils.hpp"

#include <iostream>
#include <cmath>

namespace mp {

BackgroundParallax::BackgroundParallax()
{

}

BackgroundParallax::BackgroundParallax(const sf::Texture &texture, const sf::Vector2f &bounds):
    m_sprite(texture),
    m_bounds(bounds)
{

}

void BackgroundParallax::setOffset()
{
    m_offset = m_translate;

}

void BackgroundParallax::translate(float nwX, float nwY)
{
    m_translate.x = fmodf(nwX + m_offset.x , m_sprite.getGlobalBounds().width);
    m_translate.y = fmodf(nwY + m_offset.y, m_sprite.getGlobalBounds().height);
}

void BackgroundParallax::render(Renderer &renderer) const
{

    float sWidth = m_sprite.getGlobalBounds().width;
    float sHeight = m_sprite.getGlobalBounds().height;

    renderer
            .push()
            .translate(sf::Vector2f(m_translate.x - sWidth, m_translate.y - sHeight));

    int horiz = static_cast<int>(m_bounds.x / sWidth) + 3;
    int vert = static_cast<int>(m_bounds.y / sHeight) + 3;

    for(int y = 0; y < vert; ++y)
    {
        for(int x = 0; x < horiz; ++x)
        {
            renderer.draw(m_sprite);
            renderer.translate(sf::Vector2f(sWidth, 0));
        }
        renderer.translate(sf::Vector2f(-sWidth * horiz, sHeight));
    }


    renderer.pop();
}

}
