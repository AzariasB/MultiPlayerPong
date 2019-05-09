/*
 * The MIT License
 *
 * Copyright 2017-2019 azarias.
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
#include "PlaySoloState.hpp"
#include "OptionState.hpp"
#include "CreditsState.hpp"
#include "WaitingState.hpp"

#include "src/client/Provider.hpp"
#include "src/client/Assets.hpp"
#include "src/client/ClientApp.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/widgets/Button.hpp"
#include "src/client/widgets/Dialog.hpp"

#include <iostream>

namespace mp {

MenuState::~MenuState()
{
}

MenuState::MenuState() :
    m_menu()
{

    m_menu.addCenteredLabel("MultiPlayerPong", SF_CENTER_X, 100, 70);

    const float margin = 10;
    float currentHeight = SF_ARENA_WIDTH/4.f;

    Button &soloButton = m_menu.addButton("solo",SF_CENTER_X ,currentHeight, Assets::IconAtlas::singleplayerIcon);
    currentHeight += soloButton.getHeight() + margin;

    Button &solo1v1 = m_menu.addButton({"solo", " 1v1"}, SF_CENTER_X, currentHeight, Assets::IconAtlas::multiplayerIcon );
    currentHeight += solo1v1.getHeight() + margin;

    Button &multiPlayerButton = m_menu.addButton("multi", SF_CENTER_X, currentHeight, Assets::IconAtlas::massiveMultiplayerIcon);
    currentHeight += multiPlayerButton.getHeight() + margin;

    Button &optionButton = m_menu.addButton("options", SF_CENTER_X,currentHeight, Assets::IconAtlas::gearIcon);
    currentHeight += optionButton.getHeight() + margin;

    Button &creditsButton = m_menu.addButton("credits", SF_CENTER_X, currentHeight, Assets::IconAtlas::informationIcon);
    currentHeight += creditsButton.getHeight() + margin;

    Button &quitButton = m_menu.addButton("quit", SF_CENTER_X, currentHeight, Assets::IconAtlas::powerIcon);

    m_menu.normalizeButtons(margin);
    pr::translator().translationChangedSignal.add([this, margin](){
        m_menu.normalizeButtons(margin);
    });

    soloButton.clickedSignal.add([](){
        pr::game().setGameMode(GAME_MODE::SOLO_AI);
        pr::stateMachine().slideTo<PlaySoloState>(cc::SLIDE_DIRECTION::SLIDE_UP);
    });
    solo1v1.clickedSignal.add([](){
        pr::game().setGameMode(GAME_MODE::SOLO_1V1);
        pr::stateMachine().slideTo<PlaySoloState>(cc::SLIDE_DIRECTION::SLIDE_UP);
    });
    optionButton.clickedSignal.add([](){
        pr::stateMachine().slideTo<OptionState>(cc::SLIDE_DIRECTION::SLIDE_RIGHT);
    });
    creditsButton.clickedSignal.add([](){
        pr::stateMachine().slideTo<CreditsState>(cc::SLIDE_DIRECTION::SLIDE_LEFT);
    });

    multiPlayerButton.clickedSignal.add([this](){
        DialogInput &ip = pr::dialogManager().input("Ip","enter_ip");
        auto inputDialogHidden = [&ip](){
            pr::dialogManager().hideDialog(ip.id());
        };

        ip.canceledSignal.add(inputDialogHidden);
        ip.closeSignal.add(inputDialogHidden);

        ip.confirmedSignal.add([this, &ip](std::string entered){
            if(isValidIp(entered)){
                pr::dialogManager().hideDialog(ip.id());
                pr::stateMachine().slideTo<WaitingState>(cc::SLIDE_DIRECTION::SLIDE_UP, std::move(entered));
            }else{
                DialogMessage &msg = pr::dialogManager().message("invalid_ip", "entered_invalid_id");
                msg.okClickedSignal.add([&msg](){pr::dialogManager().hideDialog(msg.id());});
            }
        });
    });

    quitButton.clickedSignal.add([](){
        DialogQuestion &leave = pr::dialogManager().question("quit","really_quit");
        leave.yesClickedSignal.add([](){ ClientApp::getInstance().quit(); });
        leave.noClickedSignal.add([&leave](){pr::dialogManager().hideDialog(leave.id()); });
    });
}

void MenuState::render(Renderer& renderer) const
{
    renderer
            .render(m_menu);
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
