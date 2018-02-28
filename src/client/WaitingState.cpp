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
 * File:   WaitingState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */


#include <SFML/System/Thread.hpp>
#include "ClientApp.hpp"
#include "WaitingState.hpp"
#include "Provider.hpp"

WaitingState::~WaitingState()
{
	delete m_messageDialog;
}


WaitingState::WaitingState() :
    State(),
	listeningThread(&WaitingState::listenSocket, this),
    m_messageDialog(Dialog::message("","Connecting..."))
{
	m_messageDialog->setOkButtonTitle("Cancel");

    pr::connect(m_messageDialog->okEvent, &WaitingState::cancelClicked, this);
    pr::connect(m_messageDialog->cancelEvent, &WaitingState::cancelClicked, this);

	m_messageDialog->show();
}


void WaitingState::draw(Renderer& renderer) const
{
	renderer.render(*m_messageDialog);
}

void WaitingState::handleEvent(const sf::Event& ev)
{
	m_messageDialog->handleEvent(ev);
}


void WaitingState::cancelClicked()
{
	listeningThread.terminate();
    pr::socket().disconnect();
    goToState((int)STATE_TYPE::MENU, TransitionData::GO_RIGHT);
}

void WaitingState::update(const sf::Time &elapsed)
{
	//Blinking point
	bool startGame;
	canBeginMutex.lock();
	startGame = canBegin;
	if (receivedNumber == 1 || receivedNumber == 2) {
        ClientApp::getInstance().setPNumber(receivedNumber);
		receivedNumber = -1;
	}
	canBeginMutex.unlock();
	sf::String text = "Connecting...";
	cStateMutex.lock();
	if (c_state == CONNECTION_STATE::CONNECTED) {
		text = "Waiting for player ...";
	}
	cStateMutex.unlock();
	m_messageDialog->setTitle(text.toAnsiString());

	if (startGame)
        goToState((int)STATE_TYPE::PLAY, TransitionData::GO_LEFT);

}

void WaitingState::onEnter(BaseStateData *data)
{
	canBegin = false;
	c_state = CONNECTION_STATE::PENDING;

	StateData<std::string> *ipData = 0;
	if(!(ipData = static_cast<StateData<std::string>*>(data)))return;

    sf::Socket::Status status = pr::socket().connect(sf::IpAddress(ipData->data()), 5300);
	if (status != sf::Socket::Done) {
		m_messageDialog->setTitle("Failed to connect");
	} else {
		std::cout << "Successfully connected to server\n";
		listeningThread.launch();
	}
}

void WaitingState::onLeave()
{
	listeningThread.terminate();
}

void WaitingState::listenSocket()
{
	sf::Packet firstPacket;
    sf::Socket::Status rcvStatus = pr::socket().receive(firstPacket);
	if (rcvStatus != sf::Socket::Done) {
		std::cerr << "Failed to receive first packet (Socket status = " << rcvStatus << ")\n";
		exit(-1);
	}

	cStateMutex.lock();
	c_state = CONNECTION_STATE::CONNECTED;
	cStateMutex.unlock();

	int pNumber;
	firstPacket >> pNumber;
	canBeginMutex.lock();
	receivedNumber = pNumber;
	canBeginMutex.unlock();


    if (pr::socket().receive(firstPacket) != sf::Socket::Done) {
		cStateMutex.lock();
		c_state = CONNECTION_STATE::DISCONNECTED;
		cStateMutex.unlock();
	}


	canBeginMutex.lock();
	canBegin = true;
	canBeginMutex.unlock();
	//die peacefully
}
