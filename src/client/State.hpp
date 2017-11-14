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
 * File:   State.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:20
 */

#ifndef STATE_H
#define STATE_H

#include <SFML/Window/Event.hpp>

#include "../Game.hpp"
#include "Renderer.hpp"

class ClientApp;

/**
 * @brief The BaseStateData struct base struct given to the states
 * when the function "onEnter" is called
 */
struct BaseStateData{
	virtual ~BaseStateData()
	{

	}

};


/**
 * @brief The StateData struct struct with data to pass it between the states
 * when onEnter is called
 */
template<typename T>
struct StateData : public BaseStateData{
	StateData(const T &data):
		m_data(data)
	{
	}


	/**
	 * @brief reference to the data hold by the object
	 * @return reference to the data hold by the object
	 */
	virtual const T &data() const
	{
		return m_data;
	}

	virtual ~StateData()
	{

	}
private:
	/**
	 * @brief m_data data held by this object
	 */
	T m_data;
};


/**
 * @brief The State class is a virtual class
 * that must be inherited by all the states of the game
 * It introduces several virtual functions that must be overriden
 * by the subclasses.
 */
class State : public sf::NonCopyable{
public:

	/**
	 * @brief State constructor
	 * @param client a reference to the client application
	 */
	State(ClientApp &client) :
		client(client)
	{

	}

	/**
	 * @brief update updates the State, is called on a regular basis, must be used to update the intern state of the state.
	 * @param elapsed the time elapsed since the last update occured, passed in as a SFML time object
	 */
	virtual void update(const sf::Time &elapsed) = 0;

	/**
	 * @brief handleEvent handles the event sent by the renderwindow (mouse move, key pressed, ...)
	 * @param ev the sfml object for the event
	 */
	virtual void handleEvent(const sf::Event &ev) = 0;

	/**
	 * @brief draw draws the data, using the given renderer, the draw function must not mofiy the intern state, only draw stuff
	 * in order to modify the intern states, one must use the "update" function
	 * @param renderer the renderer to use to draw the objects on the screen
	 */
	virtual void draw(Renderer &renderer) const = 0;

	/**
	 * @brief onEnter function called when the state becomes the current state of the application,
	 * is used to init some data
	 * @param data data passed by the previous state (if any) can be null
	 */
	virtual void onEnter(BaseStateData *data) = 0;

	/**
	 * @brief onLeave function called when the states looses the focus to let another state enters
	 * this function is not the destructor, the state could be used another time during the app's lifetime
	 */
	virtual void onLeave() = 0;

	virtual ~State()
	{
	}

	/**
	 * @brief getApp reference to the client's ap
	 * @return  const reference to the client's app
	 */
	const ClientApp &getApp() const
	{
		return client;
	}

protected:

	/**
	 * @brief getApp non-const reference, for the sub-classes
	 * @return a reference to the client application
	 */
	ClientApp &getApp()
	{
		return client;
	}

private:
	/**
	 * @brief client reference to the client's app
	 */
	ClientApp &client;
};

#endif /* STATE_H */

