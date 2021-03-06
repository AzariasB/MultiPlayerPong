/*
 * The MIT License
 *
 * Copyright 2017-2019 azarias.
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
 * File:   SoundEngine.cpp
 * Author: azarias
 *
 * Created on 21 octobre 2017, 11:49
 */

#include "SoundEngine.hpp"
#include "src/common/Math.hpp"
#include <iostream>

namespace mp {

SoundEngine::SoundEngine(ResourcesManager& sManager) :
    m_manager(sManager)
{

}

void SoundEngine::update(const sf::Time&)
{
    if(m_music.getStatus() == sf::Music::Status::Stopped && !m_isMusicMuted)
    {
        startMusic();
    }
}

void SoundEngine::playSound(Assets::Sounds s, const sf::Vector3f &position)
{
    if(m_isSoundMuted)return;
    sf::Sound &sound = m_manager.get(s);


    sound.setRelativeToListener(math::length(position) != 0.f);
    sound.setPosition(position);

    sound.play();
}

void SoundEngine::startMusic()
{
    m_isMusicMuted = false;
    m_music.stop();
    m_music.openFromStream(m_manager.get(Assets::Music1));
    m_music.play();
}

bool SoundEngine::isMusicStoped() const
{
    return m_isMusicMuted;
}

void SoundEngine::stopMusic()
{
    m_music.stop();
    m_isMusicMuted = true;
}


SoundEngine::~SoundEngine()
{
}

}
