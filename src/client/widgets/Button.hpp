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
 * File:   Button.h
 * Author: azarias
 *
 * Created on 21 octobre 2017, 16:49
 */

#pragma once


#include <SFML/System.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Widget.hpp"
#include "src/lib/twin.hpp"
#include "src/client/Assets.hpp"
#include "src/common/EventManager.hpp"
#include "src/client/ColorTweening.hpp"


namespace mp {

class Renderer;

/**
 * @brief The Button is a widget used to be clickable (and hoverable)
 * when the mouse hovers the bouton, it's colors changes, when it's clicked
 * an event "clickEventCode" is fired
 * The text of the button can be changed
 */
class Button : public Widget {
public:
    /**
     * @brief Button
     * @param app reference to the Client application
     * @param text the text to display inside the button
     */
    Button(const std::string &text = "");

    /**
     * @brief Button constructor
     * @param app reference to the Client application
     * @param text text to show
     * @param xpos x position of the button
     * @param yPos y position of the button
     */
    Button(const std::string &text, float xPos, float yPos);

    /**
     * @brief Button constructor
     * @param app reference to the Client application
     * @param text text to show
     * @param xpos x position of the button
     * @param yPos y position of the button
     */
    Button(const std::string &text, float xPos, float yPos, const Assets::IconAtlas::Holder &icon);


    /**
     * @brief update inerited function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief draw Function to draw the button
     * @param target the target to use to draw the shapes
     * @param states the states to use when rendering
     */
    void render(Renderer &renderer) const;

    /**
     * @brief setPosition sets the position of the button
     * @param position the new position (top-left) of the button
     */
    void setPosition(const sf::Vector2f &m_position);

    /**
     * @brief handleEvent handles a SFML input/event
     * @param ev the sfml object for the event
     */
    void handleEvent(const sf::Event &ev);

    /**
     * @brief setAlignment setter for the alignment
     * @param al
     */
    void setAlignment(Alignment al);

    /**
     * @brief setWidth setter for the width
     * @param width
     */
    void setWidth(float width);

    /**
     * @brief setHeight setter for the height
     * @param height
     */
    void setHeight(float height);

    /**
     * @brief getPosition position of the button
     * @return position of the button
     */
    const sf::Vector2f &getPosition() const
    {
        return m_text.getPosition();
    }

    /**
     * @brief getIcon icon of the button (if any)
     * @return
     */
    const sf::Sprite &getIcon() const;

    /**
     * @brief setIconTextureRect changes the texture rect
     * of the icon
     */
    void setIconTextureRect(const sf::IntRect &rect);

    /**
     * @brief setIcon sets the icon
     * @param sprite
     */
    void setIcon(const sf::Sprite &sprite);


    /**
     * @brief getWidth the width of the button
     * @return the width of the button
     */
    float getWidth() const;

    /**
     * @brief getHeight the height of the button
     * @return the height of the button
     */
    float getHeight() const;


    bool isSelected() const
    {
        return m_hilighted;
    }

    /**
     * @brief changes the text of the button, the dimensions will also change
     * @param text the new text to set
     */
    void setText(const std::string &text);

    /**
     * @brief setSelected changes the selected state of the button
     * @param selected
     */
    void setSelected(bool selected);

    virtual ~Button();

private:

    void init();

    /**
     * @brief updateText update the text properties
     */
    void updateText();

    /**
     * @brief updateIcon update the icon properties
     */
    void updateIcon();

    /**
     * @brief updateSize changes the size of the rectangles
     */
    void updateSize();

    /**
     * @brief isSelectionEvent if the given event is an event
     * trigerred to select the button
     * @param ev
     * @return
     */
    bool isSelectionEvent(const sf::Event &ev) const;

    /**
     * @brief m_hilighted wether the button is currently higlighted
     */
    bool m_hilighted = false;

    /**
     * @brief m_text the text for the button
     */
    sf::Text m_text;

    /**
     * @brief m_width width of the button
     */
    float m_width;

    /**
     * @brief m_height height of the button
     */
    float m_height;

    /**
     * @brief m_position keep the position in memory
     * to update it when changing the height/width
     */
    sf::Vector2f m_position = sf::Vector2f(0,0);

    /**
     * @brief m_icon icon of the button (optional)
     */
    sf::Sprite m_icon;

    /**
     * @brief m_color text color of the button
     */
    ColorTweening m_color;


    /**
     * @brief m_rectColor color of the rectangle
     * that appear when the button is selected
     */
    ColorTweening m_rectColor;

    /**
     * @brief m_rectWidth tweening used
     * to animate the button background
     */
    twin::Twin<float> m_rectWidth;

    /**
     * @brief m_background background
     * color of the button
     */
    sf::RectangleShape m_background;

    /**
     * @brief m_border the border
     * of the button
     */
    sf::RectangleShape m_border;

    /**
     * @brief m_alignment button alignment
     */
    Alignment m_alignment = Center;

public:
    const sf::Uint64 clickedEvent;
    const sf::Uint64 selectdEvent;
};



}


