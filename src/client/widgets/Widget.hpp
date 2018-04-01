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
 * File:   Widget.h
 * Author: azarias
 *
 * Created on 22 octobre 2017, 16:30
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>

class ClientApp;
class Renderer;

/**
 * @brief The Widget class base class for all the widgets of this app
 */
class Widget {
public:

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
    virtual void draw(Renderer &renderer) const = 0;

	/**
	 * @brief handleEvent handles an event sent by sfml
	 * @param ev the event to handle
	 */
	virtual void handleEvent(const sf::Event &ev) = 0;

    virtual void update(const sf::Time &elapsed)
    {

    }

	virtual ~Widget()
	{

	}
};

#endif /* WIDGET_H */

