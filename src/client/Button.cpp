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
 * File:   Button.cpp
 * Author: azarias
 * 
 * Created on 21 octobre 2017, 16:49
 */

#include "Button.hpp"
#include "ClientApp.hpp"
#include <SFML/Window.hpp>
#include <iostream>

Button::Button(ClientApp &app, const std::string &text) :
Widget(app),
m_text(text, app.getResourcesManager().getFont()),
clickedEvent(app.getGame().getEventManager().nextEventCode())
{
}

Button::Button(ClientApp &app, const std::string &text, float xPos, float yPos):
Widget(app),
m_text(text, app.getResourcesManager().getFont()),
clickedEvent(app.getGame().getEventManager().nextEventCode())
{
	setPosition(sf::Vector2f(xPos, yPos));
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_text.setPosition(position);
}

void Button::handleEvent(const sf::Event& ev)
{
	if (ev.type == sf::Event::MouseMoved) {
		sf::Vector2f realMovePos = app().getWindow().mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y ));
		m_hilighted = m_text.getGlobalBounds().contains(realMovePos);
		m_text.setFillColor(m_hilighted ? sf::Color::Red : sf::Color::White);
	} else if (ev.type == sf::Event::MouseButtonPressed) {
		sf::Vector2f realClickPos = app().getWindow().mapPixelToCoords(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
		bool isClicked = ev.mouseButton.button == sf::Mouse::Left && m_text.getGlobalBounds().contains(realClickPos);
		if (isClicked) {
			app().getGame().getEventManager().trigger(clickedEvent);
		}
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_text, states);
}

void Button::setText(const std::string &text)
{
	m_text.setString(text);
}

Button::~Button()
{

}

