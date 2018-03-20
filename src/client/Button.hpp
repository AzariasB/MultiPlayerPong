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
 * File:   Button.h
 * Author: azarias
 *
 * Created on 21 octobre 2017, 16:49
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include "../EventManager.hpp"
#include "Widget.hpp"

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
	 * @brief draw Function to draw the button
	 * @param target the target to use to draw the shapes
	 * @param states the states to use when rendering
	 */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

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
	 * @brief getPosition position of the button
	 * @return position of the button
	 */
	const sf::Vector2f &getPosition()
	{
        return m_text.getPosition();
	}

	/**
	 * @brief getWidth the width of the button
	 * @return the width of the button
	 */
	int getWidth() const
	{
		return m_text.getGlobalBounds().width + 10;
	}

	/**
	 * @brief getHeight the height of the button
	 * @return the height of the button
	 */
	int getHeight() const
	{
		return m_text.getGlobalBounds().height + 10;
	}

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
    void updateText();

    bool isSelectionEvent(const sf::Event &ev) const;
	/**
	 * @brief m_hilighted wether the button is currently higlighted
	 */
    bool m_hilighted = false;

	/**
	 * @brief m_text the text for the button
	 */
    sf::Text m_text;

public:
	const sf::Uint64 clickedEvent;
    const sf::Uint64 selectdEvent;
};

#endif /* BUTTON_H */

