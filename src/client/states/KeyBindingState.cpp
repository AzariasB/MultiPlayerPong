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
 * File:   KeyOptions.cpp
 * Author: azarias
 *
 * Created on 3/11/2017
 */

#include <qglobal.h>
#include "KeyBindingState.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/Provider.hpp"
#include "src/client/widgets/Dialog.hpp"
#include "src/client/StateMachine.hpp"
#include "src/client/widgets/DialogManager.hpp"

namespace mp {

KeyBindingState::KeyBindingState():
    m_menu()
{
    const int startX = SF_ARENA_WIDTH/2.f;
    int startY = 100;
    startY += m_menu.addCenteredLabel("Key bindings", startX, startY)->getGlobalBounds().height + 20;


    const int xSide = SF_ARENA_WIDTH / 4.f;
    for(KeyBinding::KEY_ACTION ka : KeyBinding::allActions){
        std::string btnTitle = pr::keyBinding().toString(ka);
        Button *b = m_menu.addButton(btnTitle ,xSide, startY).get();
        startY += b->getHeight();
        m_actions.emplace_back(std::make_unique<ActionsButton>(b, ka));
        pr::connect(
                    b->clickedEvent,
                    &KeyBindingState::buttonClicked,
                    this,
                    m_actions.back().get()
                    );
    }

    startY += 50.f;
    sf::Uint64 resetClicked  = m_menu.addCenteredButton("Reset", startX, startY)->clickedEvent;
    pr::connect(resetClicked, &KeyBindingState::resetKeys, this);


    sf::Uint64 backClicked = m_menu.addCenteredButton("Back", startX, startY + 100)->clickedEvent;
    pr::connect(backClicked, &StateMachine::goToState, &pr::stateMachine() , std::make_pair((int)cc::OPTIONS, TransitionData::GO_LEFT) );
}

KeyBindingState::~KeyBindingState()
{
}

void KeyBindingState::resetKeys()
{
    pr::keyBinding().resetBindings();
    for(auto &it : m_actions)
        it->button->setText(pr::keyBinding().toString(it->action));
}

void KeyBindingState::draw(Renderer &renderer) const
{
    m_menu.draw(renderer);
}

void KeyBindingState::handleEvent(const sf::Event &ev)
{
    if(pr::dialogManager().isActiveDialog(m_messageDialogId)){
        if(ev.type == sf::Event::KeyPressed && m_waitingAction){
            pr::keyBinding().setKeyAction(m_waitingAction->action, ev.key.code);
            std::string nwBtnTitle = pr::keyBinding().toString(m_waitingAction->action);
            m_waitingAction->button->setText(nwBtnTitle);
            m_waitingAction = 0;
            pr::dialogManager().hideDialog(m_messageDialogId);
        }
    }else{
        m_menu.handleEvent(ev);
    }
}

void KeyBindingState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void KeyBindingState::cancelDialog()
{
    m_waitingAction = 0;
    m_messageDialogId = 0;
}


void KeyBindingState::buttonClicked(ActionsButton *ab)
{
    m_waitingAction = ab;
    DialogMessage &dm = pr::dialogManager().message("Change key binding","Press a key");
    m_messageDialogId = dm.id();
    pr::connect(dm.okClickedEvent, &KeyBindingState::cancelDialog, this);
    pr::connect(dm.closeEvent, &KeyBindingState::cancelDialog, this);
}


}
