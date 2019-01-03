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
 * File:   FadeTransition.hpp
 * Author: azarias
 *
 * Created on 11/8/2018
 */
#pragma once

#include "Transition.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "src/lib/twin.hpp"

namespace mp
{

class Renderer;

/**
 * @brief The FadeTransition class
 * used to create a fade transition between two states
 * starts with creating two textures and uses a shader
 * to create the fade effect
 */
class FadeTransition : public Transition
{
public:
    /**
     * @brief FadeTransition empty constructor
     */
    FadeTransition();

    /**
     * @brief render inherited function
     * @param renderer renders the fade effect
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief progress update the fade effect
     * @param elapsed time since las frame
     * @return true if the fade effect is over
     */
    bool progress(const sf::Time &elapsed) override;

    /**
     * @brief onEnter when the transition starts
     * @param data the data used to  configure the transition and the state
     */
    void onEnter(BaseStateData *data) override;

    ~FadeTransition() override;

private:
    /**
     * @brief m_shader the shader used
     * to create the fade effect
     * is destroyed at the same time as the transition
     */
    sf::Shader *m_shader;

    /**
     * @brief m_fromTexture keep the texture of the state
     * we come from
     */
    sf::Texture m_fromTexture;

    /**
     * @brief m_toTexture keep the texture of the state
     * we go to
     */
    sf::Texture m_toTexture;

    /**
     * @brief m_alpha tweening used
     * to change the alpha uniform of the shader
     */
    twin::Twin<float> m_alpha;

    /**
     * @brief m_background using a sprite
     * to render the texture with the shader
     */
    sf::Sprite m_background;
};


}
