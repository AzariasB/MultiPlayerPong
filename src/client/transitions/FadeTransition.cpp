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
 * File:   FadeTransition.cpp
 * Author: azarias
 *
 * Created on 11/8/2018
 */
#include "src/client/StateMachine.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/Assets.hpp"
#include "src/client/StateMachine.hpp"

namespace mp
{

FadeTransition::FadeTransition():
    m_shader( /*pr::resourceManager().get(Assets::Alpha)*/ new sf::Shader)
{
}

FadeTransition::~FadeTransition()
{
    delete m_shader;
}

bool FadeTransition::progress(const sf::Time &time)
{
    m_alpha.step(time);
    m_shader->setUniform("progress", m_alpha.get());
    m_toTexture = pr::renderer()
                        .useTextureTarget()
                        .render(enteringState())
                        .useWindowTarget()
                        .getTextureTarget();
    m_shader->setUniform("to", m_toTexture);

    return m_alpha.progress() == 1.f;

}

void FadeTransition::render(Renderer &renderer) const
{
    renderer.pushShader(m_shader)
            .draw(m_background)
            .pop();
}


}
