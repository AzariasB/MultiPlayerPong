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
 * File:   ResourcesManager.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:08
 */

#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
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
     * @brief registerShader saves the shader in memory, making it available at runtime
     * @param filename the name of the file where to find the shader
     * @param shaderName the name of the shader to use in the program
     * @return the created shader
     */
    sf::Shader &registerShader(const std::string &filename, const std::string &shaderName);

	/**
	 * @brief getSound returns the sound associated with the name given when registered
	 * @param soundName name of the sound
	 * @return sound associated with the name, reference to the empty_sound object if not found
	 */
	sf::Sound &getSound(const std::string &soundName);

    /**
     * @brief getTexture the texture with the given name
     * @param textureName name of the texture
     * @return a reference to the texture reserved with
     * the given name
     */
	const sf::Texture &getTexture(const std::string &textureName) const;

    /**
     * @brief getShader access to the shader with the given name
     * @param shaderName name of the shader
     * @return  reference to the shader saved with the given name
     */
    sf::Shader &getShader(const std::string &shaderName);

	/**
	 * @brief getFont the font for the game
	 * @return the game's font
	 */
	const sf::Font &getFont() const
	{
        return mQuicksandFont;
	}

private:
    /**
     * @brief mQuicksandFont font used
     * for 'small' texts
     */
    sf::Font mQuicksandFont;

    /**
     * @brief m_uncompressedQuicksandFont uncompressed quicksand font
     */
    QResource m_uncompressedQuicksandFont;
	
	/**
	 * @brief m_emptySound empty sound used when an unkonw sound is requested
	 */
	sf::Sound m_emptySound;

    /**
     * @brief m_emptyShader empty shader used when an unknwon shader is requested
     */
    sf::Shader m_emptyShader;

	/**
	 * @brief m_emptyTexture empty texture used when an unknown texture is requested
	 */
	const sf::Texture m_emptyTexture;

	/**
	 * @brief m_sounds keep all the soundbuffer and their sound in memory
	 */
	std::unordered_map<std::string, std::unique_ptr<std::pair<sf::SoundBuffer, sf::Sound>> >m_sounds;

    /**
     * @brief m_textures keep all the texture in memory
     */
	std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;

    std::unordered_map<std::string, sf::Shader> m_shaders;
};



