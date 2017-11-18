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
 * File:   EndState.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:50
 */

#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "Button.hpp"
#include "State.hpp"
#include "Dialog.hpp"

/**
 * @brief The EndState class this state
 * is used when a game ends. It shows the result of the
 * game (win/loose) and the points gained during
 * the match
 */
class EndState : public State {
public:
	/**
	 * @brief EndState constructor
	 * @param app reference to the application
	 */
    EndState();

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

	/**
	 * @brief backButtonPressed when the "ok" or the cross of the dialog is pressed,
	 * goes back to the main menu
	 */
	void backButtonPressed();

	virtual ~EndState();
private:
	/**
	 * @brief m_messageDialog the dialog used to show the result
	 * of the game
	 */
	Dialog *m_messageDialog;

};

#endif /* ENDSTATE_H */

