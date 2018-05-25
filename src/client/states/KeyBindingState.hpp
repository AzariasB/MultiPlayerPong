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
 * File:   KeyOptions.hpp
 * Author: azarias
 *
 * Created on 3/11/2017
 */
#pragma once

#include "src/client/widgets/Menu.hpp"
#include "src/client/KeyBinding.hpp"
#include "src/client/State.hpp"
#include "src/client/Assets.hpp"


namespace mp {

class Dialog;

/**
 * @brief The KeyOptions class Menu showing
 * all the key binding, and offering the possibility
 * to reset the key bindings to their defaults
 */
class KeyBindingState : public State
{
public:
    /**
     * @brief KeyOptions constructor
     * @param app reference to the app's object
     * @param startX the starting X point of the menu
     * @param startY the starting Y point of the menu
     */
    KeyBindingState();

    virtual ~KeyBindingState();

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    void handleEvent(const sf::Event &ev) override;

    /**
     * @brief draw inherited function
     * @param target
     * @param states
     */
    void draw(Renderer &renderer) const override;

    /**
     * @brief update inherited function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

private:
    /**
     * @brief The ActionsButton struct
     * struct used internally to associate every
     * button with it's action
     */
    struct ActionsButton{
        /**
         * @brief ActionsButton constructor
         * @param b a pointer to the button
         * @param ka the action
         */
        ActionsButton(Button *b, KeyBinding::KEY_ACTION ka):
            button(b),
            action(ka)
        {

        }

        /**
         * @brief button the button
         */
        Button *button;

        /**
         * @brief action the action associated with the button
         */
        KeyBinding::KEY_ACTION action;
    };

    const Assets::IconAtlas::Holder &actionIcon(KeyBinding::KEY_ACTION action) const;

    /**
     * @brief buttonClicked whenever a button is clicked, to change the binding
     * of a key
     * @param ab the actionButton associated with the button clicked
     */
    void buttonClicked(ActionsButton *ab);

    /**
     * @brief cancelDialog when the dialog is canceled
     */
    void cancelDialog();

    /**
     * @brief resetKeys resets all the key bindings
     * and updates the view
     */
    void resetKeys();


    sf::Uint64 m_messageDialogId = 0;

    /**
     * @brief m_menu the menu showing all the keys
     */
    Menu m_menu;

    /**
     * @brief m_actions all the button with their associated actions
     */
    std::vector<std::unique_ptr<ActionsButton>> m_actions;

    /**
     * @brief m_waitingAction the currently action
     * waiting to have a key binding
     */
    ActionsButton *m_waitingAction = 0;

};

}

