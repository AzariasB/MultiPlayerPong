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

namespace mp {

/**
 * @brief The DialogManager class
 * class used to handle the dialogs during
 * the game.
 * The dialogs are not really part of any
 * stage or state. They have their own states
 * this is managed by the dialogmanager, it
 * can be used to show hide different types
 * of dialogs
 */
class DialogManager : public Widget
{
public:
    /**
     * @brief DialogManager constructor
     */
    DialogManager();

    /**
     * @brief draw draws all the visible dialogs
     * @param renderer renderer to use
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief handleEvent perform the event on the current dialog
     * @param ev event to handle
     */
    void handleEvent(const sf::Event &ev) override;

    /**
     * @brief update updates all the visible dialogs
     * @param elapsed time
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief isActiveDialog checks wether the given dialog is the active dialog
     * @param dialogId dialog's id to check
     * @return if the given id is the active dialog
     */
    bool isActiveDialog(const sf::Uint64 &dialogId);

    /**
     * @brief hasActiveDialogs
     * @return wether they are any active dialogs
     */
    bool hasActiveDialogs() const;

    /**
     * @brief hideDialog hides the dialog with the given id
     * @param dialogId id of the dialog to hide
     * if the dialog does not exist or is already hidden/hiding,
     * will do nothing
     */
    void hideDialog(sf::Uint64 dialogId);

    /**
     * @brief input creates an input dialog (a dialog with a simple text input)
     * @param title the title of the dialog
     * @param question the question to show
     * @return a reference to the created dialog
     */
    DialogInput &input(const std::string &title, const std::string &question);

    /**
     * @brief message create a message dialog (showing a simple message)
     * @param title title of the dialog
     * @param message message to show
     * @return a reference to the created message dialog
     */
    DialogMessage &message(const std::string &title, const std::string & message);

    /**
     * @brief question creates a yes-no question dialog
     * @param title the title of the dialog
     * @param question the question to show
     * @return a reference to the created dialogquestion
     */
    DialogQuestion &question(const std::string &title, const std::string &question);

    ~DialogManager();

private:
    /**
     * @brief m_idGenerator used to generate the id of the dialogs
     */
    sf::Uint64 m_idGenerator = 0;

    /**
     * @brief m_activeDialogId id of the active dialog
     * 0 means no active dialog
     */
    sf::Uint64 m_activeDialogId = 0;

    /**
     * @brief m_dialogs map containing all the created dialogs
     * they are either showing, shown, hiding or hidden
     * otherwise they should be destroyed
     * A unique_ptr is used because Dialog is an abstract class
     */
    std::map<sf::Uint64, std::unique_ptr<Dialog>> m_dialogs;

    /**
     * @brief removeDialog remves the dialog from the map
     * @param dialogId id of the dialog to remove
     */
    void removeDialog(sf::Uint64 dialogId);

    /**
     * @brief closeDialog closes the dialog
     * @param dialogId id of the dialog to close
     */
    void closeDialog(sf::Uint64 dialogId);

    /**
     * @brief createDialog create the dialog, and gives it the given arguments
     * @param args args to pass to the dialog constructor
     * @return a reference to the created dialog
     */
    template<typename T, typename ...Args>
    T &createDialog(const Args&... args)
    {
        static_assert(std::is_base_of<Dialog, T>::value, "T must be a subclass of Dialog");

        m_activeDialogId = ++m_idGenerator;

        std::unique_ptr<T> nwDialog = std::make_unique<T>(m_activeDialogId, args...);

        nwDialog->closeSignal.add([this](){closeDialog(m_activeDialogId); });
        nwDialog->hiddenSignal.add([this](){removeDialog(m_activeDialogId); });

        nwDialog->show(true);
        m_dialogs[m_activeDialogId] = std::move(nwDialog);
        return static_cast<T&>(*m_dialogs[m_activeDialogId]);
    }
};

}



