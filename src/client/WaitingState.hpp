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
 * File:   WaitingState.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */

#ifndef WAITINGSTATE_H
#define WAITINGSTATE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Dialog.hpp"

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
	void draw(Renderer& renderer) const override;

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

	/**
	 * @brief onLeave inherited function
	 */
	void onLeave() override;

	/**
	 * @brief listenSocket function called by the thread to listen at the sockets
	 */
	void listenSocket();

	/**
	 * @brief cancelClicked function called when the button "cancel" is clicked
	 */
	void cancelClicked();

	virtual ~WaitingState();
private:
	/**
	 * @brief listeningThread the thread that listens inputs from the server
	 */
	sf::Thread listeningThread;
	/**
	 * @brief canBeginMutex mutex to lock the "canBegin" variable access
	 */
	mutable sf::Mutex canBeginMutex;
	/**
	 * @brief cStateMutex mutex to lock th "cState" variable access
	 */
	mutable sf::Mutex cStateMutex;

	/**
	 * @brief m_messageDialog the dialog to display, to show the state
	 * of the application
	 */
	Dialog *m_messageDialog;

	/**
	 * @brief c_state state current connection state
	 */
	CONNECTION_STATE c_state;

	/**
	 * @brief canBegin wether the game can begin
	 */
	bool canBegin = false;

	/**
	 * @brief receivedNumber number sent by the server
	 * to the client to indicate it's player number
	 */
	int receivedNumber = -1;
};

#endif /* WAITINGSTATE_H */

