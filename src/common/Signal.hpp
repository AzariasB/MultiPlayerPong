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
 * File:   Signal.hpp
 * Author: azarias
 *
 * Created on 26/6/2018
 */

#pragma once

#include <vector>
#include <functional>
#include <SFML/Config.hpp>

namespace  mp {

/**
 * @brief The Signal class used as an observer
 * must be stored in the class that will emit an event
 * the classes that wants to listen for any events from this
 * signal must call the 'add' function
 * when the owner class triggers this signal, all the
 * listening classes will be trigerred
 */
template<typename ...Args>
class Signal
{
public:
    Signal()
    {}

    /**
     * @brief trigger function that will call all the listener of this signal
     * each listener has a number of listening, if this number is -1,
     * the number of listening is considered as inifinite, otherwise, this number
     * is decremented, and when it reaches 0 the listener is not notified anymore
     * @param argp all the argument to provide to the listeners
     */
    void trigger(Args ...argp)
    {
        for(auto it = m_listeners.begin(); it != m_listeners.end();){
            if (it->maxCalls == 0){
                it = m_listeners.erase(it);
            } else {
                it->func(argp...);
                if (it->maxCalls > -1) it->maxCalls--;
                ++it;
            }
        }
    }

    /**
     * @brief add adds a signal with the same arguments needed to the list
     * of listeners
     * @param other the signal to trigger when this signal is triggered
     * @param listens the max number of listens for this signal
     * @return itself
     */
    Signal &add(Signal<Args...> &other, sf::Int64 listens = -1)
    {
        std::function<void(Args...)> listener = [&other](Args ...argp){
              other.trigger(argp...);
        };
        m_listeners.emplace_back(listener, listens);

        return *this;
    }

    /**
     * @brief add adds a function to the list of listeners, with the given
     * number of listens (defaults = -1)
     * @param listener function to call when the signal is trigerred
     * @param listens the number max of listens
     * @return itself
     */
    Signal &add(const std::function<void(Args...)> listener, sf::Int64 listens = -1)
    {
        m_listeners.emplace_back(listener, listens);

        return *this;
    }

    /**
     * @brief addOnce adds a function that will be only trigerred the first
     * time the signal is trigerred
     * @param listener the function to call the first time the signal is trigerred
     * @return itself
     */
    Signal &addOnce(const std::function<void(Args...)> listener)
    {
        m_listeners.emplace_back(listener, 1);

        return *this;
    }

    /**
     * @brief clear removes all the listeners
     */
    void clear()
    {
        m_listeners.clear();
    }

private:
    /**
     * @brief The Listener struct
     * struct used to store the listener function
     * and the remaning number of calls for himself
     */
    struct Listener {

        Listener(const std::function<void(Args...)> f, sf::Int64 calls):
            func(f),
            maxCalls(calls)
        {}

        /**
         * @brief func function to call
         */
        std::function<void(Args...)> func;

        /**
         * @brief maxCalls maximum number of calls
         */
        sf::Int64 maxCalls = -1;
    };

    /**
     * @brief m_listeners all the listeners of this signal
     * these will be called when the signal itself is trigerred
     */
    std::vector<Listener> m_listeners;
};

}


