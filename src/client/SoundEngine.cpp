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
 * File:   SoundEngine.cpp
 * Author: azarias
 * 
 * Created on 21 octobre 2017, 11:49
 */

#include "SoundEngine.hpp"
#include <iostream>

SoundEngine::SoundEngine(ResourcesManager& sManager) :
m_manager(sManager)
{

}

void SoundEngine::playSound(SOUND_TYPE s)
{
	if(m_isMuted)return;
	sf::Sound &sound = m_manager.getSound(toSoundName(s));
	sound.play();
}

void SoundEngine::saveSound(SOUND_TYPE s, const std::string& filename)
{
	m_manager.registerSound(filename, toSoundName(s));
}

std::string SoundEngine::toSoundName(SOUND_TYPE st)
{
	return "sound_" + std::to_string(static_cast<int> (st));
}

SoundEngine::~SoundEngine()
{
}

