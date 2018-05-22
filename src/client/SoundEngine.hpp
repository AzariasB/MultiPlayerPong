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
 * File:   SoundEngine.h
 * Author: azarias
 *
 * Created on 21 octobre 2017, 11:49
 */

#pragma once

#include "Assets.hpp"
#include "ResourcesManager.hpp"

namespace mp {

class ResourcesManager;

/**
 * @brief The SoundEngine class used to ease access to sound/music
 * and to play it easily during the game is happening (instead of using
 * the resource manager)
 */
class SoundEngine {
public:
    /**
     * @brief SoundEngine constructor
     * @param sManager a reference to the resourceManager in order to save the sound resources
     */
    SoundEngine(ResourcesManager &sManager);

    /**
     * @brief playSound plays the given sound's type
     * @param s the type of the sound to play
     */
    void playSound(Assets::Sounds s, const sf::Vector3f &position = {0,0,0});


    void mute()
    {
        m_isMuted = true;
    }

    void unmute()
    {
        m_isMuted = false;
    }

    bool isMuted() const
    {
        return m_isMuted;
    }

    virtual ~SoundEngine();
private:


    /**
     * @brief m_manager reference to the resource manager,  to save the sound resources
     */
    ResourcesManager &m_manager;

    /**
     * @brief isMuted wether the game's sound is muted
     */
    bool m_isMuted = false;
};


}
