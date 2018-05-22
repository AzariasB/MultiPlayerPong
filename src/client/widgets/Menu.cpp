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

std::unique_ptr<Button> &Menu::addButton(const std::string &content, float xPos, float yPos)
{    
    m_buttons.emplace_back(std::make_unique<Button>(content, xPos, yPos));
    std::unique_ptr<Button> &inserted = m_buttons.back();

    int idx = m_buttons.size() -1;
    pr::connect(inserted->selectdEvent, &Menu::setSeletedIndex, this, idx);

    if(m_buttons.size() == 1) inserted->setSelected(true);
    return inserted;
}

std::unique_ptr<sf::Text> &Menu::addCenteredLabel(const std::string &content, float xCenter, float yCenter, unsigned int charSize)
{
    auto &label = addLabel(content, xCenter, yCenter, charSize);
    sf::Vector2f labelPos(label->getPosition().x - label->getGlobalBounds().width / 2.f,
                          label->getPosition().y - label->getGlobalBounds().height / 2.f);
    label->setPosition(labelPos);
    return label;
}

std::unique_ptr<sf::Text> &Menu::addLabel(const std::string &content, float xpOs, float yPos, unsigned int charSize)
{
    m_labels.emplace_back(std::make_unique<sf::Text>(content,pr::resourceManager().getFont(), charSize));
    m_labels.back()->setFillColor(cc::Colors::fontColor);
    m_labels.back()->setPosition(xpOs, yPos);
    return m_labels.back();
}

void Menu::normalizeButtons(float additionalWidth)
{
    float max = (*std::max_element(m_buttons.begin(), m_buttons.end(), [](const auto &p1, const auto &p2){
        return p1->getWidth() < p2->getWidth();
    }))->getWidth();

    for(auto &it : m_buttons)
        it->setWidth(max + additionalWidth);
}

void Menu::draw(Renderer &renderer) const
{
    if(!isVisible())return;

    for(auto &ptr : m_buttons)
        ptr->draw(renderer);

    for(auto &ptr : m_labels)
        renderer.render(*ptr);

    for(auto &ptr : m_sprites)
        renderer.render(*ptr);
}

void Menu::handleEvent(const sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed && (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::Down)){
        changeSelection(ev.key.code == sf::Keyboard::Up ? -1 : 1);
    }else if(ev.type == sf::Event::JoystickMoved && ev.joystickMove.axis == sf::Joystick::Axis::Y && std::abs(ev.joystickMove.position) > 95 ){
        changeSelection(ev.joystickMove.position > 0 ? 1 : -1);
    }else{
        for(auto &ptr : m_buttons)
            ptr->handleEvent(ev);
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
