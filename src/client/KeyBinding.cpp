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
 * File:   KeyBinding.cpp
 * Author: azarias
 *
 * Created on 2/11/2017
 */
#include "KeyBinding.hpp"

const std::array<KeyBinding::KEY_ACTION, 2> KeyBinding::allActions = {KeyBinding::GO_UP, KeyBinding::GO_DOWN};

KeyBinding::KeyBinding()
{
    initKeyMap();
    initKeyAction();
}

sf::Event KeyBinding::toGameEvent(const sf::Event &ev) const
{
    if(!(ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased  ))return ev;

    sf::Event copy = ev;
    for(auto const &it : m_keyActions){
	if(it.second.actualKey == copy.key.code){
	    copy.key.code = it.second.defaultKey;
	    break;
	}
    }
    return copy;
}

std::string KeyBinding::toString(KEY_ACTION action)
{
    if(m_keyActions.find(action) == m_keyActions.end()) return "";
    const KeyAction &ka = m_keyActions.find(action)->second;
    return ka.title + " : " +  toString(ka.actualKey);
}

void KeyBinding::resetBindings()
{
	for(auto &it : m_keyActions)
		it.second.actualKey = it.second.defaultKey;
}

const std::string &KeyBinding::toString(sf::Keyboard::Key k) const
{
    return m_keyMap.find(k)->second;
}

void KeyBinding::initKeyAction()
{
    #define SAVE_ACTION(act, title, defKey) m_keyActions.emplace(std::piecewise_construct,std::forward_as_tuple(act),std::forward_as_tuple(title, defKey))

    SAVE_ACTION(GO_UP, "Go Up", sf::Keyboard::Up);
    SAVE_ACTION(GO_DOWN, "Go Down", sf::Keyboard::Down);
}

void KeyBinding::initKeyMap()
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
    MAP_KEY(Escape);
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

}
