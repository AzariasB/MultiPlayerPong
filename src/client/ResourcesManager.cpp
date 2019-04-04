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
 * File:   ResourcesManager.cpp
 * Author: azarias
 *
 * Created on 16 octobre 2017, 22:08
 */

#include "ResourcesManager.hpp"
#include "Assets.hpp"
#include <QResource>

namespace mp {

ResourcesManager::ResourcesManager():
    m_uncompressedQuicksandFont(":/fonts/caveatbrushregular.ttf")
{

    for(const auto &p: Assets::animations) registerTexture(p.second, p.first);

    for(const auto &p : Assets::atlases) registerTexture(p.second, p.first);

    for(const auto &p: Assets::sounds)registerSound(p.second, p.first);

    for(const auto &p : Assets::icons) registerTexture(p.second, p.first);

    for(const auto &s : Assets::shaders) registerShader(s.second, s.first);

    for(const auto &m : Assets::musics) registerMusic(m.second, m.first);

    if(!m_quicksandfont.loadFromMemory(m_uncompressedQuicksandFont.data(), m_uncompressedQuicksandFont.size())){
        std::cerr << "Fail to load Whatever it takes font\n";
        exit(-1);
    }
}

//--------------
// GETTER
//--------------

sf::Sound &ResourcesManager::get(const Assets::Sounds &soundId)
{
    auto found = m_sounds.find(soundId);
    if (found != m_sounds.end()) {
        return found->second.second;
    } else {
        std::cerr << "Could not find the sound '" << soundId << "' you asked for\n";
        return m_emptySound;
    }
}

sf::MemoryInputStream &ResourcesManager::get(const Assets::Musics &musicId)
{
    int rand = static_cast<int>(std::rand()) % m_musics.size();
    auto item = m_musics.begin();
    std::advance(item, rand);
    return item->second;
}

sf::Shader* ResourcesManager::get(const Assets::Shaders &shaderId) const
{
    auto found = m_shadersContent.find(shaderId);
    auto shader = new sf::Shader;
    if(found == m_shadersContent.end()) return shader;
    sf::MemoryInputStream data = found->second;// needs to be copied to call 'load from stream'
    shader->loadFromStream(data, sf::Shader::Fragment);
    return shader;
}

const sf::Texture &ResourcesManager::get(const Assets::Animations &animadionId) const
{
    return getTexture(animadionId);
}

const sf::Texture &ResourcesManager::get(const Assets::Icons &iconId) const
{
    return getTexture(iconId);
}

const sf::Texture &ResourcesManager::get(const Assets::IconAtlas::Holder &holder) const
{
    return getTexture(holder.textureId);
}

const sf::Font &ResourcesManager::get(const Assets::Fonts &) const
{
    return m_quicksandfont;
}

const sf::Texture &ResourcesManager::getTexture(const sf::Uint64 &textureId) const
{
    auto found = m_textures.find(textureId);
    if(found != m_textures.end()){
        return found->second;
    }else{
        std::cerr << "Could not find the texture '" << textureId << "' you asked for\n";
        return m_emptyTexture;
    }
}

//--------------
// REGISTER
//--------------
void ResourcesManager::registerMusic(const std::string &filename, const Assets::Musics &musicId)
{
    QResource sRes(filename.c_str());

    sf::MemoryInputStream mis;
    mis.open(sRes.data(), sRes.size());
    m_musics[musicId] = mis;
}

void ResourcesManager::registerShader(const std::string &filename, const Assets::Shaders &shaderId)
{
    QResource sRes(filename.c_str());

    sf::MemoryInputStream mis;
    mis.open(sRes.data(), sRes.size());
    m_shadersContent[shaderId] = mis;
}



void ResourcesManager::registerSound(const std::string& filename, const Assets::Sounds& soundId)
{
    QResource res(filename.c_str());
    m_sounds[soundId].first.loadFromMemory(res.data(), res.size());
    m_sounds[soundId].second.setBuffer(m_sounds[soundId].first);
}

void ResourcesManager::registerTexture(const std::string &filename, const sf::Uint64 &textureID)
{
    QResource res(filename.c_str());

    if(res.isCompressed()){
        QByteArray arr = qUncompress(res.data(), res.size());
        if(!m_textures[textureID].loadFromMemory(arr.data(), arr.size())){
            std::cerr << "Failed to load texture " << textureID << "\n";
        }
    }else{
        if(!m_textures[textureID].loadFromMemory(res.data(), res.size())){
            std::cerr << "Failed to load texture " << textureID << "\n";
        }
    }
}

ResourcesManager::~ResourcesManager() {
    m_sounds.clear();
}

}
