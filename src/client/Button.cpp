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

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "Button.hpp"
#include "Provider.hpp"
#include "ResourcesManager.hpp"
#include "ClientConf.hpp"

Button::Button(const std::string &text) :
    m_text(text,pr::resourceManager().getFont()),
    clickedEvent(pr::nextEventCode()),
    selectdEvent(pr::nextEventCode()),
    m_color(cc::colors::fontColor)
{
    m_text.setFillColor(m_color.get());
}

Button::Button(const std::string &text, float xPos, float yPos):
    m_text(text, pr::resourceManager().getFont()),
    clickedEvent(pr::nextEventCode()),
    selectdEvent(pr::nextEventCode()),
    m_color(cc::colors::fontColor)
{
    setPosition(sf::Vector2f(xPos, yPos));
    m_text.setFillColor(m_color.get());
    m_icon.setColor(m_color.get());
    updateIcon();
}

void Button::update(const sf::Time &elapsed)
{
    m_color.update(elapsed.asSeconds());
    updateText();
}

void Button::setPosition(const sf::Vector2f& position)
{
    m_text.setPosition(position);
}

void Button::handleEvent(const sf::Event& ev)
{
    bool isClicked = false;
    if (ev.type == sf::Event::MouseMoved) {
        sf::Vector2f realMovePos = pr::mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y ));

        bool was_hilighted = m_hilighted;
        setSelected(m_text.getGlobalBounds().contains(realMovePos));

        if(was_hilighted != m_hilighted)
            pr::trigger(selectdEvent);

    } else if (ev.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f realClickPos = pr::mapPixelToCoords(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        isClicked = ev.mouseButton.button == sf::Mouse::Left && m_text.getGlobalBounds().contains(realClickPos);
    } else if(isSelectionEvent(ev)){
        isClicked = true;
    }

    if (isClicked)
        pr::trigger(clickedEvent);
}

bool Button::isSelectionEvent(const sf::Event &ev) const
{
    return (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return ||
                ev.type == sf::Event::JoystickButtonPressed && ev.joystickButton.button == 0) && m_hilighted;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_text, states);
    target.draw(m_icon, states);
}

void Button::setText(const std::string &text)
{
    m_text.setString(text);
}

void Button::setSelected(bool selected)
{
    if(selected){
        m_color = ColorTweening(m_color.get(), sf::Color::Red, 0.1, twin::easing::linear);
    }else{
        m_color = ColorTweening(m_color.get(), sf::Color::White, 0.1, twin::easing::linear);
    }
    m_hilighted = selected;
    updateText();
}

const sf::Sprite &Button::getIcon() const
{
    return m_icon;
}

void Button::setIcon(const sf::Sprite &sprite)
{
    m_icon = sprite;
    updateIcon();
}

void Button::updateIcon()
{
    //At the right of the text
    sf::FloatRect fr = m_text.getGlobalBounds();
    sf::Vector2f iconPosition(m_text.getPosition().x + fr.width + 10, m_text.getPosition().y + fr.height * 0.3);

    m_icon.setPosition(iconPosition);

    //Same height as the text
    sf::FloatRect iFr = m_icon.getLocalBounds();
    float scale = fr.height / iFr.height;
    m_icon.setScale(scale, scale);

}

void Button::updateText()
{
    m_text.setFillColor(m_color.get());
    m_icon.setColor(m_color.get());
}

Button::~Button()
{

}

