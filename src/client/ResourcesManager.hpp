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
 * File:   ResourcesManager.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:08
 */

#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <unordered_map>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <memory>
#include <QResource>

/**
 * @brief The ResourcesManager class contains all the resources
 * necessary for the client (texture, sound, font)
 */
class ResourcesManager : public sf::NonCopyable {
public:
	/**
	 * @brief ResourcesManager constructor
	 */
	ResourcesManager();
	virtual ~ResourcesManager();

	/**
	 * @brief registerSound creates the soundbuffer and keep it in memory
	 * @param filename name of the file to read from
	 * @param soundName the name of the sound to register, so it can be retrieved later
	 */
	void registerSound(const std::string &filename, const std::string &soundName);

	/**
	 * @brief regsiterTexture saves a texture to the memroy
	 * @param filename the name of the file where the texture is located
	 * @param textureName name of the texture, to retreive it later
	 */
	void registerTexture(const std::string &filename, const std::string &textureName);

	/**
	 * @brief getSound returns the sound associated with the name given when registered
	 * @param soundName name of the sound
	 * @return sound associated with the name, reference to the empty_sound object if not found
	 */
	sf::Sound &getSound(const std::string &soundName);

	const sf::Texture &getTexture(const std::string &textureName) const;

	/**
	 * @brief getFont the font for the game
	 * @return the game's font
	 */
	const sf::Font &getFont() const
	{
		return gameFont;
	}

private:
	/**
	 * @brief gameFont font used for the whole game
	 */
	sf::Font gameFont;

	/**
	 * @brief m_uncompressedFont the uncompressed font
	 */
	QByteArray m_uncompressedFont;
	
	/**
	 * @brief m_emptySound empty sound used when an unkonw sound is requested
	 */
	sf::Sound m_emptySound;

	/**
	 * @brief m_emptyTexture empty texture used when an unknown texture is requested
	 */
	const sf::Texture m_emptyTexture;

	/**
	 * @brief m_sounds keep all the soundbuffer and their sound in memory
	 */
	std::unordered_map<std::string, std::unique_ptr<std::pair<sf::SoundBuffer, sf::Sound>> >m_sounds;

	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
};

#endif /* RESOURCESMANAGER_H */

