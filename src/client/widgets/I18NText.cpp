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
 * File:   I18NText.cpp
 * Author: azarias
 *
 * Created on 5/7/2018
 */
#include "I18NText.hpp"
#include "src/client/Translator.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ResourcesManager.hpp"

namespace mp {



I18NText::I18NText(Translator &translator, const std::string &translationName, int fontSize):
    sf::Text(translator.translate(translationName), pr::resourceManager().getFont()),
    m_translator(translator),
    m_translation(translationName)
{
    m_translator.translationChangedSignal.add([this](){
        setString(m_translator.translate(m_translation));
    });
    setCharacterSize(fontSize);
}

int I18NText::width()
{
    return getGlobalBounds().width;
}

int I18NText::height()
{
    return getGlobalBounds().height;
}

}
