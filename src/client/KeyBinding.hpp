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
 * File:   KeyBinding.hpp
 * Author: azarias
 *
 * Created on 2/11/2017
 */
#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>


namespace mp {



/**
 * @brief The EnumClassHash struct
 */
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

/**
 * @brief The KeyBinding class saves the keys bindings
 * available to change (for now : going up/down)
 */
class KeyBinding
{
public:
    /**
     * @brief The KEY_ACTION enum all the possible action
     * the player can do
     */
    enum KEY_ACTION{
        GO_UP,
        GO_DOWN,
        UNKNOWN
    };

    /**
     * @brief allActions list of all the possible actions
     * the user can perform
     */
    static const std::array<KEY_ACTION, 2> allActions;

    /**
     * @brief KeyBinding constructor
     */
    KeyBinding();

    /**
     * @brief toGameEvent the game object takes specific events, this method is here to adapt the
     * actual events, to game events
     * @param ev the event sent by the user
     * @return  the event translated for the game
     */
    sf::Event toGameEvent(const sf::Event &ev) const;

    /**
     * @brief toString the "name" of the key
     * @param k the keyboard's key
     * @return the name of the given key
     */
    sf::String toString(sf::Keyboard::Key k) const;

    /**
     * @brief toString returns the name of the action, as saved (e.g. "Go Up : Up")
     * @param action the action
     * @return the action in the form of a string
     */
    sf::String toString(KEY_ACTION action);

    /**
     * @brief setKeyAction changes the key for a given action
     * @param action the action related
     * @param binding the key to use for this action
     */
    void setKeyAction(KEY_ACTION action, sf::Keyboard::Key binding)
    {
        m_keyActions[action].actualKey = binding;
    }

    void resetBindings();

private:
    /**
         * @brief The KeyAction struct structure used
         * internally to save data about a key binding :
         *  - its title
         *  - the default key
         *  - the key as set by the user (by the default is the same as the default key)
         */
    struct KeyAction{
        KeyAction():
            actualKey(sf::Keyboard::Unknown),
            title(""),
            defaultKey(sf::Keyboard::Unknown)
        {

        }

        /**
             * @brief KeyAction constructor
             * @param title
             * @param defKey
             */
        KeyAction(const sf::String &title, sf::Keyboard::Key defKey):
            actualKey(defKey),
            title(title),
            defaultKey(defKey)
        {
        }

        /**
     * @brief actualKey the key as set by the user
     */
        sf::Keyboard::Key actualKey;

        /**
     * @brief title the title of the action
     */
        const sf::String title;

        /**
     * @brief defaultKey the default key
     */
        const sf::Keyboard::Key defaultKey;
    };

    /**
     * @brief initKeyMap inits the map containing the name of each keys
     */
    void initKeyMap();

    /**
     * @brief initKeyAction inits the map containing the data
     * for each actions
     */
    void initKeyAction();

    /**
     * @brief m_keyActions the action data
     * for each action type
     */
    std::unordered_map<KEY_ACTION, KeyAction, EnumClassHash> m_keyActions;

    /**
     * @brief m_keyMap the name of each key
     */
    std::unordered_map<sf::Keyboard::Key, std::string, EnumClassHash> m_keyMap;
};


}
