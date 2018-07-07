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
 * File:   WaitingState.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */

#pragma once


#include "src/client/State.hpp"
#include "src/client/widgets/Menu.hpp"

namespace sf {
class Event;
class Time;
}


namespace mp {

class Dialog;

enum CONNECTION_STATE {
    PENDING,
    CONNECTED,
    DISCONNECTED,
};

/**
 * @brief The WaitingState class state used when the client
 * is trying to connect to the server, and when the server is actually
 * waiting for another player to connect
 */
class WaitingState : public State {
public:
    /**
     * @brief WaitingState constructor
     * @param client reference to the client's app
     */
    WaitingState();

    /**
     * @brief draw inherited function
     * @param renderer
     */
    void render(Renderer& renderer) const override;

    /**
     * @brief update inherited function
     * @param dtS
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    void handleEvent(const sf::Event& ev) override;

    /**
     * @brief onEnter inherited function
     * @param data inherited function
     */
    void onEnter(BaseStateData *data) override;

    virtual ~WaitingState();
private:

    /**
     * @brief c_state state current connection state
     */
    CONNECTION_STATE c_state;

    /**
     * @brief m_menu Menu to show the texts
     * and the "menu" button
     */
    Menu m_menu;

    /**
     * @brief m_content text containing
     */
    I18NText &m_content;
};



}


