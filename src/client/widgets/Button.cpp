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
#include "src/client/Translator.hpp"

namespace mp {

Button::Button(const sf::String &text) :
    m_text(pr::translator().make(text, 50)),
    m_width(text == "" ? 0 : m_text.width()),
    m_height(m_text.height() + 30),
    m_color(cc::Colors::fontColor),
    m_background(),
    m_border(),
    //Events
    clickedSignal(),
    selectedSignal()
{
    init();
}

Button::Button(const sf::String &text, float xPos, float yPos):
    m_text(pr::translator().make(text, 50)),
    m_width(text == "" ? 0 : m_text.width()),
    m_height(m_text.height() + 30),
    m_color(cc::Colors::fontColor),
    m_background(),
    m_border(),
    //Events
    clickedSignal(),
    selectedSignal()
{
    init();
    setPosition(sf::Vector2f(xPos, yPos));
}

Button::Button(const sf::String &text, float xPos, float yPos, const Assets::IconAtlas::Holder &icon):
    m_text(pr::translator().make(text, 50)),
    m_width(text.isEmpty() ? 30 : m_text.width() + 90),
    m_height(m_text.height() + 30),
    m_color(cc::Colors::fontColor),
    m_background(),
    m_border(),
    //Events
    clickedSignal(),
    selectedSignal()
{
    init();
    setPosition(sf::Vector2f(xPos, yPos));
    setIcon(sf::Sprite(pr::resourceManager().get<const sf::Texture&>(icon.textureId), icon.bounds));
}

Button::Button(const std::vector<sf::String> &text, float xPos, float yPos, const Assets::IconAtlas::Holder &icon):
    m_text(pr::translator().make(text, 50)),
    m_width(m_text.width() + 90),
    m_height(m_text.height() + 30),
    m_color(cc::Colors::fontColor),
    m_background(),
    m_border(),
    // Signals
    clickedSignal(),
    selectedSignal()
{
    init();
    setPosition(sf::Vector2f(xPos, yPos));
    setIcon(sf::Sprite(pr::resourceManager().get<const sf::Texture&>(icon.textureId), icon.bounds));
}


void Button::setOrigin(const sf::Vector2f &origin)
{
    m_origin = origin;

    m_border.setOrigin(origin);
    m_background.setOrigin(origin);

    setPosition(m_position);
}

void Button::setOrigin(float x, float y)
{
    setOrigin(sf::Vector2f(x,y));
}

sf::FloatRect Button::getGlobalBounds() const
{
    return m_background.getGlobalBounds();
}

void Button::init()
{
    m_listenerId = pr::translator().translationChangedSignal.add([this](){
        setWidth(m_text.width() + m_icon.getGlobalBounds().width);
    });
    m_rectColor = ColorTweening(cc::Colors::buttonColor);
    m_icon.setOrigin(m_icon.getGlobalBounds().width, m_icon.getGlobalBounds().height / 2.f);

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
    return m_height;
}

float Button::getWidth() const
{
    return m_width;
}

bool Button::update(const sf::Time &elapsed)
{
    m_color.update(elapsed);
    m_rectWidth.step(elapsed);
    m_rectColor.update(elapsed);
    updateText();
    return Widget::update(elapsed);
}

void Button::setPosition(const sf::Vector2f& position)
{
    m_position = position;
    m_background.setPosition(position.x, position.y);
    m_border.setPosition(position.x, position.y);

    m_text.setPosition(m_position.x - m_origin.x, m_position.y - m_origin.y);
    changeIconScale();
}

bool Button::handleEvent(const sf::Event& ev)
{
    bool isClicked = false;
    if (ev.type == sf::Event::MouseMoved) {
        sf::Vector2f realMovePos = pr::mapPixelToCoords(sf::Vector2i(ev.mouseMove.x, ev.mouseMove.y ));

        bool wasHilighted = m_hilighted;
        bool isSelected = m_border.getGlobalBounds().contains(realMovePos);

        if(isSelected)
            setSelected(true);

        if(wasHilighted != m_hilighted)
            selectedSignal.trigger();

    } else if (ev.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f realClickPos = pr::mapPixelToCoords(sf::Vector2i(ev.mouseButton.x, ev.mouseButton.y));
        isClicked = ev.mouseButton.button == sf::Mouse::Left && m_border.getGlobalBounds().contains(realClickPos);
    } else if(isSelectionEvent(ev)){
        isClicked = true;
    }

    if (isClicked){        
        std::function<void()> callback = [this](){
            m_rectColor = ColorTweening(cc::Colors::buttonClickedColor, cc::Colors::buttonColor, sf::milliseconds(200), twin::quintOut);
        };

        m_rectColor = ColorTweening(cc::Colors::buttonColor, cc::Colors::buttonClickedColor, sf::milliseconds(200), twin::quintOut, callback);
        clickedSignal.trigger();
        return true;
    }

    return false;
}

bool Button::isSelectionEvent(const sf::Event &ev) const
{
    return ( (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return) ||
            (ev.type == sf::Event::JoystickButtonPressed && ev.joystickButton.button == 0)) && m_hilighted;
}

void Button::render(Renderer &renderer) const
{
    if(!isVisible())return;


    renderer.draw(m_border);
    renderer.draw(m_background);
    renderer.draw(m_icon);

    switch (m_alignment) {
    case Alignment::Center:
        renderer.push()
                .translate(sf::Vector2f( (m_width - m_text.getGlobalBounds().width) / 2  , 0));
        break;
    case Alignment::TopLeft :
        renderer.push()
                .translate(sf::Vector2f(10, 0));
        break;
    default:
        renderer.push();
        break;
    }

    renderer.draw(m_text);

    renderer.pop();
}

void Button::setText(const sf::String &text)
{
    m_text.setString(text);
}

void Button::setText(const std::vector<sf::String> &str)
{
    m_text.setString(str);
}

void Button::setSelected(bool selected)
{
    if(m_hilighted == selected)return;

    if(selected){
        m_color = ColorTweening(m_color.get(), cc::Colors::higlithColor, sf::milliseconds(100), twin::easing::linear);
        m_rectWidth = twin::makeTwin(0.f, m_width, sf::milliseconds(500), twin::easing::quintOut);
    }else{
        m_color = ColorTweening(m_color.get(), cc::Colors::fontColor, sf::milliseconds(100), twin::easing::linear);
        m_rectWidth = twin::makeTwin(m_width, 0.f, sf::milliseconds(500), twin::easing::quintOut);
    }
    m_hilighted = selected;
    updateText();
}

const sf::Sprite &Button::getIcon() const
{
    return m_icon;
}

void Button::setIcon(const Assets::IconAtlas::Holder &icon)
{
    setIcon(sf::Sprite(pr::resourceManager().get<const sf::Texture&>(icon.textureId), icon.bounds));
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
        m_rectWidth = twin::makeTwin(0.f, m_width, sf::milliseconds(500), twin::easing::quintOut);
    }

