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
#include "src/client/Assets.hpp"

namespace mp {

// DIALOG BEGIN
Dialog::Dialog(const sf::Uint64 id, const sf::String &title):
    m_menu(),
    m_title(pr::translator(), title, 50),
    m_background(sf::Vector2f(SF_DIALOG_WIDTH, SF_DIALOG_HEIGHT)),
    m_id(id),
    closeSignal()
{
    m_title.setPosition(originX + 5,originY + 5);
    auto &closeBtn = m_menu.addButton("", originX + SF_DIALOG_WIDTH - SF_BUTTON_MARGIN, originY + SF_BUTTON_MARGIN, Assets::IconAtlas::crossIcon);
    closeBtn.setOrigin(closeBtn.getWidth(), 0);
    closeBtn.clickedSignal
            .add(closeSignal);

    m_background.setPosition(originX, originY);
    m_background.setFillColor(cc::Colors::dialogBackgroundColor);
    m_background.setOutlineColor(cc::Colors::dialogOutlineColor);
    m_background.setOutlineThickness(5);
    m_state = DIALOG_HIDDEN;
}

Dialog::~Dialog()
{
}

const sf::Uint64 &Dialog::id() const
{
    return m_id;
}

bool Dialog::update(const sf::Time &elapsed)
{
    if(m_state != DIALOG_HIDDEN){
        m_yTransition.step(elapsed);
        m_yPosition = m_yTransition.get();

        if(m_yTransition.progress() == 1.f){
            if(m_state == DIALOG_APPEARING)
                m_state = DIALOG_VISIBLE;
            else if(m_state == DIALOG_HIDING){
                m_state = DIALOG_HIDDEN;
                return false;
            }

        }
    }
    m_menu.update(elapsed);
    return Widget::update(elapsed);
}

void Dialog::render(Renderer &renderer) const
{
    renderer
            .draw(m_background)
            .draw(m_title)
            .render(m_menu);
}

void Dialog::beforeDraw(Renderer &renderer) const
{
    renderer.push()
            .translate(sf::Vector2f(0, m_yPosition));
}

void Dialog::afterDraw(Renderer &renderer) const
{
    renderer.pop();
}

bool Dialog::handleEvent(const sf::Event &ev)
{
    if(!isVisible())return false;
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        closeSignal.trigger();
        return true;
    }else{
        return m_menu.handleEvent(ev);
    }
}

void Dialog::setTitle(const sf::String &str)
{
    m_title.setString(str);
}

void Dialog::show(bool animate)
{
    if(m_state == DIALOG_APPEARING || m_state == DIALOG_VISIBLE)return;
    m_state = DIALOG_APPEARING;

    if(animate){
        m_yTransition = twin::makeTwin(-(float)SF_ARENA_HEIGHT, 0.f, sf::milliseconds(500), twin::backInOut);
    }else{
        m_yPosition = 0;
    }
}

void Dialog::hide()
{
    if(m_state == DIALOG_HIDING || m_state == DIALOG_HIDDEN)return;

    m_state = DIALOG_HIDING;

    m_yTransition = twin::makeTwin(0.f, -(float)SF_ARENA_HEIGHT, sf::milliseconds(500), twin::backInOut);
}

Menu &Dialog::menu()
{
    return m_menu;
}

Dialog::DIALOG_STATE Dialog::state() const
{
    return m_state;
}

// DIALOG END

//INPUT DIALOG

DialogInput::DialogInput(const sf::Uint64 &id, const sf::String &title, const sf::String &question):
    Dialog(id, title),
    m_questionText(pr::translator(), question),
    m_input(sf::Vector2f(originX + 30, originY + (SF_DIALOG_HEIGHT / 2.f) )),
    canceledSignal(),
    confirmedSignal()
{
   auto &confirmBtn = menu().addButton("confirm", originX + 4, originY + SF_DIALOG_HEIGHT - SF_BUTTON_MARGIN, Assets::IconAtlas::checkmarkIcon);
   confirmBtn.setOrigin(0, confirmBtn.getHeight());
   confirmBtn.clickedSignal
            .add([this](){
                confirmedSignal.trigger(m_input.getText());
            });

    auto &cancelBtn = menu().addButton("cancel", originX + SF_DIALOG_WIDTH, originY + SF_DIALOG_HEIGHT - SF_BUTTON_MARGIN, Assets::IconAtlas::crossIcon);
    cancelBtn.setOrigin(cancelBtn.getWidth(), cancelBtn.getHeight());
    cancelBtn.clickedSignal
            .add(canceledSignal);

    menu().changeSelection(1);

    m_questionText.setPosition(originX + 10, originY + SF_DIALOG_HEIGHT/4.f);

}

