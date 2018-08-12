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
 * File:   Animation.cpp
 * Author: azarias
 *
 * Created on 17/11/2017
 */
#include <iostream>
#include "src/common/VectorsUtils.hpp"

#include "RandomAnimation.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "src/client/Renderer.hpp"

#include "src/common/Math.hpp"

namespace mp {

RandomAnimation::RandomAnimation(const sf::Texture &texture, sf::Vector2i sprites, const sf::Time &animTime, bool loop):
    m_sprite(texture),
    m_nextFrameTimer(animTime, true),
    m_animSize(sprites),
    m_textureRect(0, 0, texture.getSize().x/sprites.x, texture.getSize().y / sprites.y),
    m_loop(loop)
{
    m_sprite.setTextureRect(m_textureRect);
    math::centerOrigin(m_sprite);
}

void RandomAnimation::setSize(const sf::Vector2f &size)
{
   m_scale.x =  size.x / m_sprite.getGlobalBounds().width;
   m_scale.y =  size.y / m_sprite.getGlobalBounds().height;
}

void RandomAnimation::setPosition(const sf::Vector2f &position)
{
    m_translate = position;
}

void RandomAnimation::render(Renderer &renderer) const
{
    renderer
            .push()
            .translate(m_translate)
            .scale(m_scale.x, m_scale.y)
            .draw(m_sprite)
            .pop();
}

void RandomAnimation::update(const sf::Time &delta)
{
    if(m_nextFrameTimer.update(delta)){
        nextFrame();
    }
}

void RandomAnimation::nextFrame()
{
    int xAnim = m_animSize.x > 1 ? rand()  % m_animSize.x : 0;
    int yAnim = m_animSize.y > 1 ? rand() % m_animSize.y : 0;
    m_textureRect.left = xAnim * m_textureRect.width;
    m_textureRect.top  = yAnim * m_textureRect.height;
    m_sprite.setTextureRect(m_textureRect);
}

RandomAnimation::~RandomAnimation()
{

}


}
