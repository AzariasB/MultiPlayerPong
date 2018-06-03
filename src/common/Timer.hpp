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
 * File:   Timer.hpp
 * Author: azarias
 *
 * Created on 3/6/2018
 */
#pragma once

#include <SFML/System/Time.hpp>
#include <functional>

namespace mp
{

class Timer
{
public:
    /**
     * @brief Timer constructor
     * @param totalTime the time it takes for this timer to complete
     * @param callback the function to call once this timer is over
     * @param repeat wether the timer must repeat itself once it ended (default = false)
     */
    Timer(const sf::Time &totalTime, const std::function<void()> callback = {}, bool repeat = false);

    /**
     * @brief update updates the timer
     * @param delta the time passed since last time
     */
    void update(const sf::Time &delta);

    /**
     * @brief setRepeat changes the repeat option of the timer
     * @param repeat wether the timer must repeats when finished
     */
    void setRepeat(bool repeat);

    /**
     * @brief setCallback changes the callback of thetimer
     * @param callback new callback to use (can be null)
     */
    void setCallback(const std::function<void()> callback);

    /**
     * @brief isRepeat getter for the repeat option of the timer
     * @return
     */
    bool isRepeat() const;

    /**
     * @brief totalTime time it takes to the timer to end
     * @return
     */
    const sf::Time &totalTime() const;

    /**
     * @brief remaining time remaining before the end of the timer
     * @return
     */
    const sf::Time &remaining() const;

private:
    /**
     * @brief m_time the current time of the timer
     * if it's under zero, the timer stops to update itself
     */
    sf::Time m_time;

    /**
     * @brief m_totalTime the total time of the timer
     */
    sf::Time m_totalTime;

    /**
     * @brief m_callback function to call (can be null)
     * when the timer ends
     */
    std::function<void()> m_callback;

    /**
     * @brief m_repeat if the timer must restart once
     * its done
     */
    bool m_repeat;
};


}
