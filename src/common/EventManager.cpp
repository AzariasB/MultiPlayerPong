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
    m_observers[++m_evCounter] = {};
    return m_evCounter;
}

EventManager::~EventManager()
{
    for(auto &lst : m_observers){
        for(auto &pair : lst.second){
            delete pair.second;
            pair.second = 0;
        }
    }
    m_observers.clear();
}

std::string EventManager::declareListener(sf::Uint64 eventCode, sf::Uint64 toTrigger)
{
    assertEventCode(eventCode);
    std::function<void()> func = [this,toTrigger](){
        this->trigger(toTrigger);
    };

    std::string uuid = math::uuid();

    m_observers[eventCode].emplace(uuid, new EventStdFunction<>(func));
    return uuid;
}

void EventManager::assertEventCode(sf::Uint64 evCode)
{
    if (evCode <= 0 || evCode > m_evCounter || m_observers.find(evCode) == m_observers.end())
        throw std::out_of_range("The given event code (" + std::to_string(evCode) + ") does not exist");
}

void EventManager::removeEvent(const sf::Uint64 &eventCode)
{
    assertEventCode(eventCode);
    for(auto &it : m_observers[eventCode]){
        delete it.second;
        it.second = 0;
    }
    m_observers.erase(eventCode);
}

void EventManager::removeListener(const std::string &tokenUUID, const sf::Uint64 &eventCode)
{
    auto observers = m_observers.find(eventCode);
    if(observers == m_observers.end()){
        std::out_of_range("The given event code (" + std::to_string(eventCode) + ") does not exist");
        return;
    }

    auto &map = (*observers).second;
    auto val = map.find(tokenUUID);
    if(val == map.end()){
        std::out_of_range("The given token uuid (" + tokenUUID + ") does not exist");
        return;
    }
    map.erase(val);
}

}
