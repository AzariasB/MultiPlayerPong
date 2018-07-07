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
 * File:   Menu.cpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#include "Menu.hpp"
#include "src/client/Provider.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/ResourcesManager.hpp"
#include "src/client/SoundEngine.hpp"
#include "src/client/Renderer.hpp"

namespace mp {


Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::update(const sf::Time &elapsed)
{
    for(auto &it : m_buttons)
        it->update(elapsed);
}

Button &Menu::addButton(const sf::String &content, float xPos, float yPos, const Assets::IconAtlas::Holder &icon)
{    
    m_buttons.emplace_back(std::make_unique<Button>(content, xPos, yPos, icon));
    std::unique_ptr<Button> &inserted = m_buttons.back();

    int idx = m_buttons.size() -1;
    inserted->selectedSignal.add([this, idx](){ setSeletedIndex(idx);});
    if(m_buttons.size() == 1) inserted->setSelected(true);
    return *inserted;
}

std::unique_ptr<I18NText> &Menu::addCenteredLabel(const sf::String &content, float xCenter, float yCenter, unsigned int charSize)
{
    auto &label = addLabel(content, xCenter, yCenter, charSize);
    math::centerOrigin(*label);
    return label;
}

std::unique_ptr<I18NText> &Menu::addLabel(const sf::String &content, float xpOs, float yPos, unsigned int charSize)
{
    m_labels.emplace_back(std::make_unique<I18NText>(pr::translator(), content, charSize));
    m_labels.back()->setFillColor(cc::Colors::fontColor);
    m_labels.back()->setPosition(xpOs, yPos);
    return m_labels.back();
}

std::unique_ptr<I18NText> &Menu::addLabel(const std::vector<sf::String> &content, float xpOs, float yPos, unsigned int charSize)
{
    m_labels.emplace_back(std::make_unique<I18NText>(pr::translator(), content, charSize));
    m_labels.back()->setFillColor(cc::Colors::fontColor);
    m_labels.back()->setPosition(xpOs, yPos);
    return m_labels.back();
}

void Menu::normalizeButtons(float additionalWidth)
{
    float max = (*std::max_element(m_buttons.begin(), m_buttons.end(), [](const auto &p1, const auto &p2){
        return p1->getWidth() < p2->getWidth();
    }))->getWidth();

    for(auto &it : m_buttons){
        it->setWidth(max + additionalWidth);
        it->setOrigin(it->getWidth() / 2.f, it->getHeight() / 2.f);
    }
}

void Menu::render(Renderer &renderer) const
{
    if(!isVisible())return;

    for(auto &ptr : m_buttons)
        ptr->render(renderer);

    for(auto &ptr : m_labels)
        renderer.draw(*ptr);
}

bool Menu::handleEvent(const sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed && (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::Left || ev.key.code == sf::Keyboard::Right)){
        changeSelection( (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::Left) ? -1 : 1);
        return true;
    }else if(ev.type == sf::Event::JoystickMoved && ev.joystickMove.axis == sf::Joystick::Axis::Y && std::abs(ev.joystickMove.position) > 95 ){
        changeSelection(ev.joystickMove.position > 0 ? 1 : -1);
        return true;
    }else{
        for(auto &ptr : m_buttons)
            if(ptr->handleEvent(ev)) return true;

        return false;
    }
}

void Menu::setSeletedIndex(int nwIndex)
{
    if(nwIndex != m_selectedButton){
        m_buttons[m_selectedButton]->setSelected(false);
        m_selectedButton = nwIndex;
        m_buttons[m_selectedButton]->setSelected(true);
        pr::soundEngine().playSound(Assets::Sounds::Click1);
    }
}

void Menu::changeSelection(int dir)
{
    if(dir == -1){
        if(m_selectedButton == 0)return;
        setSeletedIndex(m_selectedButton -1);
    }else{
        if(m_selectedButton == m_buttons.size() -1)return;
        setSeletedIndex(m_selectedButton + 1);
    }
}


}
