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

#pragma once


#include <unordered_map>
#include <list>
#include <memory>
#include <iostream>
#include <SFML/Config.hpp>

#include "Math.hpp"
#include "FunctionalUtils.hpp"


namespace mp {
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

template <typename ...Args>
struct EventStdFunction : EventFunc<Args...> {

    EventStdFunction(const std::function<void(Args...)> &callback):
    m_callback(callback){

    }

    void run(Args... argp) override
    {
        if(m_callback)m_callback(argp...);
    }

    std::function<void(Args...)> m_callback;
};

template<typename ...Args>
EventStdFunction<Args...> *makeStdFunction(const std::function<void(Args...)> &callback)
{
    return new EventStdFunction<Args...>(callback);
}

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
     * @brief declareListener used to cascade signal, when the given event code
     * is trigerred, the "toTrigger" event code will then be triggerred
     * @param eventCode the event code to listen to
     * @param toTrigger the event code to trigger when the first one is trigerred
     * @return the UUID of the event listener
     */
    const std::string &declareListener(sf::Uint64 eventCode, sf::Uint64 toTrigger);

    /**
     * Just calls a function when an event is trigerred
     *
     * @param eventCode the code of the event to listen to
     * @param trigger the function to call when the event is fired
     */
    template<typename CLOSURE>
    const std::string &declareListener(sf::Uint64 eventCode, const CLOSURE &lambda)
    {
        auto func = to_f(lambda);
        assertEventCode(eventCode);

        m_observers[eventCode].emplace_back(makeStdFunction(func));
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

}
