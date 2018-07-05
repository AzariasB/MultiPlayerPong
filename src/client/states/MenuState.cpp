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

    Button &soloButton = m_menu.addButton("solo",halfWay ,currentHeight, Assets::IconAtlas::singleplayerIcon);
    currentHeight += soloButton.getHeight() + margin;


    Button &multiPlayerButton = m_menu.addButton("multi", halfWay, currentHeight, Assets::IconAtlas::multiplayerIcon);
    currentHeight += multiPlayerButton.getHeight() + margin;

    Button &optionButton = m_menu.addButton("options", halfWay,currentHeight, Assets::IconAtlas::gearIcon);
    currentHeight += optionButton.getHeight() + margin;

    Button &creditsButton = m_menu.addButton("credits", halfWay, currentHeight, Assets::IconAtlas::informationIcon);
    currentHeight += creditsButton.getHeight() + margin;

    Button &quitButton = m_menu.addButton("quit", halfWay, currentHeight, Assets::IconAtlas::powerIcon);

    m_menu.normalizeButtons(margin);

    soloButton.clickedSignal.add([](){pr::stateMachine().goToState(cc::PLAY_SOLO, TransitionData::GO_UP);});
    optionButton.clickedSignal.add([](){pr::stateMachine().goToState(cc::OPTIONS, TransitionData::GO_RIGHT);});
    creditsButton.clickedSignal.add([](){pr::stateMachine().goToState(cc::CREDITS, TransitionData::GO_LEFT);});

    multiPlayerButton.clickedSignal.add([this](){
        DialogInput &ip = pr::dialogManager().input("Ip","Enter server ip");
        auto inputDialogHidden = [&ip](){
            pr::dialogManager().hideDialog(ip.id());
        };

        ip.canceledSignal.add(inputDialogHidden);
        ip.closeSignal.add(inputDialogHidden);

        ip.confirmedSignal.add([this, &ip](std::string entered){
            if(isValidIp(entered)){
                pr::dialogManager().hideDialog(ip.id());
                pr::stateMachine().goToState(cc::WAITING, TransitionData::GO_UP, entered);
            }else{
                DialogMessage &msg = pr::dialogManager().message("Invalid Ip", "The IP you entered is invalid");
                msg.okClickedSignal.add([&msg](){pr::dialogManager().hideDialog(msg.id());});
            }
        });
    });

    quitButton.clickedSignal.add([this](){
        DialogQuestion &leave = pr::dialogManager().question("Quit","Do you really want to quit ?");
        leave.yesClickedSignal.add([](){ ClientApp::getInstance().quit(); });
        leave.noClickedSignal.add([&leave](){pr::dialogManager().hideDialog(leave.id()); });
    });
}

void MenuState::render(Renderer& renderer) const
{
    m_menu.render(renderer);
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
