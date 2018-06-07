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
 * File:   SplashScreenState.hpp
 * Author: azarias
 *
 * Created on 5/6/2018
 */
#pragma once

#include "src/client/State.hpp"
#include "src/common/Timer.hpp"
#include "src/lib/twin.hpp"

#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

namespace mp {

class SplashScreenState : public State
{
public:
    SplashScreenState();

    void update(const sf::Time &elapsed);

    void render(Renderer &renderer) const;

    void handleEvent(const sf::Event &ev);

private:
    sf::Sprite &insertSprite(const sf::Uint64 &id, float xCenter);

    Timer m_timer;

    std::vector<sf::Sprite> m_sprites = {};

    sf::Text m_games;

    sf::Text m_ema;

    twin::Twin<float> m_emaPos;

    twin::Twin<float> m_emaScale;
};


}
