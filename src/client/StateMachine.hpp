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
 * File:   StateMachine.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 19:04
 */

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <SFML/System/NonCopyable.hpp>
#include <unordered_map>

#include "State.hpp"
class ClientApp;

/**
 * @brief The StateMachine class class that holds all the different possible states
 * of the application. it will also handle the states changes
 */
class StateMachine : public sf::NonCopyable {
public:
	/**
	 * @brief StateMachine constructor
	 */
    StateMachine();

	/**
	 * @brief addState adds the state given as template parameter to the list of states (creates a new state object)
	 * @param stateLabel the id for the inserted state, will be used to retreive the state later
	 */
	template<typename T>
	void addState(int stateLabel)
	{
		static_assert(std::is_base_of<State, T>::value, "T must extend State");
        states[stateLabel] = std::make_unique<T>();
    }

	/**
	 * @brief setCurrentState changes the current state, calls onLeave and onEnter for the current state and the new state
	 * @param stateLabel id of the label to set, if the id is not in the bound of the known states, throws an error
	 */
	void setCurrentState(int stateLabel);

	/**
	 * @brief setCurrentState sets the current state, and passes some data to the entering state
	 * @param stateLabel id of the label to set
	 * @param data data to pass to the entering state
	 */
	template<typename T>
	void setCurrentState(int stateLabel, const T &data)
	{
	    if (currentStateIndex > -1)
		states[currentStateIndex]->onLeave();
	    currentStateIndex = stateLabel;

	    StateData<T> dat(data);
	    states[currentStateIndex]->onEnter(&dat);
	}

	/**
	 * @brief getCurrentState a reference to the current state
	 * @return a reference to the current state
	 */
	State &getCurrentState()
	{
		if (currentStateIndex < 0)throw std::out_of_range("The current state index is not set");
		return *states[currentStateIndex];
	}

    State &getStateAt(int index)
    {
        if(states.find(index) == states.end())
            throw std::out_of_range("Index not found");

        return *states[index];
    }

	/**
	 * @brief getCurrentStateIndex the index of the current state (-1 if no states was set)
	 * @return the index of the current state (-1 if no states was set)
	 */
	int getCurrentStateIndex()
	{
		return currentStateIndex;
	}

	virtual ~StateMachine();
private:
	/**
	 * @brief states keep in memory all the newly created states
	 * using smart pointers in order to delete them when getting out of scope
	 */
	std::unordered_map<int, std::unique_ptr<State>> states;

	/**
	 * @brief currentStateIndex index of the current state
	 */
	int currentStateIndex = -1;

};

#endif /* STATEMACHINE_H */

