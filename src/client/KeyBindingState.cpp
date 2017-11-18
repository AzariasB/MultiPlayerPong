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
 * File:   KeyOptions.cpp
 * Author: azarias
 *
 * Created on 3/11/2017
 */
#include <iostream>
#include "KeyBindingState.hpp"
#include "ClientApp.hpp"
#include "Provider.hpp"


KeyBindingState::KeyBindingState():
    m_messageDialog(Dialog::message("","Press a key")),
    m_menu()
{
    int startX = 0;
    int startY = 0;
    startY += m_menu.addLabel("Key bindings",startX, startY)->getGlobalBounds().height + 10;


    for(KeyBinding::KEY_ACTION ka : KeyBinding::allActions){
        std::string btnTitle = pr::keyBinding().toString(ka);
        Button *b = m_menu.addButton( btnTitle ,startX, startY).get();
        startY += b->getHeight();
        m_actions.emplace_back(std::make_unique<ActionsButton>(b, ka));
        pr::connect(
                    b->clickedEvent,
                    &KeyBindingState::buttonClicked,
                    this,
                    m_actions.back().get()
                    );
    }

    sf::Uint64 resetClicked  = m_menu.addButton("Reset", startX, startY)->clickedEvent;
    pr::connect(resetClicked, &KeyBindingState::resetKeys, this);


    sf::Uint64 backClicked = m_menu.addButton("Back", startX, ARENA_HEIGHT - 50)->clickedEvent;
    pr::connect(backClicked, &StateMachine::setCurrentState, &pr::stateMachine(), (int)STATE_TYPE::OPTIONS);

    m_messageDialog->setOkButtonTitle("Cancel");
    pr::connect(m_messageDialog->cancelEvent, &KeyBindingState::cancelDialog, this);
    pr::connect(m_messageDialog->okEvent, &KeyBindingState::cancelDialog, this);
}

KeyBindingState::~KeyBindingState()
{
    delete m_messageDialog;
}

void KeyBindingState::resetKeys()
{
    pr::keyBinding().resetBindings();
    for(auto &it : m_actions)
        it->button->setText(pr::keyBinding().toString(it->action));
}

void KeyBindingState::draw(Renderer &renderer) const
{
    renderer.render(m_menu);
    renderer.render(*m_messageDialog);
}

void KeyBindingState::handleEvent(const sf::Event &ev)
{
    if(m_messageDialog->isVisible()){
        if(ev.type == sf::Event::KeyPressed && m_waitingAction){
            pr::keyBinding().setKeyAction(m_waitingAction->action, ev.key.code);
            std::string nwBtnTitle = pr::keyBinding().toString(m_waitingAction->action);
            m_waitingAction->button->setText(nwBtnTitle);
            m_waitingAction = 0;
            m_messageDialog->hide();
        }else{
            m_messageDialog->handleEvent(ev);
        }
    }else{
        m_menu.handleEvent(ev);
    }
}

void KeyBindingState::onEnter(BaseStateData *data)
{

}

void KeyBindingState::onLeave()
{

}

void KeyBindingState::update(const sf::Time &elapsed)
{

}

void KeyBindingState::cancelDialog()
{
    m_waitingAction = 0;
    m_messageDialog->hide();
}


void KeyBindingState::buttonClicked(ActionsButton *ab)
{
    m_waitingAction = ab;
    m_messageDialog->show();
}
