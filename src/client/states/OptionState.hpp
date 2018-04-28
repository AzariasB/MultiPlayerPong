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
 * File:   Optionstate.hpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#pragma once

#include "src/client/State.hpp"
#include "src/client/widgets/Menu.hpp"


/**
 * @brief The OptionState class
 *  state used to change the client's options
 * the sound, the key bindings, ...
 */
class OptionState : public State
{
public:
	/**
	 * @brief OptionState Constructor
	 * @param app reference to the app
	 */
    OptionState();

	/**
	 * @brief update inherited function
	 * @param elapsed
	 */
	void update(const sf::Time &elapsed) override;

	/**
	 * @brief draw inherited function
	 * @param renderer
	 */
	void draw(Renderer &renderer) const override;

	/**
	 * @brief handleEvent inherited function
	 * @param ev
	 */
	void handleEvent(const sf::Event &ev) override;

	/**
	 * @brief toggleSound changes the sound state
	 * and update the icon
	 */
	void toggleSound();

	virtual ~OptionState();

private:
	/**
	 * @brief getCurrentSoundRect the textureRect corresponding to the current
	 * sound state
	 * @return
	 */
	const sf::IntRect &getCurrentSoundRect() const;

    Button *m_muteButton = 0;

	/**
	 * @brief m_menu the menu with all the options
	 */
	Menu m_menu;
	/**
	 * @brief m_withSoundRect rect for the icon "with sound"
	 */
    sf::IntRect m_withSoundRect = sf::IntRect(65, 0, 64, 53);

	/**
	 * @brief m_withoutSoundRect rect for the icon "without sound"
	 */
    sf::IntRect m_withoutSoundRect = sf::IntRect(0, 0, 64, 53);


};


