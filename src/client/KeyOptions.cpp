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
 * File:   KeyOptions.cpp
 * Author: azarias
 *
 * Created on 3/11/2017
 */
#include "KeyOptions.hpp"
#include "ClientApp.hpp"
#include <iostream>

KeyOptions::KeyOptions(ClientApp &app, int startX, int startY):
	Menu(app),
	m_messageDialog(Dialog::message(app, "","Press a key"))
{
	for(KeyBinding::KEY_ACTION ka : KeyBinding::allActions){
		std::string btnTitle = app.getKeyBindings().toString(ka);
		Button *b = addButton( btnTitle ,startX, startY).get();
		startY += b->getHeight();
		m_actions.emplace_back(std::make_unique<ActionsButton>(b, ka));
		app.getGame().getEventManager().declareListener(
					b->clickedEvent,
					&KeyOptions::buttonClicked,
					this,
					m_actions.back().get()
					);
	}

	Button &resetB = *addButton("Reset", startX, startY);
	app.getGame().getEventManager().declareListener(
				resetB.clickedEvent,
				&KeyOptions::resetKeys,
				this
				);

	m_messageDialog->setOkButtonTitle("Cancel");
	app.getGame().getEventManager().declareListener(
				m_messageDialog->cancelEvent,
				&KeyOptions::cancelDialog,
				this
				);
	app.getGame().getEventManager().declareListener(
				m_messageDialog->okEvent,
				&KeyOptions::cancelDialog,
				this
				);
}

KeyOptions::~KeyOptions()
{
	delete m_messageDialog;
}

void KeyOptions::resetKeys()
{
	app().getKeyBindings().resetBindings();
	for(auto &it : m_actions)
		it->button->setText(app().getKeyBindings().toString(it->action));
}

void KeyOptions::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	Menu::draw(target, states);
	target.draw(*m_messageDialog);
}

void KeyOptions::handleEvent(const sf::Event &ev)
{
	if(m_messageDialog->isVisible()){
		if(ev.type == sf::Event::KeyPressed && m_waitingAction){
			app().getKeyBindings().setKeyAction(m_waitingAction->action, ev.key.code);
			std::string nwBtnTitle = app().getKeyBindings().toString(m_waitingAction->action);
			m_waitingAction->button->setText(nwBtnTitle);
			m_waitingAction = 0;
			m_messageDialog->hide();
		}else{
			m_messageDialog->handleEvent(ev);
		}
	}else{
		Menu::handleEvent(ev);
	}
}

void KeyOptions::cancelDialog()
{
	m_waitingAction = 0;
	m_messageDialog->hide();
}


void KeyOptions::buttonClicked(ActionsButton *ab)
{
	m_waitingAction = ab;
	m_messageDialog->show();
}
