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
#include <SFML/Graphics/Glyph.hpp>
#include "TextInput.hpp"

#include "src/client/Provider.hpp"
#include "src/client/Renderer.hpp"
#include "src/common/Config.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/ResourcesManager.hpp"

namespace mp {

TextInput::TextInput(const sf::Vector2f &position) :
    m_text("", pr::resourceManager().getFont()),
    m_pipe(),
    m_pipeIndex(0),
    m_typed(""),
    m_background(sf::Vector2f(9 * SF_DIALOG_WIDTH / 10.f, 50)),
    m_timer(sf::milliseconds(700), true)
{
    m_background.setOutlineColor(cc::Colors::dialogOutlineColor);
    m_background.setFillColor(cc::Colors::backgroundColor);
    m_background.setOutlineThickness(5);
    m_background.setPosition(position.x - 10, position.y);
    m_text.setPosition(position);
    m_pipe.setFillColor(sf::Color::White);
    m_pipe.setSize(sf::Vector2f(2, 40));
    movePipe(0);

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
        switch (ev.key.code) {
        case sf::Keyboard::Left: return movePipe(-1);
        case sf::Keyboard::Right: return movePipe(1);
        case sf::Keyboard::End: return movePipe(m_typed.getSize());
        case sf::Keyboard::Home: return movePipe(-m_typed.getSize());
        case sf::Keyboard::Delete: return supprChar();
        case sf::Keyboard::V:
            if(ev.key.control) addString(sf::Clipboard::getString());
            return true;
        case sf::Keyboard::C:
            if(ev.key.control) sf::Clipboard::setString(m_typed);
            return true;
        default: return false;
        }
    } else if (ev.type == sf::Event::TextEntered) {
        sf::Uint32 txt = ev.text.unicode;
        if(txt == 127)return false;
        if(txt == 8){//backspace
            removeChar();
        } else if(txt != 13) {
            //bug on linux : the 13 character (line cariage) is sent when pressing a character sometimes
            addString(sf::String(txt));
        }
        return true;
    }
    return false;
}

bool TextInput::supprChar()
{
    if(!m_typed.isEmpty() && m_pipeIndex < m_typed.getSize()){
        m_typed.erase(m_pipeIndex, 1);
        m_text.setString(m_typed);
        return true;
    }

    return false;
}

void TextInput::removeChar()
{
    if(!m_typed.isEmpty() && m_pipeIndex > 0){
        m_typed.erase(m_pipeIndex -1, 1);
        m_text.setString(m_typed);
        movePipe(-1);
    }
}

void TextInput::addString(const sf::String &toAdd)
{
    if(m_typed.isEmpty()){
        m_typed = toAdd;
    } else {
         m_typed.insert(m_pipeIndex, toAdd);
    }
    m_typed = m_typed.substring(0, MAX_INPUT_CHARS);
    m_text.setString(m_typed);
    movePipe(toAdd.getSize());
}

bool TextInput::movePipe(int direction)
{
    int oldIdx = m_pipeIndex;
    m_pipeIndex = math::clampf(0, (int)m_typed.getSize(), m_pipeIndex + direction);
    float xPos = 0;
    for(int i = 0; i < m_pipeIndex; ++i){
        xPos += pr::resourceManager().getFont().getGlyph(m_typed[i], m_text.getCharacterSize(), false).advance;
    }

    m_pipe.setPosition(m_text.getPosition().x + xPos, m_text.getPosition().y );
    return oldIdx != m_pipeIndex;
}

TextInput::~TextInput()
{
}

void TextInput::setText(const sf::String &str)
{
    m_typed = str;
    m_text.setString(m_typed);
    movePipe(1);
}

const sf::String &TextInput::getText() const
{
    return m_typed;
}

}
