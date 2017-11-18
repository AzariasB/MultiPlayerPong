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
 * File:   MenuState.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include <SFML/Window/Event.hpp>
#include "State.hpp"
#include "Button.hpp"
#include "Dialog.hpp"
#include "Menu.hpp"

/**
 * @brief The MenuState class state used
 * at the start of the application, to show the play button
 * the quit button (and maybe others to come)
 */
class MenuState : public State {
public:
	/**
	 * @brief MenuState constructor
	 * @param client reference to the app
	 */
    MenuState();

	/**
	 * @brief draw inherited function
	 * @param renderer
	 */
	void draw(Renderer& renderer) const override;

	/**
	 * @brief handleEvent inherited function
	 * @param ev
	 */
	void handleEvent(const sf::Event& ev) override;

	/**
	 * @brief dialogConfirmed when the dialog asking for the IP
	 * is confirmed, checks if the IP adress is correct, and if
	 * it is, goes to the Waiting state, otherwise, shows a dialog
	 * saying the ip is a wrong one
	 */
	void dialogConfirmed();

	/**
	 * @brief update inherited function
	 * @param dtS
	 */
	void update(const sf::Time &elapsed) override;

	/**
	 * @brief onEnter inherited function
	 * @param data
	 */
	void onEnter(BaseStateData *data) override;

	/**
	 * @brief onLeave inherited function
	 */
	void onLeave() override;

	virtual ~MenuState();
private :
	/**
	 * @brief isValidIp checks if the given string is a valid ip (using regexp)
	 * @param enteredIp the ip entered by the user
	 * @return wehter the given string is a valid ip
	 */
	bool isValidIp(const std::string &enteredIp) const;

	/**
	 * @brief m_menu Menu holding all the differents buttons
	 */
	Menu m_menu;

	/**
	 * @brief m_inputDialog input dialog
	 */
	Dialog *m_inputDialog;

	/**
	 * @brief m_messageDialog the message dialog
	 */
	Dialog *m_messageDialog;
};

#endif /* MENUSTATE_H */

