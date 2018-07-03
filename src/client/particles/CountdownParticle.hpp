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
 * File:   CoundtownParticle.hpp
 * Author: azarias
 *
 * Created on 2/5/2018
 */

#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Particle.hpp"
#include "src/lib/twin.hpp"


namespace mp {

/**
 * @brief The CoundtownParticle class
 * particle used when doing the countdown
 * before a game, in order to have
 * a stylized countdown
 */
class CountdownParticle : public Particle
{
public:
    /**
     * @brief CountdownParticle constructor
     */
    CountdownParticle();

    /**
     * @brief update inherited function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief render inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief isFinished when the text is finally rendered
     * @return
     */
    bool isFinished() const override;

    /**
     * @brief init initializes the partile
     * @param text
     * @param position
     * @param lifetime
     */
    void init(const std::string &text, const sf::Vector2f &position, const sf::Time &lifetime);

private:
    /**
     * @brief m_textScale scale of the text
     */
    twin::Twin<float> m_textScale;

    /**
     * @brief m_textAlpha tweening for the text alpha
     */
    twin::Twin<sf::Uint8> m_textAlpha;

    /**
     * @brief m_text text to draw
     */
    sf::Text m_text;

    /**
     * @brief m_textColor color of the text
     */
    sf::Color m_textColor;
};

}

