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
 * File:   Animation.hpp
 * Author: azarias
 *
 * Created on 17/11/2017
 */
#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

class Animation : public sf::Drawable
{
public:
    Animation(const sf::Texture &texture, sf::Vector2i sprites, const sf::Time &animTime, bool loop = true);

    virtual ~Animation();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void update(const sf::Time &delta);

    void setPosition(const sf::Vector2f &position);

    const sf::Vector2f &getPosition() const;

private:
    void nextFrame();

    sf::Sprite m_sprite;

    sf::Time m_time;

    sf::Time m_frameTime;

    sf::Vector2i m_rectPos;

    sf::Vector2i m_animSize;

    sf::IntRect m_textureRect;

    bool m_loop;
};

#endif // ANIMATION_HPP