DialogInput::~DialogInput()
{
}

bool DialogInput::update(const sf::Time &elapsed)
{
    m_input.update(elapsed);
    return Dialog::update(elapsed);
}

void DialogInput::render(Renderer &renderer) const
{
    beforeDraw(renderer);
    Dialog::render(renderer);
    renderer.draw(m_questionText)
            .render(m_input);
    afterDraw(renderer);
}

bool DialogInput::handleEvent(const sf::Event &ev)
{
    if(!isVisible()) return false;
    return m_input.handleEvent(ev) || Dialog::handleEvent(ev);
}

// INPUT END

// QUESTION DIALOG


DialogQuestion::DialogQuestion(const sf::Uint64 &id, const sf::String &title, const sf::String &question):
    Dialog(id, title),
    m_questionText(pr::translator(), question, 40),
    yesClickedSignal(),
    noClickedSignal()
{
    m_questionText.setPosition(originX + 20, originY + (SF_DIALOG_HEIGHT  / 2.f));


    auto &yesBtn = menu().addButton("yes", originX + SF_BUTTON_MARGIN, originY + SF_DIALOG_HEIGHT - SF_BUTTON_MARGIN, Assets::IconAtlas::checkmarkIcon);
    yesBtn.setOrigin(0, yesBtn.getHeight());
    yesBtn.clickedSignal.add(yesClickedSignal);

    menu().changeSelection(1);

    auto &noBtn = menu().addButton("no", originX + SF_DIALOG_WIDTH - SF_BUTTON_MARGIN, originY + SF_DIALOG_HEIGHT - SF_BUTTON_MARGIN, Assets::IconAtlas::crossIcon);
    noBtn.setOrigin(noBtn.getWidth(), noBtn.getHeight());
    noBtn.clickedSignal.add(noClickedSignal);
}

DialogQuestion::~DialogQuestion()
{
}

const sf::String &DialogQuestion::getQuestion() const
{
    return m_questionText.getString();
}

void DialogQuestion::setQuestion(const sf::String &nwQuestion)
{
    m_questionText.setString(nwQuestion);
}

void DialogQuestion::render(Renderer &renderer) const
{
    beforeDraw(renderer);

    Dialog::render(renderer);

    afterDraw(renderer.draw(m_questionText));
}

// QUESTION END


// MESSAGE BEGIN

DialogMessage::DialogMessage(const sf::Uint64 &id, const sf::String &title, const sf::String &message):
    Dialog(id, title),
    m_messageText(pr::translator(), message, 40),
    okClickedSignal()
{
    auto &okBtn = menu().addButton("ok", originX + SF_BUTTON_MARGIN, originY + SF_DIALOG_HEIGHT - SF_BUTTON_MARGIN, Assets::IconAtlas::checkmarkIcon);
    okBtn.setOrigin(0, okBtn.getHeight());
    okBtn.clickedSignal
            .add(okClickedSignal);

    menu().changeSelection(1);

    m_messageText.setPosition(originX + 10, originY + (SF_DIALOG_HEIGHT / 2.f));

}

DialogMessage::~DialogMessage()
{
}

sf::String DialogMessage::getMessage() const
{
    return m_messageText.getString().toAnsiString();
}

void DialogMessage::setMessage(const sf::String &nwMessage)
{
    m_messageText.setString(nwMessage);
}

void DialogMessage::render(Renderer &renderer) const
{
    beforeDraw(renderer);

    Dialog::render(renderer);

    afterDraw(renderer.draw(m_messageText));
}


// MESSAGE END
}
