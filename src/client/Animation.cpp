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
#include "Animation.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

namespace mp {

Animation::Animation(const sf::Texture &texture, sf::Vector2i sprites, const sf::Time &animTime, bool loop):
    m_sprite(texture),
    m_time(animTime),
    m_frameTime(m_time /static_cast<sf::Int64>(sprites.x * sprites.y)),
    m_animSize(sprites),
    m_textureRect(0, 0, texture.getSize().x/sprites.x, texture.getSize().y / sprites.y),
    m_loop(loop)
{
    m_sprite.setTextureRect(m_textureRect);
}

void Animation::setPosition(const sf::Vector2f &position)
{
    m_sprite.setPosition(position);
}

const sf::Vector2f &Animation::getPosition() const
{
    return m_sprite.getPosition();
}

void Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

void Animation::update(const sf::Time &delta)
{
    m_time += delta;
    if(m_time > m_frameTime){
        m_time = sf::Time();
        nextFrame();
    }
}

void Animation::nextFrame()
{
    m_rectPos.x++;
    if(m_rectPos.x == m_animSize.x){
        m_rectPos.x = 0;
        m_rectPos.y++;

        if(m_rectPos.y == m_animSize.y){
            if(m_loop){
                m_rectPos.x = 0;
                m_rectPos.y = 0;
            }else{
                //send "animation end" signal
            }
        }
    }
    m_textureRect.left = m_rectPos.x*m_textureRect.width;
    m_textureRect.top = m_rectPos.y *m_textureRect.height;
    m_sprite.setTextureRect(m_textureRect);
}

Animation::~Animation()
{

}


}
