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

template<typename ...Args>
class Signal
{
public:
    Signal()
    {}

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

    void add(Signal<Args...> &other, sf::Int64 listens = -1)
    {
        std::function<void(Args...)> listener = [&other](Args ...argp){
              other.trigger(argp...);
        };
        m_listeners.emplace_back(listener, listens);
    }

    void add(const std::function<void(Args...)> listener, sf::Int64 listens = -1)
    {
        m_listeners.emplace_back(listener, listens);
    }

    void addOnce(const std::function<void(Args...)> listener)
    {
        m_listeners.emplace_back(listener, 0);
    }

private:
    struct Listener {

        Listener(const std::function<void(Args...)> f, sf::Int64 calls):
            func(f),
            maxCalls(calls)
        {}

        std::function<void(Args...)> func;
        sf::Int64 maxCalls = -1;
    };


    std::vector<Listener> m_listeners;
};

}


