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
 * File:   Menu.hpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Widget.hpp"
#include "Button.hpp"

/**
 * @brief The Menu class a menu is a widget
 * containing several buttons and labels
 * this eases the way of creating menus
 */
class Menu : public Widget
{
public:
	/**
	 * @brief Menu constructor
	 * @param app reference to the application
	 */
    Menu();

	virtual ~Menu();

	/**
	 * @brief draw inherited function
	 * @param target
	 * @param states
	 */
    void draw(Renderer &renderer) const;

	/**
	 * @brief handleEvent inherited function
	 * @param ev
	 */
	void handleEvent(const sf::Event &ev) override;

    /**
     * @brief update inherited function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

	/**
	 * @brief addButton adds a button to the menu, with the given text, at the given position
	 * returns the button if the caller wants to make additional changes, and store it for another usage
	 * @param content the string to display
	 * @param xPos the X position of the button
	 * @param yPos the Y position of the button
	 * @return the button newly created
	 */
    std::unique_ptr<Button> &addButton(const std::string &content, float xPos, float yPos);

    /**
     * @brief addCenteredButton adds the button to the menu, with the given text, and
     * centers it at the given position (instead of placing its top left corner at the
     * given position)
     * @param content text of the button
     * @param xCenter x coordinate of the button
     * @param yCenter y coordinate of the button
     * @return
     */
    std::unique_ptr<Button> &addCenteredButton(const std::string &content, float xCenter, float yCenter);

	/**
	 * @brief addLabel adds a label to the menu, with the given text, at the given result
	 * @param content the string to display
	 * @param xpOs the X position of the text
	 * @param yPos the Y position of the text
	 * @return the text newly created
	 */
    std::unique_ptr<sf::Text> &addLabel(const std::string &content, float xpOs, float yPos, unsigned int charSize = 30);

    /**
     * @brief addCenteredLabel adds the label to the menu, with the given text, and centers it
     * at the given position (instead of putting its top-left cordner at the given position)
     * @param content the text of the label
     * @param xCenter x position of the labels center
     * @param yCenter y position of the labels center
     * @return the newly created text
     */
    std::unique_ptr<sf::Text> &addCenteredLabel(const std::string &content, float xCenter, float yCenter, unsigned int charSize = 30);

	/**
	 * @brief addSprite adds a sprite to the menu, using the given texture, and the texture rectangle
	 * returns the created sprite, in order to modify it more if needed
	 * @param textureName the name of the texture in the resource manager
	 * @param pos the position of the sprite
	 * @param textureRect the rectangle texture
	 * @return the newly created sprite
	 */
	std::unique_ptr<sf::Sprite> &addSprite(const std::string &textureName, const sf::Vector2f &pos, const sf::IntRect &textureRect);

    /**
     * @brief addCenteredSprite add the sprite to the menu, centered at the given location
     * @param textureName name of the texture
     * @param centerPos center of the sprite
     * @param textureRect texture rectangle of the sprite
     * @return
     */
    std::unique_ptr<sf::Sprite> &addCenteredSprite(const std::string &textureName, const sf::Vector2f &centerPos, const sf::IntRect &textureRect);

private:
    /**
     * @brief changeSelection updates the selected button
     * @param dir
     */
    void changeSelection(int dir);

    /**
     * @brief setSeletedIndex changes the selected button index
     * @param nwIndex
     */
    void setSeletedIndex(int nwIndex);

	/**
	 * @brief m_labels all the labels of the menu
	 */
	std::vector<std::unique_ptr<sf::Text>> m_labels;

	/**
	 * @brief m_buttons all the buttons of the menu
	 */
	std::vector<std::unique_ptr<Button>> m_buttons;

    std::size_t m_selectedButton = 0;

	/**
	 * @brief m_sprites all the sprites of the menu
	 */
	std::vector<std::unique_ptr<sf::Sprite>> m_sprites;
};


