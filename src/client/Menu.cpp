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
 * File:   Menu.cpp
 * Author: azarias
 *
 * Created on 1/11/2017
 */
#include "Menu.hpp"
#include "ClientApp.hpp"
#include "../Game.hpp"

Menu::Menu(ClientApp &app):
    Widget(app)
{

}

Menu::~Menu()
{

}

std::unique_ptr<Button> &Menu::addButton(const std::string &content, int xPos, int yPos)
{    
    m_buttons.emplace_back(std::make_unique<Button>(app(), content, xPos, yPos));
    std::unique_ptr<Button> &inserted = m_buttons.back();

    int idx = m_buttons.size() -1;
     app().getGame().getEventManager().declareListener(inserted->selectdEvent, &Menu::setSeletedIndex, this, idx);

    if(m_buttons.size() == 1) inserted->setSelected(true);
    return inserted;
}


std::unique_ptr<sf::Text> &Menu::addLabel(const std::string &content, int xpOs, int yPos)
{
    m_labels.emplace_back(std::make_unique<sf::Text>(content, app().getResourcesManager().getFont()));
    m_labels.back()->setPosition(xpOs, yPos);
    return m_labels.back();
}

std::unique_ptr<sf::Sprite> &Menu::addSprite(const std::string &textureName, const sf::Vector2f &pos, const sf::IntRect &textureRect)
{
    const sf::Texture &texture = app().getResourcesManager().getTexture(textureName);
    m_sprites.emplace_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(texture, textureRect)));
    m_sprites.back()->setPosition(pos);
    return m_sprites.back();
}

void Menu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(auto it = m_buttons.begin(); it != m_buttons.end(); ++it){
        target.draw(**it, states);
    }

    for(auto it = m_labels.begin(); it != m_labels.end(); ++it){
        target.draw(**it, states);
    }

    for(auto it = m_sprites.begin(); it != m_sprites.end(); ++it){
        target.draw(**it, states);
    }
}

void Menu::handleEvent(const sf::Event &ev)
{
    if(ev.type == sf::Event::KeyPressed && (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::Down)){
        changeSelection(ev.key.code == sf::Keyboard::Up ? -1 : 1);
    }else if(ev.type == sf::Event::JoystickMoved && ev.joystickMove.axis == sf::Joystick::Axis::Y && std::abs(ev.joystickMove.position) > 95 ){
        changeSelection(ev.joystickMove.position > 0 ? 1 : -1);
    }else{
        for(auto it = m_buttons.begin(); it != m_buttons.end(); ++it){
            (*it)->handleEvent(ev);
        }
    }
}

void Menu::setSeletedIndex(int nwIndex)
{
    m_buttons[m_selectedButton]->setSelected(false);
    m_selectedButton = nwIndex;
    m_buttons[m_selectedButton]->setSelected(true);
}

void Menu::changeSelection(int dir)
{
    int oldSelected = m_selectedButton;
    if(dir == -1){
        if(m_selectedButton == 0)return;
        m_selectedButton--;
    }else{
        if(m_selectedButton == m_buttons.size() -1)return;
        m_selectedButton++;
    }

    m_buttons[oldSelected]->setSelected(false);
    m_buttons[m_selectedButton]->setSelected(true);
}
