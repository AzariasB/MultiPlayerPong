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
 * File:   Dialog.cpp
 * Author: azarias
 *
 * Created on 23/10/2017
 */
#include "Dialog.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourcesManager.hpp"
#include "Provider.hpp"

Dialog *Dialog::input(const std::string &title)
{
    return new Dialog(title, "", DIALOG_TYPE::INPUT);
}

Dialog* Dialog::message(const std::string &message, const std::string &title)
{
    return new Dialog(title, message, DIALOG_TYPE::MESSAGE);
}

Dialog::Dialog(const std::string &title, const std::string &message, DIALOG_TYPE type):
    m_okButton("Confirm"),
    m_cancelButton("Cancel"),
    m_xButton("X"),
    m_input(),
    m_title(sf::String(title), pr::resourceManager().getFont()),
    m_message("",pr::resourceManager().getFont()),
    m_type(type),
    okEvent(pr::nextEventCode()),
    cancelEvent(pr::nextEventCode())
{
    pr::connect(m_okButton.clickedEvent, &Dialog::okButtonClicked, this);
    pr::connect(m_cancelButton.clickedEvent, &Dialog::cancelButtonClicked, this);
    pr::connect(m_xButton.clickedEvent, &Dialog::cancelButtonClicked, this);

    m_title.setPosition(originX + 1,originY +1);
    m_input.setText(message);
    m_input.setPosition(sf::Vector2f(
                            originX + 10,
                            originY + SF_DIALOG_HEIGHT/2
                            ));
    m_message.setPosition(sf::Vector2f(
                              originX,
                              originY + SF_DIALOG_HEIGHT/2
                              ));

    m_okButton.setPosition(sf::Vector2f(
                               originX,
                               originY + SF_DIALOG_HEIGHT - m_okButton.getHeight()
                               ));
    m_cancelButton.setPosition(sf::Vector2f(
                                   originX + SF_DIALOG_WIDTH - m_cancelButton.getWidth(),
                                   originY + SF_DIALOG_HEIGHT - m_cancelButton.getHeight()
                                   ));

    m_xButton.setPosition(sf::Vector2f(
                              originX + SF_DIALOG_WIDTH - m_xButton.getWidth(),
                              originY
                              ));

}

void Dialog::cancelButtonClicked()
{
    pr::trigger(cancelEvent);
}

void Dialog::okButtonClicked()
{
    pr::trigger(okEvent);
}

const std::string &Dialog::getResult() const
{
    return m_input.getText();
}

void Dialog::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!m_isVisible)return;
    sf::RectangleShape rect(sf::Vector2f(SF_DIALOG_WIDTH,SF_DIALOG_HEIGHT));
    rect.setPosition(originX,originY);
    rect.setOutlineColor(sf::Color::White);
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(5);

    target.draw(rect, states);
    target.draw(m_title, states);
    if(m_type == DIALOG_TYPE::INPUT){
        target.draw(m_input, states);
        target.draw(m_cancelButton, states);
    }else{
        target.draw(m_message, states);
    }
    target.draw(m_okButton, states);
    target.draw(m_xButton, states);
}

void Dialog::handleEvent(const sf::Event &ev)
{
    if(!m_isVisible)return;
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::trigger(cancelEvent);
    }else if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return){
        pr::trigger(okEvent);
    }else{
        m_okButton.handleEvent(ev);
        if(m_type == DIALOG_TYPE::INPUT){
            m_cancelButton.handleEvent(ev);
            m_input.handleEvent(ev);
        }
        m_xButton.handleEvent(ev);
    }
}

void Dialog::setMessage(const std::string &str)
{
    m_message.setString(str);
}

void Dialog::setTitle(const std::string &str)
{
    m_title.setString(str);
}

void Dialog::setOkButtonTitle(const std::string &str)
{
    m_okButton.setText(str);
}

void Dialog::show()
{
    m_isVisible =  true;
}

void Dialog::hide()
{
    m_isVisible = false;
}
