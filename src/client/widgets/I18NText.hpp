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
 * File:   I18NText.hpp
 * Author: azarias
 *
 * Created on 5/7/2018
 */
#pragma once

#include <SFML/Graphics/Text.hpp>
#include <vector>
#include "src/common/Signal.hpp"

namespace mp {
class Translator;

/**
 * @brief The I18NText class used to create a text widget
 * that will automatically translates when the user changes
 * the settings
 */
class I18NText : public sf::Text
{
public:
    /**
     * @brief I18NText first constructor : with a vector of string, the text will try
     * to translate each string of the vector and concatanate the results
     * @param translator a reference to the translator
     * @param translations the vector of all the strings to try to translate
     * @param fontSize the size of the text's font
     */
    I18NText(Translator &translator, const std::vector<sf::String> &translations, unsigned int fontSize);

    /**
     * @brief I18NText second constructor: just takes a string and tries to translate it
     * @param translator reference to the translator
     * @param translationName the string to try to translate
     * @param fontSize the font size
     */
    I18NText(Translator &translator, const sf::String &translationName, unsigned int fontSize = 30);

    /**
     * @brief operator += appends the given string to the existing list, will try to translate the
     * added string
     * @param add the string to add
     * @return itself
     */
    I18NText &operator+=(const sf::String &add);

    virtual ~I18NText();

    /**
     * @brief width the width of this text
     * @return
     */
    float width();

    /**
     * @brief height
     * @return  the height of this text
     */
    float height();

    /**
     * @brief setString removes the current string and changes it with the given string
     * @param str the new string
     */
    void setString(const sf::String &str);

    /**
     * @brief setString changes the current string with the given one
     * @param str the new string
     */
    void setString(const std::vector<sf::String> &str);

private:
    /**
     * @brief updateString update the position of the string,
     * and tries to translate each substring it contains
     */
    void updateString();

    /**
     * @brief m_translator keep a reference to the translator,
     * to use it when a translation is needed
     */
    Translator &m_translator;

    /**
     * @brief m_translations the whole string in itself
     */
    std::vector<sf::String> m_translations;

    /**
      * function called whenever the translation is changing
    */
    std::function<void()> m_erase = [this](){updateString();};

    /**
     * @brief m_listenerId keep the id of the listener,
     * to be able to remove it when the text is destroyed
     * (in the dialogs for exemple)
     */
    std::string m_listenerId;
};


}
