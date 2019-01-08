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
 * File:   ResourcesManager.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:08
 */

#pragma once


#include <iostream>
#include <type_traits>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/MemoryInputStream.hpp>
#include <unordered_map>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <memory>
#include <QResource>


namespace sf {
    class Shader;
}

namespace mp {
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

    template<typename RESOURCE>
    RESOURCE get(const sf::Uint64 & = 0);

    template<typename RESOURCE>
    RESOURCE get(const sf::Uint64 & = 0) const;


private:


    /**
     * @brief registerSound creates the soundbuffer and keep it in memory
     * @param filename name of the file to read from
     * @param soundName the name of the sound to register, so it can be retrieved later
     */
    void registerSound(const std::string &filename, const sf::Uint64 &soundId);

    /**
     * @brief regsiterTexture saves a texture to the memroy
     * @param filename the name of the file where the texture is located
     * @param textureName name of the texture, to retreive it later
     */
    void registerTexture(const std::string &filename, const sf::Uint64 &textureID);

    /**
     * @brief registerShader saves the shader in memory, making it available at runtime
     * @param filename the name of the file where to find the shader
     * @param shaderName the name of the shader to use in the program
     * @return the created shader
     */
    void registerShader(const std::string &filename, const sf::Uint64 &shaderId);

    /**
     * @brief registerMusic saves a music
     * @param filename name of the file where the music is located
     */
    void registerMusic(const std::string &filename, const sf::Uint64 &musicId);

    /**
     * @brief mQuicksandFont font used
     * for 'small' texts
     */
    sf::Font m_quicksandfont;

    /**
     * @brief m_uncompressedQuicksandFont uncompressed quicksand font
     */
    QResource m_uncompressedQuicksandFont;

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
    std::unordered_map<sf::Uint64, std::pair<sf::SoundBuffer, sf::Sound> >m_sounds;

    /**
     * @brief m_textures keep all the texture in memory
     */
    std::unordered_map<sf::Uint64, sf::Texture> m_textures;

    /**
     * @brief m_shaders keep all the shaders in memory
     */
    std::unordered_map<sf::Uint64, sf::MemoryInputStream> m_shadersContent;

    /**
     * @brief m_musics all the available musics for the game
     */
    std::unordered_map<sf::Uint64, sf::MemoryInputStream> m_musics;
};

//--------------
// GETTER
//--------------

template<>
inline sf::MemoryInputStream &ResourcesManager::get<sf::MemoryInputStream&>(const sf::Uint64&)
{
    int rand = static_cast<int>(std::rand()) % m_musics.size();
    auto item = m_musics.begin();
    std::advance(item, rand);
    return item->second;
}

template<>
inline sf::Sound& ResourcesManager::get<sf::Sound&>(const sf::Uint64& soundID) {
    if (m_sounds.find(soundID) != m_sounds.end()) {
        return m_sounds[soundID].second;
    } else {
        std::cerr << "Could not find the sound '" << soundID << "' you asked for\n";
        return m_emptySound;
    }
}

template<>
inline sf::Shader * ResourcesManager::get<sf::Shader*>(const sf::Uint64 &shaderId) const
{
    if(m_shadersContent.find(shaderId) != m_shadersContent.end()){
        sf::Shader *shader = new sf::Shader;
        sf::MemoryInputStream mis = m_shadersContent.find(shaderId)->second;
        shader->loadFromStream(mis, sf::Shader::Fragment);
        return shader;
    }
    return nullptr;
}

template<>
inline const sf::Texture &ResourcesManager::get<const sf::Texture&>(const sf::Uint64 &textureID) const
{
    auto found = m_textures.find(textureID);
    if(found != m_textures.end()){
        return m_textures.find(textureID)->second;
    }else{
        std::cerr << "Could not find the texture '" << textureID << "' you asked for\n";
        return m_emptyTexture;
    }
}

template<>
inline const sf::Font &ResourcesManager::get<const sf::Font&>(const sf::Uint64 &) const
{
    return m_quicksandfont;
}

}
