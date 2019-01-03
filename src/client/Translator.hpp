/*
 * The MIT License
 *
 * Copyright 2017-2019 azarias.
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
 * File:   Translator.hpp
 * Author: azarias
 *
 * Created on 5/7/2018
 */
#pragma once

#include "widgets/I18NText.hpp"
#include "Assets.hpp"
#include "src/common/Signal.hpp"

namespace mp {

/**
 * @brief The Translator class
 * Used to translate all the possible strings of the application
 * using the translation files found in the resources
 * Whenever the translation is changed by the user
 * a signal is emitted, so all the string of the application can be
 * updated
 */
class Translator
{
public:
    /**
     * @brief Translator
     * empty constructor
     */
    Translator();

    /**
     * @brief translate tries to translate the given string using its internal
     * dictionnary, if the translation fails (no equivalence found) the string
     * itself is returned
     * @param translationName the name of the translation to find (or a normal string if
     * there is no need for a translation)
     * @return the translated string of the original string
     */
    sf::String translate(const sf::String &translationName) const;

    /**
     * @brief setCurrentTranslation sets the current language for the application,
     * this will trigger the "translationChangedSignal"
     * @param trName the name of the translation
     */
    void setCurrentTranslation(const std::string &trName);

    /**
     * @brief make creates a translatable text, with the given translation name and
     * the given font size
     * @param translationName name of the translation (can also be a non-translatable string)
     * @param fontSize size of the font for the text to create
     * @return the text linked with this translator, so that when the language changes
     * the string updates if necessary
     */
    I18NText make(const sf::String &translationName, int fontSize = 30);

    /**
     * @brief make creates a translatable text, with the given translation strings and the given font
     * size
     * @param translations vector of string to translate
     * @param fontSize size of the font
     * @return the text linked with this translator, so that when the language changes,
     *  the string updates if necessary
     */
    I18NText make(const std::vector<sf::String> &translations, int fontSize = 30);

    /**
     * @brief currentTranslation accessor to the current translation name
     * @return string representing the current translation name
     */
    const std::string &currentTranslation() const;

private:
    /**
     * @brief m_currentTranslation short name of the current translation
     */
    std::string m_currentTranslation = "fr";

public:
    /**
     * @brief translationChangedSignal
     * signal that is triggered wheneverthe current translation
     * is changed
     */
    Signal<> translationChangedSignal;
};

}
