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

#include "src/client/Renderer.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/ClientConf.hpp"



// DIALOG BEGIN
Dialog::Dialog(const sf::Uint64 id, const std::string &title):
    m_xButton("X"),
    m_title(sf::String(title), pr::resourceManager().getFont()),
    m_background(sf::Vector2f(SF_DIALOG_WIDTH, SF_DIALOG_HEIGHT)),
    m_id(id),
    closeEvent(pr::nextEventCode()),
    hiddenEvent(pr::nextEventCode())
{
    pr::connect(m_xButton.clickedEvent, &Dialog::closed, this);

    m_title.setPosition(originX + 5,originY + 5);

    m_xButton.setPosition(sf::Vector2f(
                              originX + SF_DIALOG_WIDTH - m_xButton.getWidth() - 5,
                              originY + 5
                              ));

    m_background.setPosition(originX, originY);
    m_background.setFillColor(cc::colors::dialogBackgroundColor);
    m_background.setOutlineColor(cc::colors::dialogOutlineColor);
    m_background.setOutlineThickness(5);
    m_state = DIALOG_HIDDEN;
}

const sf::Uint64 &Dialog::id() const
{
    return m_id;
}

void Dialog::closed()
{
    pr::trigger(closeEvent);
}

void Dialog::update(const sf::Time &elapsed)
{
    if(m_state != DIALOG_HIDDEN){
        m_yTransition.step(elapsed.asSeconds());
        m_yPosition = m_yTransition.get();

        if(m_yTransition.progress() == 1.f){
            if(m_state == DIALOG_APPEARING)
                m_state = DIALOG_VISIBLE;
            else if(m_state == DIALOG_HIDING){
                m_state = DIALOG_HIDDEN;
                pr::trigger(hiddenEvent);
            }

        }

        m_xButton.update(elapsed);
    }
}

void Dialog::draw(Renderer &renderer) const
{
    renderer.render(m_background);
    renderer.render(m_title);
    m_xButton.draw(renderer);
}

void Dialog::beforeDraw(Renderer &renderer) const
{
    renderer.push();
    renderer.translate(sf::Vector2f(0, m_yPosition));
}

void Dialog::afterDraw(Renderer &renderer) const
{
    renderer.pop();
}

void Dialog::handleEvent(const sf::Event &ev)
{
    if(!isVisible())return;
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        pr::trigger(closeEvent);
    }else{
        m_xButton.handleEvent(ev);
    }
}

void Dialog::setTitle(const std::string &str)
{
    m_title.setString(str);
}

void Dialog::show(bool animate)
{
    if(m_state == DIALOG_APPEARING || m_state == DIALOG_VISIBLE)return;
    m_state = DIALOG_APPEARING;

    if(animate){
        m_yTransition = twin::makeTwin(-(float)SF_ARENA_HEIGHT, 0.f, 0.5f, twin::backInOut);
    }else{
        m_yPosition = 0;
    }
}

void Dialog::hide(bool animate)
{
    if(m_state == DIALOG_HIDING || m_state == DIALOG_HIDDEN)return;

    m_state = DIALOG_HIDING;

    if(animate){
         m_yTransition = twin::makeTwin(0.f, -(float)SF_ARENA_HEIGHT, 0.5f, twin::backInOut);
    }else{
        m_state = DIALOG_HIDDEN;
    }
}

Dialog::DIALOG_STATE Dialog::state() const
{
    return m_state;
}

// DIALOG END

//INPUT DIALOG

DialogInput::DialogInput(const sf::Uint64 &id, const std::string &title, const std::string &question):
Dialog(id, title),
m_questionText(question, pr::resourceManager().getFont()),
m_input(sf::Vector2f(originX + 10, originY + SF_DIALOG_HEIGHT/2)),
m_confirmButton("Confirm",  originX + 10, originY + SF_DIALOG_HEIGHT - 50),
m_cancelButton("Cancel", originX + SF_DIALOG_WIDTH - 200, originY + SF_DIALOG_HEIGHT - 50),
cancelClickedEvent(pr::nextEventCode()),
confirmClickedEvent(pr::nextEventCode())
{
    m_questionText.setPosition(originX + 10, originY + SF_DIALOG_HEIGHT/4.f);

    pr::connect(m_confirmButton.clickedEvent, &DialogInput::confirmClicked, this);
    pr::connect(m_cancelButton.clickedEvent, &DialogInput::cancelClicked, this);
}


