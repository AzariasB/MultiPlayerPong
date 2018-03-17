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
 * File:   TextInput.cpp
 * Author: azarias
 * 
 * Created on 22 octobre 2017, 16:29
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "TextInput.hpp"
#include "Provider.hpp"
#include "ResourcesManager.hpp"
#include "src/Config.hpp"

TextInput::TextInput() :
m_text("", pr::resourceManager().getFont()),
m_pipe("|", pr::resourceManager().getFont()),
m_typed("")
{

}

void TextInput::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	sf::RectangleShape rect(sf::Vector2f(SF_DIALOG_WIDTH,50));
	rect.setPosition(m_text.getPosition().x - 10, m_text.getPosition().y);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(5);
	rect.setFillColor(sf::Color::Black);

	target.draw(rect, states);
	target.draw(m_text, states);

	if(m_clock.getElapsedTime().asSeconds() < 0.7){
		target.draw(m_pipe,states);
	}else if(m_clock.getElapsedTime().asSeconds() > 1.4){
		m_clock.restart();
	}
}

void TextInput::handleEvent(const sf::Event& ev)
{
	if (ev.type == sf::Event::TextEntered) {
		sf::Uint32 txt = ev.text.unicode;
		if(txt == 8){//backspace
			if(!m_typed.empty())
				m_typed.pop_back();
		}else if(txt > 31 && txt < 127){
			m_typed += (char) ev.text.unicode;
		}
		m_text.setString(m_typed);
		if(m_text.getGlobalBounds().width + 40 > SF_DIALOG_WIDTH){
			m_typed.pop_back();
			m_text.setString(m_typed);
		}
		updatePipePos();
	}
}

TextInput::~TextInput()
{
}

void TextInput::setPosition(const sf::Vector2f &pos)
{
	m_text.setPosition(pos);
	updatePipePos();
}

void TextInput::setText(const std::string &str)
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

const std::string& TextInput::getText() const
{
	return m_typed;
}
