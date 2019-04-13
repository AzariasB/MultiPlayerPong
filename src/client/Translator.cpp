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
 * File:   Translator.cpp
 * Author: azarias
 *
 * Created on 5/7/2018
 */
#include "Translator.hpp"
#include "Provider.hpp"
#include <iostream>

namespace mp {

Translator::Translator(const std::string &currentTranslation):
    m_currentTranslation(currentTranslation)
{
    if(Assets::I18N::translations.find(currentTranslation) == Assets::I18N::translations.end()){
        m_currentTranslation = "en";
    }
}

sf::String Translator::translate(const sf::String &translationName) const
{
    if(translationName.isEmpty())return translationName;

    // std::wcout << translationName.toWideString() << "\n";
    const auto &tr = Assets::I18N::translations;
    const auto iterator = tr.find(m_currentTranslation);
    if( iterator == tr.end())return translationName;
    const auto &map = (*iterator).second;
    const auto &val = map.translation.find(translationName);
    if(val == map.translation.end())return translationName;
    return (*val).second;
}

const std::string &Translator::currentTranslation() const
{
    return m_currentTranslation;
}

void Translator::setCurrentTranslation(const std::string &trName)
{
    m_currentTranslation = trName;
    translationChangedSignal.trigger();
}

I18NText Translator::make(const sf::String &translationName, int fontSize)
{
    return I18NText(*this, translationName, fontSize);

}

I18NText Translator::make(const std::vector<sf::String> &translations, int fontSize)
{
    return I18NText(*this, translations, fontSize);
}

}
