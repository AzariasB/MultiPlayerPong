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
 * File:   EventManager.h
 * Author: azarias
 *
 * Created on 21 octobre 2017, 12:18
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <functional>
#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>
#include <SFML/Config.hpp>

#include "Math.hpp"

/**
 * @brief The BaseEvent struct base object for an event, (used to
 * store it in an array)
 */
struct BaseEvent {

	virtual ~BaseEvent()
	{

	}
};

/**
 * @brief The EventFunc struct actual object used instead of the baseEvent
 * to store the function to call when an event is trigerred,
 * the template contains all the argument's types (it can be none),
 * so that the function that triggers the event can pass data
 * to all the listeners
 */
template <typename... Args>
struct EventFunc : BaseEvent {

	virtual ~EventFunc()
	{
	}

	/**
	 * @brief run is called when the function associated with the event is fired
	 * if the trigerrer passed some arguments when trigerred, the function "run"
	 * is called with these arguments
	 * @param argp the arguments to pass to the function
	 */
	virtual void run(Args... argp) = 0;
};

/**
 * @brief The EventFunctor struct contains only a simple function, this function
 * is called whenever the event is fired
 */
template <typename ...Args>
struct EventFunctor : EventFunc<Args...> {

	/**
	 * @brief EventFunctor constructor
	 * @param func the function to call whenever the event is fired
	 */
	EventFunctor(void (*func)(Args...)) :
	m_func(func)
	{
	}

	/**
	 * @brief run calls the simple function passed to the constructor
	 * @param argp
	 */
	void run(Args... argp) override
	{
		(*m_func)(argp...);
	}


	void (*m_func)(Args...);
};

/**
 * @brief The EventFunctorWithArg struct is the same as the EventFunctor,
 * but can have an argument passed in parameter to the constructor, so
 * the function can be called with this argument when the event is fired
 */
template<typename A, typename ...Args>
struct EventFunctorWithArg : EventFunc<Args...> {

	/**
	 * @brief EventFunctorWithArg constructor
	 * @param func the function to call
	 * @param arg the arg to use when calling the function
	 */
	EventFunctorWithArg(void (*func)(A, Args...), A arg) :
	m_func(func),
	m_arg(arg)
	{

	}

	/**
	 * @brief run runs the function with the given argument in parameter
	 * in the constructor, followed by the others arguments (if any)
	 * @param argp the other arguments
	 */
	void run(Args... argp) override
	{
		(*m_func)(m_arg, argp...);
	}


	void (*m_func)(A, Args...);
	A m_arg;
};

/**
 * @brief The EventMemberFunc struct stores a member method
 * and the object associated with it, so when an event is fired
 * the object's method is called
 */
template<typename T, typename ...Args>
struct EventMemberFunc : EventFunc<Args...> {

	/**
	 * @brief EventMemberFunc constructor
	 * @param func the member method
	 * @param obj the object containing the method
	 */
	EventMemberFunc(void(T::*func)(Args...), T* obj) :
	m_func(func),
	m_obj(obj)
	{

	}

	/**
	 * @brief run calls the object's method with the given arguments
	 * @param argp the arguments
	 */
	void run(Args... argp) override
	{
		(m_obj->*m_func)(argp...);
	}


	void(T::*m_func)(Args...);
	T* m_obj = 0;
};

/**
 * @brief The EventMemberFuncWithArg struct is the same as the eventMemberFunc struct
 * but is constructed with an additional argument used when calling the member
 * method
 */
template<typename T, typename A, typename ...Args>
struct EventMemberFuncWithArg : EventFunc<Args...> {

	/**
	 * @brief EventMemberFuncWithArg constructor
	 * @param func the member method
	 * @param obj the object containing the method
	 * @param arg the argument to use when calling the methdo
	 */
    EventMemberFuncWithArg(void(T::*func)(A, Args...), T*obj, A arg) :
	m_func(func),
	m_obj(obj),
    m_arg(arg)
	{

	}

	/**
	 * @brief run calls the object's method with the argument given in the constructor
	 * followed by the arguments in parameter
	 * @param argp the other arguments
	 */
	void run(Args... argp) override
	{
		(m_obj->*m_func)(m_arg, argp...);
	}


