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
 * File:   EventManager.cpp
 * Author: azarias
 *
 * Created on 21 octobre 2017, 12:18
 */

#include "EventManager.hpp"

namespace mp {

EventManager::EventManager():
    m_evCounter(0)
{

}

sf::Uint64 EventManager::nextEventCode()
{
    m_observers.insert(std::make_pair(++m_evCounter, std::list<BaseEvent*>()));
    return m_evCounter;
}

EventManager::~EventManager()
{
    for(auto &lst : m_observers){
        for(auto *ptr: lst.second){
            delete ptr;
        }
    }
    m_observers.clear();
}

const std::string &EventManager::addIterator(sf::Uint64 evCode, const std::string &uuid)
{
    return (*m_tokens.insert(
                std::make_pair(uuid, std::prev(m_observers[evCode].end()))
                ).first/* iterator to pair */).first /* key */;
}

void EventManager::assertEventCode(sf::Uint64 evCode)
{
    if (evCode <= 0 || evCode > m_evCounter)
        throw std::out_of_range("The given event code (" + std::to_string(evCode) + ") is out of range");
}

void EventManager::removeListener(const std::string &tokenUUID, const sf::Uint64 &eventCode)
{
    if(m_tokens.find(tokenUUID) != m_tokens.end() &&
            m_observers.find(eventCode) != m_observers.end() &&
            m_observers[eventCode].size() > 0){
        std::list<BaseEvent*>::iterator listIt = m_tokens[tokenUUID];
        delete (*listIt);
        m_observers[eventCode].erase(listIt);
        m_tokens.erase(tokenUUID);
    }else{
        std::out_of_range("The given uuid (" + tokenUUID + ") does not exist");
    }
}

}
