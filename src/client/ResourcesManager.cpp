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
 * File:   ResourcesManager.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:08
 */

#include <iostream>
#include "ResourcesManager.hpp"
#include <QResource>
#include <SFML/System/MemoryInputStream.hpp>

ResourcesManager::ResourcesManager():
    m_uncompressedQuicksandFont(":/quicksand.otf")
{

    if(!mQuicksandFont.loadFromMemory(m_uncompressedQuicksandFont.data(), m_uncompressedQuicksandFont.size())){
        std::cerr << "Fail to load quicksand font\n";
        exit(-1);
    }
}

sf::Sound& ResourcesManager::getSound(const std::string& soundName) {
	if (m_sounds.find(soundName) != m_sounds.end()) {
		return m_sounds[soundName]->second;
	} else {
		std::cerr << "Could not find the sound '" << soundName << "' you asked for\n";
		return m_emptySound;
	}
}

sf::Shader &ResourcesManager::registerShader(const std::string &filename, const std::string &shaderName)
{
    QResource sRes(filename.c_str());

    sf::MemoryInputStream mis;
    mis.open(sRes.data(), sRes.size());

    sf::Shader &s = m_shaders[shaderName];
    s.loadFromStream(mis, sf::Shader::Fragment);
    return s;
}

sf::Shader &ResourcesManager::getShader(const std::string &shaderName)
{
    if(m_shaders.find(shaderName) != m_shaders.end()){
        return m_shaders[shaderName];
    }
    return m_emptyShader;
}


const sf::Texture &ResourcesManager::getTexture(const std::string &textureName) const
{
	if(m_textures.find(textureName) != m_textures.end()){
		return *m_textures.find(textureName)->second;
	}else{
		std::cerr << "Could not find the texture '" << textureName << "' you asked for\n";
		return m_emptyTexture;
	}
}

void ResourcesManager::registerSound(const std::string& filename, const std::string& soundName) {
	QResource res(filename.c_str());
	m_sounds[soundName] = std::make_unique<std::pair < sf::SoundBuffer, sf::Sound >> ();
	m_sounds[soundName]->first.loadFromMemory(res.data(), res.size());
	m_sounds[soundName]->second.setBuffer(m_sounds[soundName]->first);
}

void ResourcesManager::registerTexture(const std::string &filename, const std::string &textureName)
{
	QResource res(filename.c_str());
	m_textures[textureName] = std::make_unique<sf::Texture>();
	m_textures[textureName]->loadFromMemory(res.data(), res.size());
}

ResourcesManager::~ResourcesManager() {
	m_sounds.clear();
}

