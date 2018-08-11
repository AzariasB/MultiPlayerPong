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
 * File:   PauseState.cpp
 * Author: azarias
 *
 * Created on 7/5/2018
 */
#include "PauseState.hpp"
#include "src/common/Game.hpp"
#include "src/common/Config.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/Translator.hpp"
#include "src/client/StateMachine.hpp"

#include <iostream>

namespace mp {

PauseState::PauseState():
    m_menu(),
    m_shader(pr::resourceManager().createShader(Assets::Shaders::Alpha))
{
    m_menu.addCenteredLabel("Pause", SF_ARENA_WIDTH / 2.f, 50, 100);

    float startY = 250.f;

    Button &resume = m_menu.addButton("resume", SF_ARENA_WIDTH / 2.f , startY, Assets::IconAtlas::rightIcon);
    startY += resume.getHeight() + 10.f;

    Button &restart = m_menu.addButton("restart", SF_ARENA_WIDTH / 2.f, startY, Assets::IconAtlas::returnIcon);
    startY += restart.getHeight() + 10.f;

    Button &options = m_menu.addButton("options", SF_ARENA_WIDTH / 2.f , startY, Assets::IconAtlas::gearIcon);
    startY += options.getHeight() + 10.f;

    Button &menuBtn = m_menu.addButton("menu", SF_ARENA_WIDTH / 2.f, startY, Assets::IconAtlas::exitLeftIcon);
    startY += menuBtn.getHeight() + 10.f;

    m_menu.normalizeButtons(10);

    resume.clickedSignal.add([](){pr::stateMachine().setCurrentState(cc::PLAY_SOLO);});
    options.clickedSignal.add([](){pr::stateMachine().goToState(cc::OPTIONS, TransitionData::GO_RIGHT);});
    menuBtn.clickedSignal.add([](){pr::stateMachine().goToState(cc::MENU, TransitionData::GO_DOWN);});
    restart.clickedSignal.add([](){
        pr::game().reset();
        pr::stateMachine().setCurrentState(cc::PLAY_SOLO);
    });

    pr::translator().translationChangedSignal.add([this](){
        m_menu.normalizeButtons(10);
    });
}

PauseState::~PauseState()
{
    delete m_shader;
}

void PauseState::onAfterLeaving()
{
    if(pr::stateMachine().getCurrentStateIndex() != cc::PLAY_SOLO){
        pr::stateMachine().getStateAt(cc::PLAY_SOLO).onAfterLeaving();
    }
}

void PauseState::onEnter(BaseStateData *)
{
    m_fromTexture = pr::renderer()
                        .useTextureTarget()
                        .render(pr::stateMachine().getStateAt(cc::PLAY_SOLO))
                        .useWindowTarget()
                        .getTextureTarget();

    m_shader->setUniform("from", m_fromTexture);
    m_shader->setUniform("progress", 0.f);
    m_shader->setUniform("resolution", sf::Vector2f(m_fromTexture.getSize().x, m_fromTexture.getSize().y));
    m_alpha = twin::makeTwin(0.f, 1.f, sf::milliseconds(500), twin::easing::quadOut);

    m_toTexture = pr::renderer()
                    .useTextureTarget()
                    .render(pr::stateMachine().getStateAt(cc::PLAY_SOLO))
                    .render(m_menu)
                    .useWindowTarget()
                    .getTextureTarget();
    m_shader->setUniform("to", m_toTexture);

    m_background = sf::Sprite(m_fromTexture);
    m_background.setPosition(0,0);
    m_background.setOrigin(0,0);
}

void PauseState::render(Renderer &renderer) const
{
    if(m_alpha.progress() == 1.f) {
        renderer.render(pr::stateMachine().getStateAt(cc::PLAY_SOLO))
                .render(m_menu);
    } else{
        renderer.pushShader(m_shader)
                .draw(m_background)
                .pop();
    }
}

void PauseState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
    m_alpha.step(elapsed);

    m_toTexture = pr::renderer()
                    .useTextureTarget()
                    .render(pr::stateMachine().getStateAt(cc::PLAY_SOLO))
                    .render(m_menu)
                    .useWindowTarget()
                    .getTextureTarget();
    m_shader->setUniform("to", m_toTexture);
    m_shader->setUniform("progress", m_alpha.get());
}

void PauseState::handleEvent(const sf::Event &ev)
{
    m_menu.handleEvent(ev);
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
        pr::stateMachine().setCurrentState(cc::PLAY_SOLO);
}


}
