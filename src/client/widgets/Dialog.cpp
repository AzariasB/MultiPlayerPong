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
Dialog::Dialog(const sf::Uint64 id, const std::string &title):
    m_menu(),
    m_title(sf::String(title), pr::resourceManager().getFont(), 50),
    m_background(sf::Vector2f(SF_DIALOG_WIDTH, SF_DIALOG_HEIGHT)),
    m_id(id),
    closeSignal(),
    hiddenSignal()
{
    m_title.setPosition(originX + 5,originY + 5);
    m_menu.addButton("", originX + SF_DIALOG_WIDTH - 15, originY, Assets::IconAtlas::crossIcon)
            .clickedSignal
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

void Dialog::update(const sf::Time &elapsed)
{
    if(m_state != DIALOG_HIDDEN){
        m_yTransition.step(elapsed);
        m_yPosition = m_yTransition.get();

        if(m_yTransition.progress() == 1.f){
            if(m_state == DIALOG_APPEARING)
                m_state = DIALOG_VISIBLE;
            else if(m_state == DIALOG_HIDING){
                m_state = DIALOG_HIDDEN;
                hiddenSignal.trigger();
                return;
            }

        }
    }
    m_menu.update(elapsed);
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

void Dialog::handleEvent(const sf::Event &ev)
{
    if(!isVisible())return;
    if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
        closeSignal.trigger();
    }else{
        m_menu.handleEvent(ev);
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

DialogInput::DialogInput(const sf::Uint64 &id, const std::string &title, const std::string &question):
    Dialog(id, title),
    m_questionText(question, pr::resourceManager().getFont()),
    m_input(sf::Vector2f(originX + 30, originY + SF_DIALOG_HEIGHT/2)),
    canceledSignal(),
    confirmedSignal()
{
    menu().
            addButton("confirm", originX + 102, originY + SF_DIALOG_HEIGHT - 65, Assets::IconAtlas::checkmarkIcon)
            .clickedSignal
            .add([this](){
                confirmedSignal.trigger(m_input.getText());
            });

    menu()
            .addButton("cancel", originX + SF_DIALOG_WIDTH - 90, originY + SF_DIALOG_HEIGHT - 62, Assets::IconAtlas::crossIcon)
            .clickedSignal
            .add(canceledSignal);

    menu().changeSelection(1);

    m_questionText.setPosition(originX + 10, originY + SF_DIALOG_HEIGHT/4.f);

}

DialogInput::~DialogInput()
{
}

void DialogInput::update(const sf::Time &elapsed)
{
    m_input.update(elapsed);
    Dialog::update(elapsed);
}

void DialogInput::render(Renderer &renderer) const
{
    beforeDraw(renderer);
    Dialog::render(renderer);
    afterDraw(renderer.render(m_input));
}

void DialogInput::handleEvent(const sf::Event &ev)
{
    Dialog::handleEvent(ev);
    m_input.handleEvent(ev);
}

// INPUT END

// QUESTION DIALOG


DialogQuestion::DialogQuestion(const sf::Uint64 &id, const std::string &title, const std::string &question):
    Dialog(id, title),
    m_questionText(question, pr::resourceManager().getFont(), 40),
    yesClickedSignal(),
    noClickedSignal()
{
    m_questionText.setPosition(originX + 20, originY + SF_DIALOG_HEIGHT / 2.f);


    menu()
            .addButton("yes", originX + 70, originY + SF_DIALOG_HEIGHT - 72, Assets::IconAtlas::checkmarkIcon)
            .clickedSignal
            .add(yesClickedSignal);

    menu().changeSelection(1);

    menu()
            .addButton("no", originX + SF_DIALOG_WIDTH - 60, originY + SF_DIALOG_HEIGHT - 63, Assets::IconAtlas::crossIcon)
            .clickedSignal
            .add(noClickedSignal);
}

DialogQuestion::~DialogQuestion()
{
}

const std::string &DialogQuestion::getQuestion() const
{
    return m_questionText.getString().toAnsiString();
}

void DialogQuestion::setQuestion(const std::string &nwQuestion)
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

DialogMessage::DialogMessage(const sf::Uint64 &id, const std::string &title, const std::string &message):
    Dialog(id, title),
    m_messageText(message, pr::resourceManager().getFont(), 40),
    okClickedSignal()
{
    menu()
            .addButton("ok", originX + 65, originY + SF_DIALOG_HEIGHT - 65, Assets::IconAtlas::checkmarkIcon)
            .clickedSignal
            .add(okClickedSignal);

    menu().changeSelection(1);

    m_messageText.setPosition(originX + 10, originY + SF_DIALOG_HEIGHT / 2.f);

}

DialogMessage::~DialogMessage()
{
}

std::string DialogMessage::getMessage() const
{
    return m_messageText.getString().toAnsiString();
}

void DialogMessage::setMessage(const std::string &nwMessage)
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
