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

/**
 * @brief The RandomAnimation class
 * used to create a drawing-like feel to the objects
 * on the scene (ball, paddles, walls)
 * Instead of following a certain order for the sprite on the given texture
 * chooses a random rectTexture within the available ones
 */
class RandomAnimation : public Renderable
{
public:
    /**
     * @brief RandomAnimation constructor
     * @param texture the texture to use to create the animation
     * @param sprites the number of vertical (y) and horizontal (x) sprites
     * @param animTime the time of a single animation
     * @param loop wether this animation must loop
     */
    RandomAnimation(const sf::Texture &texture, sf::Vector2i sprites, const sf::Time &animTime, bool loop = true);

    virtual ~RandomAnimation() override;

    /**
     * @brief render renders the currently selected sprite
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief update updates the internal timer
     * and if needed, changes the current sprite rect
     * @param delta
     */
    void update(const sf::Time &delta);

    /**
     * @brief setPosition changes the position of the
     * CENTER of this animation
     * @param position
     */
    void setPosition(const sf::Vector2f &position);

    /**
     * @brief setSize changes the scale of the
     * sprite in order to reach the given size
     * @param size
     */
    void setSize(const sf::Vector2f &size);

private:
    /**
     * @brief nextFrame finds the next
     * random frame (might be the same as
     * the current one)
     */
    void nextFrame();

    /**
     * @brief m_sprite the sprite used for the rendering
     */
    sf::Sprite m_sprite;

    /**
     * @brief m_nextFrameTimer timer to know
     * when to trigger the next frame
     */
    Timer m_nextFrameTimer;

    /**
     * @brief m_animSize number of sprites vertically
     * and horizontally
     */
    sf::Vector2i m_animSize;

    /**
     * @brief m_textureRect the texture rect used
     * for the sprite
     */
    sf::IntRect m_textureRect;

    /**
      * scale of the sprite
      * */
    sf::Vector2f m_scale = {1.f, 1.f};

    /**
      * Translate used
      * to move the sprite around
      * */
    sf::Vector2f m_translate = {0.f, 0.f};

    /**
     * @brief m_loop wether the animation must be looped
     */
    bool m_loop;
};



}
