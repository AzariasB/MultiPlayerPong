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
 * File:   TextInput.cpp
 * Author: azarias
 *
 * Created on 22 octobre 2017, 16:29
 */

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Clipboard.hpp>
#include "TextInput.hpp"

#include "src/client/Provider.hpp"
#include "src/client/Renderer.hpp"
#include "src/common/Config.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/ResourcesManager.hpp"

namespace mp {

TextInput::TextInput(const sf::Vector2f &position) :
    m_text("", pr::resourceManager().getFont()),
    m_pipe("|", pr::resourceManager().getFont()),
    m_typed(""),
    m_background(sf::Vector2f(9 * SF_DIALOG_WIDTH / 10.f, 50)),
    m_timer(sf::milliseconds(700), true)
{
    m_background.setOutlineColor(cc::Colors::dialogOutlineColor);
    m_background.setFillColor(cc::Colors::backgroundColor);
    m_background.setOutlineThickness(5);
    m_background.setPosition(position.x - 10, position.y);
    m_text.setPosition(position);
    updatePipePos();

    m_timer.setCallback([this](){
        sf::Color txtColor = m_pipe.getFillColor();
        txtColor.a = 255 - txtColor.a;
        m_pipe.setFillColor(txtColor);
    });
}

void TextInput::render(Renderer &renderer) const
{
    if(!isVisible())return;

    renderer.draw(m_background)
            .draw(m_text)
            .draw(m_pipe);
}

bool TextInput::update(const sf::Time &elapsed)
{
    m_timer.update(elapsed);
    return Widget::update(elapsed);
}

bool TextInput::handleEvent(const sf::Event& ev)
{
    if(ev.type == sf::Event::KeyPressed){
        if(ev.key.code == sf::Keyboard::V && ev.key.control){
            addString(sf::Clipboard::getString().toAnsiString());
            return true;
        }
    } else if (ev.type == sf::Event::TextEntered) {
        sf::Uint32 txt = ev.text.unicode;
        if(txt == 8){//backspace
            removeLastChar();
        } else {
            addString(sf::String(txt));
        }
        return true;
    }
}

void TextInput::removeLastChar()
{
    if(!m_typed.isEmpty()){
        m_typed = m_typed.substring(0, m_typed.getSize() - 1);
        m_text.setString(m_typed);
        updatePipePos();
    }
}

void TextInput::addString(const sf::String &toAdd)
{
    m_typed += toAdd;
    m_typed = m_typed.substring(0, MAX_INPUT_CHARS);
    m_text.setString(m_typed);
    updatePipePos();
}

TextInput::~TextInput()
{
}


void TextInput::setText(const sf::String &str)
{
    m_typed = str;
    m_text.setString(m_typed);
    updatePipePos();
}

void TextInput::updatePipePos()
{
    float textWidth = m_text.getGlobalBounds().width;
    m_pipe.setPosition(m_text.getPosition().x + textWidth, m_text.getPosition().y );
}

const sf::String &TextInput::getText() const
{
    return m_typed;
}

}
