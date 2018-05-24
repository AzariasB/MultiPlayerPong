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
 * File:   MenuState.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:48
 */
#include <regex>

#include "MenuState.hpp"
#include "src/client/Provider.hpp"
#include "src/client/Assets.hpp"
#include "src/client/ClientApp.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/widgets/Button.hpp"
#include "src/client/widgets/Dialog.hpp"

namespace mp {

MenuState::~MenuState()
{
}

MenuState::MenuState() :
    m_menu()
{

    m_menu.addCenteredLabel("MultiPlayerPong", SF_ARENA_WIDTH/2.f, 100, 70);

    const float margin = 10;
    const float halfWay = SF_ARENA_WIDTH/2.f;
    float currentHeight = SF_ARENA_WIDTH/4.f;

    const Button &soloButton = m_menu.addButton("Solo",halfWay ,currentHeight, Assets::Icons::Singleplayer);
    currentHeight += soloButton.getHeight() + margin;


    const Button &multiPlayerButton = m_menu.addButton("Multiplayer", halfWay, currentHeight, Assets::Icons::Multiplayer);
    currentHeight += multiPlayerButton.getHeight() + margin;

    const Button &optionButton = m_menu.addButton("Options", halfWay,currentHeight, Assets::Icons::Gear);
    currentHeight += optionButton.getHeight() + margin;

    const Button &creditsButton = m_menu.addButton("Credits", halfWay, currentHeight, Assets::Icons::Information);
    currentHeight += creditsButton.getHeight() + margin;

    const Button &quitButton = m_menu.addButton("Quit", halfWay, currentHeight, Assets::Icons::Power);

    m_menu.normalizeButtons(margin);

    pr::connect(soloButton.clickedEvent, &StateMachine::goToState, &pr::stateMachine() , std::make_pair((int)cc::PLAY_SOLO, TransitionData::GO_UP) );
    pr::connect(multiPlayerButton.clickedEvent, &MenuState::showInputDialog, this);
    pr::connect(optionButton.clickedEvent, &StateMachine::goToState, &pr::stateMachine() , std::make_pair((int)cc::OPTIONS, TransitionData::GO_RIGHT));
    pr::connect(creditsButton.clickedEvent, &StateMachine::goToState, &pr::stateMachine(), std::make_pair((int)cc::CREDITS, TransitionData::GO_LEFT));
    pr::connect(quitButton.clickedEvent, &MenuState::requestQuit, this);
}

void MenuState::showInputDialog()
{
    DialogInput &ip = pr::dialogManager().input("Ip","Enter server ip");
    m_inputDialiogId = ip.id();
    pr::connect(ip.cancelClickedEvent, &MenuState::inputDialogHidden, this);
    pr::connect(ip.closeEvent, &MenuState::inputDialogHidden, this);
    pr::connect(ip.confirmClickedEvent, &MenuState::ipEntered, this);
}

void MenuState::inputDialogHidden()
{
    pr::dialogManager().hideDialog(m_inputDialiogId);
    m_inputDialiogId = 0;
}

void MenuState::gotoOptionState()
{
    pr::stateMachine().goToState(cc::OPTIONS, TransitionData::GO_LEFT);
}

void MenuState::ipEntered(const std::string &entered)
{
    if(isValidIp(entered)){
        pr::dialogManager().hideDialog(m_inputDialiogId);
        pr::stateMachine().goToState(cc::WAITING, TransitionData::GO_UP, entered);
    }else{
        DialogMessage &msg = pr::dialogManager().message("Invalid Ip", "The IP you entered is invalid");
        pr::connect(msg.okClickedEvent, &Dialog::hide, static_cast<Dialog*>(&msg));
    }
}

void MenuState::requestQuit()
{
    DialogQuestion &leave = pr::dialogManager().question("Quit","Do you really want to quit ?");
    pr::connect(leave.yesClickedEvent, &ClientApp::quit, &ClientApp::getInstance());
    pr::connect(leave.noClickedEvent, &DialogManager::hideDialog, &pr::dialogManager(), leave.id());
}

void MenuState::draw(Renderer& renderer) const
{
    m_menu.draw(renderer);
}

void MenuState::handleEvent(const sf::Event& ev)
{
    if(!pr::dialogManager().hasActiveDialogs())
        m_menu.handleEvent(ev);
}

void MenuState::update(const sf::Time &elapsed)
{
    m_menu.update(elapsed);
}

bool MenuState::isValidIp(const std::string &enteredIp) const
{
    return std::regex_match(enteredIp, std::regex("^((2(5[0-5]|[0-4][0-9])|1[0-9]{2}|[0-9]{1,2})(\\.|$)){4}"));
}

void MenuState::onAfterLeaving()
{
}

}
