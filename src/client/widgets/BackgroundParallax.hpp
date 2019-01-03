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
 * File:   BackgroundParallax.hpp
 * Author: azarias
 *
 * Created on 3/8/2018
 */
#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "src/client/Renderable.hpp"

namespace sf {
    class Texture;
}

namespace mp {

/**
 * @brief The BackgroundParallax class
 * widget used to have a background parallax
 * it's just a single texture that is repeating itself
 * over and over, on the window's view.
 * It's using a single sprite and translates it
 */
class BackgroundParallax : public Renderable
{
public:
    /**
     * @brief BackgroundParallax empty constructor
     */
    BackgroundParallax();

    /**
     * @brief BackgroundParallax better constructor
     * @param texture the texture to use to draw the background
     * @param bounds the bounds where to draw the texture
     * (the texture is used as a whole)
     */
    BackgroundParallax(const sf::Texture &texture, const sf::Vector2f &bounds);

    /**
     * @brief render inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const;

    /**
     * @brief setOffset to call when a transition is over,
     * avoids to have a jump of the background when the next
     * transistion starts
     */
    void setOffset();

    /**
     * @brief translate moves the background to the new given position
     * @param nwX x position
     * @param nwY y position
     */
    void translate(float nwX, float nwY);

private:
    /**
     * @brief m_sprite the sprite thats drawn
     */
    sf::Sprite m_sprite;

    /**
     * @brief m_bounds bounds where to draw
     * the sprite
     */
    sf::Vector2f m_bounds;

    /**
     * @brief m_translate current translation
     */
    sf::Vector2f m_translate;

    /**
      Current offset
    */
    sf::Vector2f m_offset = {0, 0};
};


}
