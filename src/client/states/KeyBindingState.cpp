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
    startY += m_menu.addCenteredLabel("Key bindings", startX, startY, 70)->getGlobalBounds().height + 50;


    const int xSide = SF_ARENA_WIDTH / 4.f;
    for(KeyBinding::KEY_ACTION ka : KeyBinding::allActions){
        std::string btnTitle = pr::keyBinding().toString(ka);
        Button &b = m_menu.addButton(btnTitle ,xSide, startY, actionIcon(ka));
        startY += b.getHeight() + 10;
        m_actions.emplace_back(std::make_unique<ActionsButton>(&b, ka));
        auto action = m_actions.back().get();
        pr::connect(b.clickedEvent, [this, action](){buttonClicked(action);});
    }

    startY += 150.f;
    const Button& resetbtn= m_menu.addButton("Reset", startX, startY, Assets::IconAtlas::returnIcon);
    startY += resetbtn.getHeight();
    pr::connect(resetbtn.clickedEvent, [this](){resetKeys();});


    sf::Uint64 backClicked = m_menu.addButton("Back", startX, startY + 10, Assets::IconAtlas::exitLeftIcon).clickedEvent;
    pr::connect(backClicked, [](){pr::stateMachine().goToState(cc::OPTIONS, TransitionData::GO_LEFT);});

    m_menu.normalizeButtons();
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

void KeyBindingState::render(Renderer &renderer) const
{
    m_menu.render(renderer);
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
        if(ev.type == sf::Event::KeyReleased && ev.key.code == sf::Keyboard::Escape){
            pr::stateMachine().goToState(cc::OPTIONS, TransitionData::GO_LEFT);
        }else{
            m_menu.handleEvent(ev);
        }
    }
}

const Assets::IconAtlas::Holder &KeyBindingState::actionIcon(KeyBinding::KEY_ACTION action) const
{
    switch (action) {
    case KeyBinding::GO_DOWN: return Assets::IconAtlas::arrowDownIcon;
    case KeyBinding::GO_UP: return Assets::IconAtlas::arrowUpIcon;
    default: return Assets::IconAtlas::crossIcon;
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
    auto cancel = [this](){cancelDialog();};
    pr::connect(dm.okClickedEvent, cancel);// &KeyBindingState::cancelDialog, this);
    pr::connect(dm.closeEvent, cancel);
}


}
