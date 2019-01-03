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
 * File:   KeyOptions.cpp
 * Author: azarias
 *
 * Created on 3/11/2017
 */

#include <qglobal.h>
#include "KeyBindingState.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/Provider.hpp"
#include "src/client/Translator.hpp"
#include "src/client/widgets/Dialog.hpp"
#include "src/client/StateMachine.hpp"
#include "src/client/widgets/DialogManager.hpp"
#include "src/common/Game.hpp"

namespace mp {

KeyBindingState::KeyBindingState():
    m_menu()
{
    initKeyMap();

    const float startX = SF_CENTER_X;
    int startY = 100;
    startY += m_menu.addCenteredLabel("key_bindings", startX, startY, 70)->height() + 50;


    const float xSide = SF_ARENA_WIDTH / 4.f;
    for(auto ka : Input::allActions){
        Button &b = m_menu.addButton(actionToString(ka) ,xSide, startY, actionIcon(ka));
        startY += b.getHeight() + 10;
        m_actions.emplace_back(std::make_unique<ActionsButton>(&b, ka));
        auto *action = m_actions.back().get();
        b.clickedSignal.add([this, action](){
            buttonClicked(action);
        });
    }

    startY += 150.f;
    Button& resetbtn = m_menu.addButton("reset", startX, startY, Assets::IconAtlas::returnIcon);
    startY += resetbtn.getHeight();
    resetbtn.clickedSignal.add([this](){resetKeys();});


    m_menu.addButton("back", startX, startY + 10, Assets::IconAtlas::exitLeftIcon)
            .clickedSignal
            .add([](){
                pr::stateMachine().slideTo(cc::OPTIONS, SlideData::GO_LEFT);
            });

    m_menu.normalizeButtons();
    pr::translator().translationChangedSignal.add([this](){m_menu.normalizeButtons();});
}

KeyBindingState::~KeyBindingState()
{
}

std::vector<sf::String> KeyBindingState::actionToString(Input::I_AXIS_DIRECTION dir)
{
    sf::Keyboard::Key k = pr::game().input().getAxisKey(dir);
    sf::String kStr = keyToString(k);
    switch (dir) {
    case Input::Y_AXIS_1_UP:return {"Up", " P1 : ", kStr};
    case Input::Y_AXIS_1_DOWN: return {"Down", " P1 : ", kStr};
    case Input::Y_AXIS_2_UP: return {"Up", " P2 : ", kStr};
    case Input::Y_AXIS_2_DOWN: return {"Down", " P2 : ", kStr};
    }
    return {};
}

void KeyBindingState::resetKeys()
{
    pr::game().input().resetBindings();
    for(auto &it : m_actions)
        it->button->setText(actionToString(it->action));

}

void KeyBindingState::render(Renderer &renderer) const
{
    m_menu.render(renderer);
}

void KeyBindingState::handleEvent(const sf::Event &ev)
{
    if(pr::dialogManager().isActiveDialog(m_messageDialogId)){
        if(ev.type == sf::Event::KeyPressed && m_waitingAction){
            pr::game().input().setAxisButton(m_waitingAction->action, ev.key.code);
            std::vector<sf::String> nwBtnTitle = actionToString(m_waitingAction->action);
            m_waitingAction->button->setText(nwBtnTitle);
            m_waitingAction = nullptr;
            pr::dialogManager().hideDialog(m_messageDialogId);
        }
    }else{
        if(ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape){
            pr::stateMachine().slideTo(cc::OPTIONS, SlideData::GO_LEFT);
        }else{
            m_menu.handleEvent(ev);
        }
    }
}

const Assets::IconAtlas::Holder &KeyBindingState::actionIcon(int action) const
{
    switch (action) {
    case Input::I_AXIS_DIRECTION::Y_AXIS_1_DOWN:
    case Input::I_AXIS_DIRECTION::Y_AXIS_2_DOWN:
        return Assets::IconAtlas::arrowDownIcon;
    case Input::I_AXIS_DIRECTION::Y_AXIS_1_UP:
    case Input::I_AXIS_DIRECTION::Y_AXIS_2_UP:
        return Assets::IconAtlas::arrowUpIcon;
    default: return Assets::IconAtlas::crossIcon;
    }
}

void KeyBindingState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

void KeyBindingState::cancelDialog()
{
    pr::dialogManager().hideDialog(m_messageDialogId);
    m_waitingAction = nullptr;
    m_messageDialogId = 0;
}


void KeyBindingState::buttonClicked(ActionsButton *ab)
{
    m_waitingAction = ab;
    DialogMessage &dm = pr::dialogManager().message("change_key","press_key");
    m_messageDialogId = dm.id();
    auto cancel = [this](){cancelDialog();};
    dm.okClickedSignal.add(cancel);
    dm.closeSignal.add(cancel);
}

sf::String KeyBindingState::keyToString(sf::Keyboard::Key k) const
{
    auto found = m_keyMap.find(k);
    return found == m_keyMap.end() ? "" : found->second;
}

void KeyBindingState::initKeyMap()
{
#define MAP_KEY(key_id) m_keyMap[sf::Keyboard::key_id] = #key_id

    MAP_KEY(Unknown);
    MAP_KEY(A);
    MAP_KEY(B);
    MAP_KEY(C);
    MAP_KEY(D);
    MAP_KEY(E);
    MAP_KEY(F);
    MAP_KEY(G);
    MAP_KEY(H);
    MAP_KEY(I);
    MAP_KEY(J);
    MAP_KEY(K);
    MAP_KEY(L);
    MAP_KEY(M);
    MAP_KEY(N);
    MAP_KEY(O);
    MAP_KEY(P);
    MAP_KEY(Q);
    MAP_KEY(R);
    MAP_KEY(S);
    MAP_KEY(T);
    MAP_KEY(U);
    MAP_KEY(V);
    MAP_KEY(W);
    MAP_KEY(X);
    MAP_KEY(Y);
    MAP_KEY(Z);
    MAP_KEY(Num0);
    MAP_KEY(Num1);
    MAP_KEY(Num2);
    MAP_KEY(Num3);
    MAP_KEY(Num4);
    MAP_KEY(Num5);
    MAP_KEY(Num6);
    MAP_KEY(Num7);
    MAP_KEY(Num8);
    MAP_KEY(Num9);
    MAP_KEY(LControl);
    MAP_KEY(LShift);
    MAP_KEY(LAlt);
    MAP_KEY(LSystem);
    MAP_KEY(RControl);
    MAP_KEY(RShift);
    MAP_KEY(RAlt);
    MAP_KEY(RSystem);
    MAP_KEY(Menu);
    MAP_KEY(LBracket);
    MAP_KEY(RBracket);
    MAP_KEY(SemiColon);
    MAP_KEY(Comma);
    MAP_KEY(Period);
    MAP_KEY(Quote);
    MAP_KEY(Slash);
    MAP_KEY(BackSlash);
    MAP_KEY(Tilde);
    MAP_KEY(Equal);
    MAP_KEY(Dash);
    MAP_KEY(Space);
    MAP_KEY(Return);
    MAP_KEY(BackSpace);
    MAP_KEY(Tab);
    MAP_KEY(PageUp);
    MAP_KEY(PageDown);
    MAP_KEY(End);
    MAP_KEY(Home);
    MAP_KEY(Insert);
    MAP_KEY(Delete);
    MAP_KEY(Add);
    MAP_KEY(Subtract);
    MAP_KEY(Multiply);
    MAP_KEY(Divide);
    MAP_KEY(Left);
    MAP_KEY(Right);
    MAP_KEY(Up);
    MAP_KEY(Down);
    MAP_KEY(Numpad0);
    MAP_KEY(Numpad1);
    MAP_KEY(Numpad2);
    MAP_KEY(Numpad3);
    MAP_KEY(Numpad4);
    MAP_KEY(Numpad5);
    MAP_KEY(Numpad6);
    MAP_KEY(Numpad7);
    MAP_KEY(Numpad8);
    MAP_KEY(Numpad9);
    MAP_KEY(F1);
    MAP_KEY(F2);
    MAP_KEY(F3);
    MAP_KEY(F4);
    MAP_KEY(F5);
    MAP_KEY(F6);
    MAP_KEY(F7);
    MAP_KEY(F8);
    MAP_KEY(F9);
    MAP_KEY(F10);
    MAP_KEY(F11);
    MAP_KEY(F12);
    MAP_KEY(F13);
    MAP_KEY(F14);
    MAP_KEY(F15);
    MAP_KEY(Pause);

#undef MAP_KEY
}



}
