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
 * File:   Button.cpp
 * Author: azarias
 *
 * Created on 21 octobre 2017, 16:49
 */

#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <functional>
#include "Button.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/Renderer.hpp"

namespace mp {

Button::Button(const std::string &text) :
    m_text(text,pr::resourceManager().getFont(), 50),
    m_width(m_text.getGlobalBounds().width),
    m_height(m_text.getGlobalBounds().height + 30),
    m_color(cc::Colors::fontColor),
    m_background(),
    m_border(),
    //Events
    clickedEvent(pr::nextEventCode()),
    selectdEvent(pr::nextEventCode())
{
    init();
}

Button::Button(const std::string &text, float xPos, float yPos, int iconId):
    m_text(text, pr::resourceManager().getFont(), 50),
    m_width(m_text.getGlobalBounds().width),
    m_height(m_text.getGlobalBounds().height + 30),
    m_color(cc::Colors::fontColor),
    m_background(),
    m_border(),
    //Events
    clickedEvent(pr::nextEventCode()),
    selectdEvent(pr::nextEventCode())
{
    init();
    setPosition(sf::Vector2f(xPos, yPos));
    if(iconId > -1)
        setIcon(sf::Sprite(pr::resourceManager().getTexture(iconId)));
}

void Button::init()
{
    m_rectColor = ColorTweening(cc::Colors::buttonColor);

    m_background.setFillColor(m_rectColor.get());
    m_border.setOutlineColor(cc::Colors::buttonBorderColor);
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineThickness(SF_BUTTON_BORDER);
    m_text.setFillColor(m_color.get());
    m_icon.setColor(m_color.get());
    updateSize();
}

float Button::getHeight() const
{
    return m_height + SF_BUTTON_BORDER * 2;
}

float Button::getWidth() const
{
    return m_width + SF_BUTTON_BORDER * 2;
}

void Button::update(const sf::Time &elapsed)
{
    m_color.update(elapsed.asSeconds());
    m_rectWidth.step(elapsed.asSeconds());
    m_rectColor.update(elapsed.asSeconds());
    updateText();
}

void Button::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    m_text.setPosition(position.x - m_width / 2.f, position.y);
    m_background.setPosition(position.x - m_width / 2.f, position.y);
    m_border.setPosition(position.x - m_width / 2.f, position.y);
}

void Button::handleEvent(const sf::Event& ev)
{
    bool isClicked = false;
    if (ev.type == sf::Event::MouseMoved) {
        sf::Vector2f realMovePos = pr::mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y ));

        bool was_hilighted = m_hilighted;
        setSelected(m_border.getGlobalBounds().contains(realMovePos));

        if(was_hilighted != m_hilighted)
            pr::trigger(selectdEvent);

    } else if (ev.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f realClickPos = pr::mapPixelToCoords(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        isClicked = ev.mouseButton.button == sf::Mouse::Left && m_border.getGlobalBounds().contains(realClickPos);
    } else if(isSelectionEvent(ev)){
        isClicked = true;
    }

    if (isClicked){        
        std::function<void()> callback = [this](){
            m_rectColor = ColorTweening(cc::Colors::buttonClickedColor, cc::Colors::buttonColor, 0.2, twin::quintOut);
        };

        m_rectColor = ColorTweening(cc::Colors::buttonColor, cc::Colors::buttonClickedColor, 0.2, twin::quintOut, callback);
        pr::trigger(clickedEvent);
    }

}

bool Button::isSelectionEvent(const sf::Event &ev) const
{
    return (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return ||
            ev.type == sf::Event::JoystickButtonPressed && ev.joystickButton.button == 0) && m_hilighted;
}

void Button::draw(Renderer &renderer) const
{
    if(!isVisible())return;


    renderer.render(m_border);
    renderer.render(m_background);
    renderer.render(m_icon);

    switch (m_alignment) {
    case Alignment::Center:
        renderer.pushTranslate(sf::Vector2f( (m_width - m_text.getGlobalBounds().width) / 2  , 0));
        break;
    case Alignment::TopLeft :
        renderer.pushTranslate(sf::Vector2f(10, 0));
        break;
    default:
        renderer.push();
        break;
    }

    renderer.render(m_text);

    renderer.pop();
}

void Button::setText(const std::string &text)
{
    m_text.setString(text);
}

void Button::setSelected(bool selected)
{
    if(m_hilighted == selected)return;

    if(selected){
        m_color = ColorTweening(m_color.get(), cc::Colors::higlithColor, 0.1, twin::easing::linear);
        m_rectWidth = twin::makeTwin(0.f, m_width, 0.5f, twin::easing::quintOut);
    }else{
        m_color = ColorTweening(m_color.get(), cc::Colors::fontColor, 0.1, twin::easing::linear);
        m_rectWidth = twin::makeTwin(m_width, 0.f, 0.5f, twin::easing::quintOut);
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
    m_alignment = Alignment::TopLeft;
    updateIcon();
}

void Button::setHeight(float height)
{
    m_height = height;
    updateSize();
}

void Button::setWidth(float width)
{
    m_width = width;
    updateSize();
}

void Button::updateSize()
{
    if(m_hilighted){
        m_rectWidth = twin::makeTwin(0.f, m_width, 0.5f, twin::easing::quintOut);
    }

    m_border.setSize(sf::Vector2f(m_width, m_height));
    sf::FloatRect nwSize = m_icon.getGlobalBounds();
    sf::Vector2f iconPosition(m_position.x + (m_width / 2) - nwSize.width, m_position.y +  (m_height - nwSize.height) / 2 );
    m_icon.setPosition(iconPosition);
    setPosition(m_position);
}

void Button::setIconTextureRect(const sf::IntRect &rect)
{
    m_icon.setTextureRect(rect);
}

void Button::updateIcon()
{
    //Same height as the text
    sf::FloatRect iFr = m_icon.getLocalBounds();

    float scale = m_height / iFr.height;
    m_icon.setScale(scale, scale);


    sf::FloatRect nwSize = m_icon.getGlobalBounds();
    sf::Vector2f iconPosition(m_position.x + m_width - nwSize.width, m_position.y +  (m_height - nwSize.height) / 2 );
    m_icon.setPosition(iconPosition);

    setWidth(m_width + iFr.width);
}



void Button::updateText()
{
    m_text.setFillColor(m_color.get());
    m_icon.setColor(m_color.get());
    m_background.setFillColor(m_rectColor.get());
    m_background.setSize(sf::Vector2f(m_rectWidth.get(), m_height));
}

void Button::setAlignment(Alignment al)
{
    m_alignment = al;
}


Button::~Button()
{

}

}


