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
 * File:   CreditsState.hpp
 * Author: azarias
 *
 * Created on 17/5/2018
 */
#pragma once

#include "src/client/State.hpp"
#include "src/client/widgets/Menu.hpp"

namespace mp {

/**
 * @brief The CreditsState class
 * State used to credit all the work
 * used for this project, all the frameworks
 * librairies, artworks, ...
 * It's just a simple menu with a single
 * button to go back to the menu
 */
class CreditsState : public State
{
public:
    /**
     * @brief CreditsState
     * empty constructor
     */
    CreditsState();

    /**
     * @brief update inherited function
     * @param elapsed
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief draw inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief handleEvent inherited function
     * @param ev
     */
    void handleEvent(const sf::Event &ev) override;

private:

    std::string sfmlVersion() const;

    std::string box2dVersion() const;

    std::string qtVersion() const;

    std::string toVersion(int major, int minor, int patch) const;

    /**
     * @brief menu transitions back to the menu
     */
    void menu();

    /**
     * @brief mMenu the main menu
     * to display, with all the credits in it
     */
    Menu mMenu;
};

}
