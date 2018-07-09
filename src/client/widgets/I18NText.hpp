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

class I18NText : public sf::Text
{
public:
    I18NText(Translator &translator, const std::vector<sf::String> &translations, int fontSize);

    I18NText(Translator &translator, const sf::String &translationName, int fontSize = 30);

    I18NText &operator+=(const sf::String &add);

    int width();

    int height();

    void setString(const sf::String &str);

    void setString(const std::vector<sf::String> &str);

private:
    void updateString();

    Translator &m_translator;

    std::vector<sf::String> m_translations;
};


}
