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
 * File:   DialogManager.cpp
 * Author: azarias
 *
 * Created on 29/3/2018
 */
#include "DialogManager.hpp"

namespace mp {

DialogManager::DialogManager()
{

}

DialogManager::~DialogManager()
{

}

void DialogManager::render(Renderer &renderer) const
{
    for(auto &ptr : m_dialogs)
        ptr.second->render(renderer);
}

void DialogManager::handleEvent(const sf::Event &ev)
{
    if(m_activeDialogId > 0)
        m_dialogs[m_activeDialogId]->handleEvent(ev);
}

void DialogManager::update(const sf::Time &elapsed)
{
    for(auto &ptr : m_dialogs) ptr.second->update(elapsed);
}

bool DialogManager::isActiveDialog(const sf::Uint64 &dialogId)
{
    return dialogId > 0 && m_activeDialogId > 0 && dialogId == m_activeDialogId;
}

bool DialogManager::hasActiveDialogs() const
{
    return m_dialogs.size() > 0;
}

void DialogManager::hideDialog(sf::Uint64 dialogId)
{
    if(m_dialogs[dialogId]){
        m_dialogs[dialogId]->hide();
    }
}

void DialogManager::removeDialog(sf::Uint64 dialogId)
{
    m_dialogs.erase(dialogId);
    if(dialogId == m_activeDialogId){
        if(m_dialogs.size() > 0){
            m_activeDialogId = (*std::prev(m_dialogs.end())).first;
        }else{
            m_activeDialogId = 0;
        }
    }
}

void DialogManager::closeDialog(sf::Uint64 dialogId)
{
    if(dialogId > 0 && m_dialogs.find(dialogId) != m_dialogs.end()){
        m_dialogs[dialogId]->hide();
    }
}

DialogInput &DialogManager::input(const std::string &title, const std::string &question)
{
    return createDialog<DialogInput>(title, question);
}

DialogQuestion &DialogManager::question(const std::string &title, const std::string &question)
{
    return createDialog<DialogQuestion>(title, question);
}

DialogMessage &DialogManager::message(const std::string &title, const std::string &message)
{
    return createDialog<DialogMessage>(title, message);
}

}