void DialogInput::confirmClicked()
{
    pr::trigger(confirmClickedEvent, m_input.getText());
}

void DialogInput::cancelClicked()
{
    pr::trigger(cancelClickedEvent);
}

void DialogInput::update(const sf::Time &elapsed)
{
    Dialog::update(elapsed);
    m_cancelButton.update(elapsed);
    m_confirmButton.update(elapsed);
    m_input.update(elapsed);
}

void DialogInput::draw(Renderer &renderer) const
{
    beforeDraw(renderer);

    Dialog::draw(renderer);
    m_cancelButton.draw(renderer);
    m_confirmButton.draw(renderer);
    m_input.draw(renderer);

    afterDraw(renderer);
}

void DialogInput::handleEvent(const sf::Event &ev)
{
    Dialog::handleEvent(ev);
    if(state() == DIALOG_VISIBLE && ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return){
        confirmClicked();
    }else{
        m_cancelButton.handleEvent(ev);
        m_confirmButton.handleEvent(ev);
        m_input.handleEvent(ev);
    }
}

// INPUT END

// QUESTION DIALOG


DialogQuestion::DialogQuestion(const sf::Uint64 &id, const std::string &title, const std::string &question):
Dialog(id, title),
m_questionText(question, pr::resourceManager().getFont()),
m_yesButton("Yes", originX + 10, originY + SF_DIALOG_HEIGHT - 50),
m_noButton("No", originX + SF_DIALOG_WIDTH - 200, originY + SF_DIALOG_HEIGHT - 50),
yesClickedEvent(pr::nextEventCode()),
noClickedEvent(pr::nextEventCode())
{
    m_questionText.setPosition(originX + 10, originY  +SF_DIALOG_HEIGHT/2.f);

    pr::connect(m_yesButton.clickedEvent, &DialogQuestion::yesClicked, this);
    pr::connect(m_noButton.clickedEvent, &DialogQuestion::noClicked, this);

}

const std::string &DialogQuestion::getQuestion() const
{
    return m_questionText.getString().toAnsiString();
}

void DialogQuestion::setQuestion(const std::string &nwQuestion)
{
    m_questionText.setString(nwQuestion);
}

void DialogQuestion::update(const sf::Time &elapsed)
{
    Dialog::update(elapsed);
    m_yesButton.update(elapsed);
    m_noButton.update(elapsed);
}

void DialogQuestion::draw(Renderer &renderer) const
{
    beforeDraw(renderer);

    Dialog::draw(renderer);
    m_yesButton.draw(renderer);
    m_noButton.draw(renderer);
    renderer.render(m_questionText);

    afterDraw(renderer);
}

void DialogQuestion::handleEvent(const sf::Event &ev)
{
    Dialog::handleEvent(ev);
    m_yesButton.handleEvent(ev);
    m_noButton.handleEvent(ev);
}

void DialogQuestion::yesClicked()
{
    pr::trigger(yesClickedEvent);
}

void DialogQuestion::noClicked()
{
    pr::trigger(noClickedEvent);
}

// QUESTION END


// MESSAGE BEGIN

DialogMessage::DialogMessage(const sf::Uint64 &id, const std::string &title, const std::string &message):
Dialog(id, title),
m_messageText(message, pr::resourceManager().getFont()),
m_okButton("Ok", originX + 10, originY + SF_DIALOG_HEIGHT - 50),
okClickedEvent(pr::nextEventCode())
{
    m_messageText.setPosition(originX + 10, originY + SF_DIALOG_HEIGHT / 2.f);

    pr::connect(m_okButton.clickedEvent, &DialogMessage::okClicked, this);
}

const std::string &DialogMessage::getMessage() const
{
    return m_messageText.getString().toAnsiString();
}

void DialogMessage::setMessage(const std::string &nwMessage)
{
    m_messageText.setString(nwMessage);
}

void DialogMessage::update(const sf::Time &elapsed)
{
    Dialog::update(elapsed);
    m_okButton.update(elapsed);
}

void DialogMessage::draw(Renderer &renderer) const
{
    beforeDraw(renderer);

    Dialog::draw(renderer);
    m_okButton.draw(renderer);
    renderer.render(m_messageText);

    afterDraw(renderer);
}

void DialogMessage::handleEvent(const sf::Event &ev)
{
    Dialog::handleEvent(ev);
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Return){
        okClicked();
    }else{
        m_okButton.handleEvent(ev);
    }
}

void DialogMessage::okClicked()
{
    pr::trigger(okClickedEvent);
}

// MESSAGE END
