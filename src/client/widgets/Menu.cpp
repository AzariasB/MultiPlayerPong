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
 * File:   Menu.cpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#include "Menu.hpp"
#include "src/client/Provider.hpp"
#include "src/client/Renderer.hpp"
#include "src/client/ClientConf.hpp"
#include "src/client/SoundEngine.hpp"
#include "src/client/ResourcesManager.hpp"

namespace mp {


Menu::Menu()
{
}

Menu::~Menu()
{

}

bool Menu::update(const sf::Time &elapsed)
{
    for(auto &it : m_buttons)
        it->update(elapsed);
    return true;
}


Button &Menu::addButton(const sf::String &content, float xPos, float yPos)
{
    m_buttons.emplace_back(std::make_unique<Button>(content, xPos, yPos));
    return configureButton(*m_buttons.back());
}

Button &Menu::addButton(const sf::String &content, float xPos, float yPos, const Assets::IconAtlas::Holder &icon)
{    
    m_buttons.emplace_back(std::make_unique<Button>(content, xPos, yPos, icon));
    return configureButton(*m_buttons.back());
}

Button &Menu::addButton(const std::vector<sf::String> &content, float xPos, float yPos, const Assets::IconAtlas::Holder &icon)
{
    m_buttons.emplace_back(std::make_unique<Button>(content, xPos, yPos, icon));
    return configureButton(*m_buttons.back());
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

Button &Menu::configureButton(Button &inserted)
{
    std::size_t idx = m_buttons.size() -1;
    inserted.selectedSignal.add([this, idx](){ setSeletedIndex(idx);});
    if(m_buttons.size() == 1) inserted.setSelected(true);
    return inserted;
}

void Menu::normalizeButtons(float additionalWidth)
{
    float max = (*std::max_element(m_buttons.begin(), m_buttons.end(), [](const auto &p1, const auto &p2){
        return p1->getWidth() < p2->getWidth();
    }))->getWidth();

    for(auto &it : m_buttons){
        it->setWidth(max + additionalWidth);
        it->setOrigin(it->getWidth() / 2.f, 0);
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
        return changeSelection( (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::Left) ? -1 : 1);
    }else if(ev.type == sf::Event::JoystickMoved && ev.joystickMove.axis == sf::Joystick::Axis::Y && std::abs(ev.joystickMove.position) > 95 ){
        return changeSelection(ev.joystickMove.position > 0 ? 1 : -1);
    }else{
        for(auto &ptr : m_buttons)
            if(ptr->handleEvent(ev)) return true;

        return false;
    }
}

bool Menu::setSeletedIndex(std::size_t nwIndex)
{
    if(nwIndex != m_selectedButton){
        m_buttons[m_selectedButton]->setSelected(false);
        m_selectedButton = nwIndex;
        m_buttons[m_selectedButton]->setSelected(true);
        pr::soundEngine().playSound(Assets::Sounds::Click1);
        return true;
    }
    return false;
}

bool Menu::changeSelection(int dir)
{
    if(dir == -1){
        return m_selectedButton != 0 && setSeletedIndex(m_selectedButton - 1);
    }else{
        return m_selectedButton != m_buttons.size() - 1 && setSeletedIndex(m_selectedButton + 1);
    }
}


}
