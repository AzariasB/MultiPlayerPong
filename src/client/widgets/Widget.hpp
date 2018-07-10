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
 * File:   Widget.h
 * Author: azarias
 *
 * Created on 22 octobre 2017, 16:30
 */

#pragma once

#include "src/client/Renderable.hpp"

namespace sf {
    class Event;
    class Time;
}

namespace mp {

class ClientApp;
class Renderer;

/**
 * @brief The Widget class base class for all the widgets of this app
 */
class Widget : public Renderable {
public:

    enum Alignment{
        TopLeft,
        BottomLeft,
        Center,
        TopRight,
        BottomRight
    };


    /**
     * @brief Widget constructor
     * @param app a reference to the client's application
     */
    Widget()
    {

    }

    /**
     * @brief draw draws the widget to the given target, using the given rendering states
     * @param target the target in which to draw the widget
     * @param states the states to use when drawing the widget
     */
    virtual void render(Renderer &renderer) const override = 0;

    /**
     * @brief handleEvent handles an event sent by sfml
     * @param ev the event to handle
     */
    virtual bool handleEvent(const sf::Event &ev) = 0;

    /**
     * @brief update calls to update the internal state of the widget
     * @param elapsed the time elapsed since the last update method was called
     * @return true if the widget is still "alive" and must be updated at the next frame
     * false if it does not need to be updated anymore (and can be destroyed)
     */
    virtual bool update(const sf::Time &elapsed)
    {
        return true;
    }

    virtual ~Widget()
    {

    }

    /**
     * @brief isVisible
     * @return the visibility of this widget
     */
    bool isVisible() const {return m_isVisible;}

    /**
     * @brief setVisible setter for the visibility of the widget
     * @param visible
     */
    void setVisible(bool visible){m_isVisible = visible;}


private:
    /**
     * @brief m_isVisible
     * wether the widget must be
     * displayed on screen, this must be handled
     * by the sub-class of the widget
     */
    bool m_isVisible = true;

};


}


