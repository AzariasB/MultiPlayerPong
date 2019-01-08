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
// REGISTER
//--------------
void ResourcesManager::registerMusic(const std::string &filename, const sf::Uint64 &musicId)
{
    QResource sRes(filename.c_str());

    sf::MemoryInputStream mis;
    mis.open(sRes.data(), sRes.size());
    m_musics[musicId] = mis;
}

void ResourcesManager::registerShader(const std::string &filename, const sf::Uint64 &shaderId)
{
    QResource sRes(filename.c_str());

    sf::MemoryInputStream mis;
    mis.open(sRes.data(), sRes.size());
    m_shadersContent[shaderId] = mis;
}



void ResourcesManager::registerSound(const std::string& filename, const sf::Uint64& soundId)
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
