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
 * File:   Dialog.h
 * Author: azarias
 *
 * Created on 23/10/2017
 */
#ifndef DIALOG_H
#define DIALOG_H

#include "Widget.hpp"
#include "Button.hpp"
#include "TextInput.hpp"
#include "src/Config.hpp"
#include "src/lib/twin.hpp"

/**
 * @brief The Dialog class used to show a dialog in the middle
 * of the screen. There can be two types of dialogs : a message dialog,
 * and an input dialog.
 */
class Dialog : public Widget
{
public:
	/**
	 * @brief message a pointer to a dialog showing the given message, with the given title
	 * @param message the message to display in the middle of the dialog
	 * @param title the title of the dialog
	 * @return a pointer to the dialog
	 */
    static Dialog *message(const std::string &message, const std::string &title);

	/**
	 * @brief input a pointer to a dialog with a text input
	 * @param title the title of the input
	 * @return a pointer to the dialog
	 */
    static Dialog *input(const std::string &title);

	/**
	 * @brief draw draws the dialog and all its sub-components
	 * @param target the target in which to draw
	 * @param states the states to use to draw
	 */
    virtual void draw(Renderer &renderer) const;
	/**
	 * @brief handleEvent inherited function
	 * @param ev
	 */
	virtual void handleEvent(const sf::Event &ev);


    /**
     * @brief update inherited function
     * @param elapsed elapsed time
     */
    virtual void update(const sf::Time &elapsed);

	/**
	 * @brief isVisible wether the dialog is currently displayed
	 * @return wether the dialog is currently displayed
	 */
	bool isVisible() const
	{
		return m_isVisible;
	}

	/**
	 * @brief getResult used when the dialog is an input dialog (otherwise, returns an empty string)
	 * @return the text typed by the user
	 */
	const std::string &getResult() const;

	/**
	 * @brief show shows the dialog, sets its state to visible
	 */
    void show(bool animate = true);

	/**
	 * @brief hide hides the dialog, sets its state to invisible
	 */
    void hide(bool animate = true);

	/**
	 * @brief okButtonClicked function called when the button "ok" is pressed
	 * will fire the "ok" event of the dialog
	 */
	void okButtonClicked();

	/**
	 * @brief cancelButtonClicked function called when the button "cancel" or the cross is pressed
	 * will fire the "cancel" event of the dialog
	 */
	void cancelButtonClicked();

	/**
	 * @brief setTitle changes the title of the dialog
	 * @param str the new title of the dialog
	 */
	void setTitle(const std::string &str);

	/**
	 * @brief setMessage changes the message of the dialog
	 * @param str the new message of the dialog
	 */
	void setMessage(const std::string &str);

	/**
	 * @brief setOkButtonTitle changes the text contained in the "ok" button
	 * @param str the new text of the "ok" button
	 */
	void setOkButtonTitle(const std::string &str);

private:
	/**
	 * @brief The DIALOG_TYPE enum types of dialogs
	 */
	enum DIALOG_TYPE{
	        INPUT,
	        MESSAGE
	};

	/**
	 * @brief Dialog private dialog constructor, the user must call either input or message to get a pointer to a dialog
	 * @param title the title of the dialog
	 * @param message the message (if the dialog is a message dialog)
	 * @param type the type of the dialog
	 */
    Dialog(const std::string &title, const std::string &message = "", DIALOG_TYPE type = DIALOG_TYPE::MESSAGE);


    /**
     * @brief m_yPosition y position of this dialog
     */
    twin::Twin<float, float> m_yTransition;

    /**
     * @brief m_yPosition Y position of the dialog
     * (used to create animations)
     */
    float m_yPosition;

	/**
	 * @brief m_okButton the button to the bottom-left of the dialog ("confirm" by default)
	 */
	Button m_okButton;

	/**
	 * @brief m_cancelButton the button to the bottom-right of the dialog("cancel" by default)
	 */
	Button m_cancelButton;

	/**
	 * @brief m_xButton the top-right cross of the dialog
	 */
	Button m_xButton;

	/**
	 * @brief m_input the text input (only used if the dialog is of INPUT type)
	 */
	TextInput m_input;

	/**
	 * @brief m_title title of the dialog
	 */
	sf::Text m_title;

	/**
	 * @brief m_message message of the dialog (only used if the dialog is of MESSAGE type)
	 */
	sf::Text m_message;

	/**
	 * @brief m_type the type of the dialog
	 */
	DIALOG_TYPE m_type;

	/**
	 * @brief originX origin of the dialog (it's not the 0,0 point of the screen)
	 */
    const int originX = (SF_ARENA_WIDTH- SF_DIALOG_WIDTH)/2;

	/**
	 * @brief originY y origin of the dialog
	 */
    const int originY = (SF_ARENA_HEIGHT - SF_DIALOG_HEIGHT)/2;

	/**
	 * @brief m_isVisible wether the dialog is visible
	 */
	bool m_isVisible = false;

public:

	const sf::Uint64 okEvent;
	const sf::Uint64 cancelEvent;
};

#endif // DIALOG_H
