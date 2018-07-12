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
 * File:   Dialog.h
 * Author: azarias
 *
 * Created on 23/10/2017
 */
#pragma once


#include <SFML/Graphics/RectangleShape.hpp>

#include "Menu.hpp"
#include "Widget.hpp"
#include "Button.hpp"
#include "I18NText.hpp"
#include "TextInput.hpp"
#include "src/lib/twin.hpp"
#include "src/common/Config.hpp"
#include "src/client/ClientConf.hpp"



namespace mp {

//BEGIN DIALOG
/**
 * @brief The Dialog class used to show a dialog in the middle
 * of the screen. There can be two types of dialogs : a message dialog,
 * and an input dialog.
 */
class Dialog : public Widget
{
public:
    enum DIALOG_STATE{
        DIALOG_HIDDEN,
        DIALOG_VISIBLE,
        DIALOG_APPEARING,
        DIALOG_HIDING
    };

    /**
     * @brief Dialog private dialog constructor, the user must call either input or message to get a pointer to a dialog
     * @param title the title of the dialog
     * @param message the message (if the dialog is a message dialog)
     * @param type the type of the dialog
     */
    Dialog(const sf::Uint64 id, const sf::String &title);

    virtual ~Dialog();

	/**
	 * @brief draw draws the dialog and all its sub-components
	 * @param target the target in which to draw
	 * @param states the states to use to draw
	 */
    virtual void render(Renderer &renderer) const;
	/**
	 * @brief handleEvent inherited function
	 * @param ev
	 */
    virtual bool handleEvent(const sf::Event &ev) override;


    /**
     * @brief update inherited function
     * @param elapsed elapsed time
     */
    virtual bool update(const sf::Time &elapsed);

	/**
	 * @brief isVisible wether the dialog is currently displayed
	 * @return wether the dialog is currently displayed
	 */
    bool isVisible() const
	{
        return m_state == DIALOG_APPEARING || m_state == DIALOG_VISIBLE;
	}

	/**
	 * @brief show shows the dialog, sets its state to visible
	 */
    void show(bool animate = true);

	/**
	 * @brief hide hides the dialog, sets its state to invisible
	 */
    void hide();

	/**
	 * @brief setTitle changes the title of the dialog
	 * @param str the new title of the dialog
	 */
    void setTitle(const sf::String &str);

    const sf::Uint64 &id() const;

protected:
    /**
     * @brief beforeDraw must be called before a child class starts to draw
     * in order to have the animation effect aplly
     * @param renderer
     */
    void beforeDraw(Renderer &renderer) const;

    /**
     * @brief afterDraw to call by child classes to remove
     * the effect applyed on 'beforedraw'
     * @param renderer
     */
    void afterDraw(Renderer &renderer) const;

    Menu &menu();

    /**
     * @brief originX origin of the dialog (it's not the 0,0 point of the screen)
     */
    const int originX = (SF_ARENA_WIDTH - SF_DIALOG_WIDTH)/2;

    /**
     * @brief originY y origin of the dialog
     */
    const int originY = (SF_ARENA_HEIGHT - SF_DIALOG_HEIGHT)/2;

    DIALOG_STATE state() const;

private:

    /**
     * @brief m_yPosition y position of this dialog
     */
    twin::Twin<float> m_yTransition;

    /**
     * @brief m_yPosition Y position of the dialog
     * (used to create animations)
     */
    float m_yPosition;

    /**
     * @brief m_menu menu containing all the buttons
     */
    Menu m_menu;

	/**
	 * @brief m_title title of the dialog
	 */
    I18NText m_title;

    /**
     * @brief background shape
     */
    sf::RectangleShape m_background;

    /**
     * @brief m_state current display state of the dialog
     */
    DIALOG_STATE m_state;

    /**
     * @brief m_id id of the dialog
     */
    const sf::Uint64 m_id;

public:
    Signal<> closeSignal;
};

//END DIALOG

//BEGIN INPUT DIALOG

/**
 * @brief The DialogInput class dialog inputs are here
 * to ask a question to the user, and have a textbox to
 * answer this question
 * he can either cancel or confirm the text he typed
 */
class DialogInput : public Dialog
{
public:
    /**
     * @brief DialogInput constructor
     * @param id id of this dialog
     * @param title title of the dialog
     * @param question question to ask to the user
     */
    DialogInput(const sf::Uint64 &id, const sf::String &title, const sf::String &question);

    virtual ~DialogInput();

    /**
     * @brief getValue gets the value typed by the user
     * @return a string containing the value typed by the user
     */
    const sf::String &getValue() const;

    /**
     * @brief update inherited function
     * @param elapsed
     */
    bool update(const sf::Time &elapsed) override;

    /**
     * @brief draw inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    bool handleEvent(const sf::Event &ev) override;

private:
    /**
     * @brief m_questionText text containing the question
     * asked to the user
     */
    I18NText m_questionText;

    /**
     * @brief m_input text input where the user can type
     * the answer
     */
    TextInput m_input;

public:
    Signal<> canceledSignal;
    Signal<sf::String> confirmedSignal;
};
//END INPUT DIALOG


//BEGIN QUESTION DIALOG

/**
 * @brief The DialogQuestion class used to ask
 * a yes-no question to the user
 */
class DialogQuestion : public Dialog
{
public:
    /**
     * @brief DialogQuestion constructor
     * @param id id of this dialog
     * @param title title of the dialog
     * @param question question to ask to the user
     */
    DialogQuestion(const sf::Uint64 &id, const sf::String &title, const sf::String &question);

    virtual ~DialogQuestion();

    /**
     * @brief getQuestion getter for the question asked
     * to the user
     * @return
     */
    const sf::String &getQuestion() const;

    /**
     * @brief setQuestion changes the question asked to the user
     * @param nwQuestion the new question to ask the user
     */
    void setQuestion(const sf::String &nwQuestion);

    /**
     * @brief render inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

private:
    /**
     * @brief m_questionText text asking the user a question
     */
    I18NText m_questionText;

public:
    Signal<> yesClickedSignal;
    Signal<> noClickedSignal;
};
//END QUESTION DIALOG

//BEGIN MESSAGE DIALOG

/**
 * @brief The DialogMessage class dialog showing
 * a message to the user, with only a "ok" button
 */
class DialogMessage : public Dialog
{
public:
    /**
     * @brief DialogMessage constructor
     * @param id dialog id
     * @param title
     * @param message message to show the user
     */
    DialogMessage(const sf::Uint64 &id, const sf::String &title, const sf::String &message);

    virtual ~DialogMessage();

    /**
     * @brief getMessage returns the message shown to the user
     * @return
     */
    sf::String getMessage() const;

    /**
     * @brief setMessage changes the message shown to the user
     * @param nwMessage
     */
    void setMessage(const sf::String &nwMessage);

    /**
     * @brief render inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

private:
    /**
     * @brief m_messageText the message shown to the user
     */
    I18NText m_messageText;

public:
    Signal<> okClickedSignal;
};
//END MESSAGE DIALOG


}
