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
 * File:   Animation.hpp
 * Author: azarias
 *
 * Created on 17/11/2017
 */
#pragma once


#include <SFML/Graphics/Sprite.hpp>
#include "src/common/Timer.hpp"
#include "src/client/Renderable.hpp"

namespace sf {
    class Texture;
}

namespace mp {

class RandomAnimation : public Renderable
{
public:
    RandomAnimation(const sf::Texture &texture, sf::Vector2i sprites, const sf::Time &animTime, bool loop = true);

    virtual ~RandomAnimation() override;

    void render(Renderer &renderer) const override;

    void update(const sf::Time &delta);

    void setPosition(const sf::Vector2f &position);

    void setSize(const sf::Vector2f &size);

private:
    void nextFrame();


    sf::Sprite m_sprite;

    Timer m_nextFrameTimer;

    sf::Vector2i m_animSize;

    sf::IntRect m_textureRect;

    sf::Vector2i m_rectPos = {0, 0};

    sf::Vector2f m_scale = {1.f, 1.f};

    sf::Vector2f m_translate = {0.f, 0.f};

    bool m_loop;
};



}
