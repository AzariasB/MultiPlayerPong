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
 * File:   MenuState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */

#include "MenuState.hpp"
#include "ClientApp.hpp"
#include <regex>

MenuState::~MenuState()
{
	delete m_inputDialog;
	delete m_messageDialog;
}

MenuState::MenuState(ClientApp& client) :
	State(client),
	m_menu(client),
	m_inputDialog(Dialog::input(client,"IP adress")),
	m_messageDialog(Dialog::message(client, "", "") )
{
	EventManager &evM = client.getGame().getEventManager();
	const Button &playButton = *m_menu.addButton("Play", 0,0);
	const Button &optionButton = *m_menu.addButton("Options", 0, playButton.getHeight());
	const Button &quitButton = *m_menu.addButton("Quit", 0, playButton.getHeight() + optionButton.getHeight());

	evM.declareListener(playButton.clickedEvent, &Dialog::show, m_inputDialog);
	evM.declareListener(optionButton.clickedEvent, &StateMachine::setCurrentState, &getApp().getStateMachine(), (int)STATE_TYPE::OPTIONS);
	evM.declareListener(quitButton.clickedEvent, &ClientApp::quit, &getApp());
	evM.declareListener(m_inputDialog->cancelEvent, &Dialog::hide, m_inputDialog);
	evM.declareListener(m_inputDialog->okEvent, &MenuState::dialogConfirmed, this);
	evM.declareListener(m_messageDialog->okEvent, &Dialog::hide, m_messageDialog);
	evM.declareListener(m_messageDialog->cancelEvent, &Dialog::hide, m_messageDialog);
}


void MenuState::dialogConfirmed()
{
	if(isValidIp(m_inputDialog->getResult())){
		m_inputDialog->hide();
		//change of state and indicate the server's ip
		std::string res = m_inputDialog->getResult();
		getApp().getStateMachine().setCurrentState(STATE_TYPE::WAITING, res);
	}else{
		//Message
		m_messageDialog->setTitle("Invalid IP");
		m_messageDialog->show();
	}
}

void MenuState::draw(Renderer& renderer) const
{
	renderer.render(m_menu);
	renderer.render(*m_inputDialog);
	renderer.render(*m_messageDialog);
}

void MenuState::handleEvent(const sf::Event& ev)
{
	if(m_messageDialog->isVisible()){
		m_messageDialog->handleEvent(ev);
	}else if(m_inputDialog->isVisible()){
		m_inputDialog->handleEvent(ev);
	}else{
		m_menu.handleEvent(ev);
	}
}

void MenuState::update(const sf::Time &elapsed)
{
	//Nothing to do for now
}

bool MenuState::isValidIp(const std::string &enteredIp) const
{
	return std::regex_match(enteredIp, std::regex("^((2(5[0-5]|[0-4][0-9])|1[0-9]{2}|[0-9]{1,2})(\\.|$)){4}"));
}

void MenuState::onEnter(BaseStateData *data)
{

}

void MenuState::onLeave()
{

}