	void(T::*m_func)(A, Args...);
    T*m_obj;
    A m_arg;
};

/**
 * @brief The EventManager class used to store events and events listeners
 * to the call the expected functions when an event is fired
 */
class EventManager {
public:
	/**
	 * @brief EventManager constructor
	 */
	EventManager();

	/**
	 * Declares a code event. So every observers can subscribe for this event
	 * for when it's fired
	 * 
	 * @param eventCode
	 */
	sf::Uint64 nextEventCode();

	/**
	 * Just calls a function when an event is trigerred
	 * 
	 * @param eventCode the code of the event to listen to
	 * @param trigger the function to call when the event is fired
	 */
	template<typename ...Args>
    const std::string &declareListener(sf::Uint64 eventCode, void(*func)(Args...))
	{      
		assertEventCode(eventCode);
		m_observers[eventCode].emplace_back(new EventFunctor<Args...>(func));
        return addIterator(eventCode, math::uuid());
	}

	/**
	 * Calls an object's function when an event is trigerred
	 * 
	 * @param eventCode the code of the event to listen to
	 * @param trigger the function to call when the event is fired
	 */
	template<typename T, typename ...Args>
    const std::string &declareListener(sf::Uint64 eventCode, void (T::*func)(Args...), T* obj)
	{
		assertEventCode(eventCode);
        m_observers[eventCode].emplace_back(new EventMemberFunc<T, Args...>(func, obj));
        return addIterator(eventCode, math::uuid());
	}

	/**
	 * @brief declareListener stores an eventMemberFuncWithArg in the observers map, the
	 * function will be called when the event eventCode is fired
	 * @param func the member method
	 * @param eventCode the eventCode to listen for
	 * @param obj the object containing the method
	 * @param arg the additionnal argument
	 */
	template<typename T, typename A, typename ...Args>
    const std::string &declareListener(sf::Uint64 eventCode, void(T::*func)(A, Args&&...), T*obj, A arg)
	{
		assertEventCode(eventCode);
        m_observers[eventCode].emplace_back(new EventMemberFuncWithArg<T, A, Args&&...>(func, obj, arg));
        return addIterator(eventCode, math::uuid());
	}

    /**
     * @brief removeListener removes the given listeners, used when
     * one wants to stop listening for events
     * @param eventCode the code of the event to stop to listen to
     * @param iter the token given when creating the listener
     */
    void removeListener(const std::string &tokenUUID, const sf::Uint64 &eventCode);

	/**
	 * @brief trigger calls all the method listening for the given evCode,
	 * all the listeners will be called (in order of registering) with the provided
	 * arguments
	 * @param evCode the code of the event to fire
	 * @param argp all the arguments to pass to the listeners
	 */
	template<typename ...Args>
    void trigger(sf::Uint64 evCode, Args... argp)
	{
		assertEventCode(evCode);
        for(auto &it : m_observers[evCode]){
            EventFunc<Args...> &ef = static_cast<EventFunc<Args...>&>(*it);
            ef.run(argp...);
        }
	}

	virtual ~EventManager();
private:
	/**
	 * @brief assertEventCode asserts that the given code is between an existing range of event code
	 * @param evCode the event code to check
	 */
	void assertEventCode(sf::Uint64 evCode);

    /**
     * @brief last returns the last inserted element of the given observer list
     * @param evCode the event containing the list of events
     * @return the last element of the list
     */
    const std::string &addIterator(sf::Uint64 evCode, const std::string &uuid);

	/**
	 * @brief m_evCounter each event has it's own code, for each new
	 * request of event code, the event counter is incremented
	 */
	sf::Uint64 m_evCounter = 0;

	/**
	 * @brief m_observers all the observers
	 */
    std::unordered_map<sf::Uint64, std::list<BaseEvent*> > m_observers;

    /**
     * @brief m_tokens when creating an event listener, we create a UUID
     * and returns it, so the listener can later be removed using the given
     * token
     */
    std::unordered_map<std::string, std::list<BaseEvent*>::iterator> m_tokens;
};

#endif /* EVENTMANAGER_H */