    m_border.setSize(sf::Vector2f(m_width, m_height));
    changeIconScale();
    setPosition(m_position);
}

void Button::setIconTextureRect(const sf::IntRect &rect)
{
    m_icon.setTextureRect(rect);
}

void Button::changeIconScale()
{
    //Same height as the text
    sf::FloatRect iFr = m_icon.getLocalBounds();

    float scale = m_height / iFr.height;
    m_icon.setScale(scale, scale);
    m_icon.setOrigin(iFr.width, iFr.height / 2.f);
    m_icon.setPosition( (m_position.x - m_origin.x) + m_width, m_position.y - m_origin.y + (m_height / 2.f));
}

void Button::updateIcon()
{
    changeIconScale();
    // setWidth(m_width + m_icon.getGlobalBounds().width - oldIconWidth);
}


void Button::updateText()
{
    m_text.setFillColor(m_color.get());
    m_icon.setColor(m_color.get());
    m_background.setFillColor(m_rectColor.get());
    m_background.setSize(sf::Vector2f(m_rectWidth.get(), m_height));
}

void Button::removeIcon()
{
    m_icon = sf::Sprite();
}

void Button::setAlignment(Alignment al)
{
    m_alignment = al;
}


Button::~Button()
{
    pr::translator().translationChangedSignal.remove(m_listenerId);
}

}


