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
 * File:   Timer.cpp
 * Author: azarias
 *
 * Created on 3/6/2018
 */
#include "Timer.hpp"

namespace mp
{

Timer::Timer(const sf::Time &totalTime, bool repeat, const std::function<void()> callback):
    m_time(totalTime),
    m_totalTime(totalTime),
    m_callback(callback),
    m_repeat(repeat)
{
}

void Timer::setTime(const sf::Time &time)
{
    m_totalTime = time;
}

void Timer::trigger()
{
    if(m_callback)m_callback();
}

void Timer::restart()
{
    m_time = m_totalTime;
}

void Timer::update(const sf::Time &delta)
{
    if(m_time <= sf::Time::Zero)return;

    m_time -= delta;
    if(m_time <= sf::Time::Zero){
        if(m_callback) m_callback();
        if(m_repeat) m_time = m_totalTime;
    }
}

void Timer::setCallback(const std::function<void ()> callback)
{
    m_callback = callback;
}

void Timer::setRepeat(bool repeat)
{
    m_repeat = repeat;
}

bool Timer::isRepeat() const
{
    return m_repeat;
}

const sf::Time &Timer::remaining() const
{
    return m_time;
}

const sf::Time &Timer::totalTime() const
{
    return m_totalTime;
}

}
