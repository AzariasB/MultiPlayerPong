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
 * File:   SoundEngine.h
 * Author: azarias
 *
 * Created on 21 octobre 2017, 11:49
 */

#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "ResourcesManager.hpp"


class ResourcesManager;

/**
 * @brief The SoundEngine class used to ease access to sound/music
 * and to play it easily during the game is happening (instead of using
 * the resource manager)
 */
class SoundEngine {
public:

	/**
	 * @brief The SOUND_TYPE enum all the possible sound the soundEngine can play
	 */
	enum SOUND_TYPE {
		BOUNCE
	};

	/**
	 * @brief SoundEngine constructor
	 * @param sManager a reference to the resourceManager in order to save the sound resources
	 */
	SoundEngine(ResourcesManager &sManager);

	/**
	 * @brief saveSound saves the sound of the given type, with the given filename to read from
	 * @param s the type of the sound to save
	 * @param filename the filename to use for this sound type
	 */
	void saveSound(SOUND_TYPE s, const std::string &filename);

	/**
	 * @brief playSound plays the given sound's type
	 * @param s the type of the sound to play
	 */
	void playSound(SOUND_TYPE s);

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
	 * @brief toSoundName turns the given sound type into a string in order to save it in the resource manager
	 * @param st sound type to turn into a string
	 * @return the sound type turned into a string
	 */
	std::string toSoundName(SOUND_TYPE st);

	/**
	 * @brief m_manager reference to the resource manager,  to save the sound resources
	 */
	ResourcesManager &m_manager;

	/**
	 * @brief isMuted wether the game's sound is muted
	 */
	bool m_isMuted = false;
};

#endif /* SOUNDENGINE_H */

