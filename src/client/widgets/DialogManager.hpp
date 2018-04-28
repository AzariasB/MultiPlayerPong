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
 * File:   DialogManager.hpp
 * Author: azarias
 *
 * Created on 29/3/2018
 */
#pragma once

#include <map>
#include "Widget.hpp"
#include "Dialog.hpp"
#include "src/client/Provider.hpp"

class DialogManager : public Widget
{
public:
    DialogManager();

    void draw(Renderer &renderer) const override;

    void handleEvent(const sf::Event &ev) override;

    void update(const sf::Time &elapsed) override;

    bool isActiveDialog(const sf::Uint64 &dialogId);

    bool hasActiveDialogs() const;

    void hideDialog(const sf::Uint64 &dialogId);

    DialogInput &input(const std::string &title, const std::string &question);

    DialogMessage &message(const std::string &title, const std::string & message);

    DialogQuestion &question(const std::string &title, const std::string &question);

    ~DialogManager();

private:

    sf::Uint64 m_idGenerator = 0;

    sf::Uint64 m_activeDialogId = 0;

    std::map<sf::Uint64, std::unique_ptr<Dialog>> m_dialogs;

    void removeDialog(sf::Uint64 dialogId);

    void closeDialog(sf::Uint64 dialogId);

    template<typename T, typename ...Args>
    T &createDialog(const Args&... args)
    {
        static_assert(std::is_base_of<Dialog, T>::value, "T must be a subclass of Dialog");

        m_activeDialogId = ++m_idGenerator;

        std::unique_ptr<T> nwDialog = std::make_unique<T>(m_activeDialogId, args...);

        pr::connect(nwDialog->closeEvent, &DialogManager::closeDialog, this, m_activeDialogId);
        pr::connect(nwDialog->hiddenEvent, &DialogManager::removeDialog, this, m_activeDialogId);
        nwDialog->show(true);
        m_dialogs[m_activeDialogId] = std::move(nwDialog);
        return static_cast<T&>(*m_dialogs[m_activeDialogId]);
    }
};


