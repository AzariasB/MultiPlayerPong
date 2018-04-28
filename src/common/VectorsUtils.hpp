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
 * File:   VectorsUtils.h
 * Author: azarias
 *
 * Created on 11 octobre 2017, 18:03
 */

#ifndef VECTORSUTILS_H
#define VECTORSUTILS_H

#include <SFML/Network/Packet.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <complex>
#include <iosfwd>
#include <unordered_map>
#include <Box2D/Common/b2Math.h>

#include "Math.hpp"


template<typename K, typename V, typename ...Args>
void deserialize(sf::Packet &packet, std::unordered_map<K,V> &mmap, Args&... argp)
{
    sf::Uint32 size;
    packet >> size;
    for(sf::Uint32 i = 0; i < size; ++i){
        V v(argp...);
        packet >> v;
        mmap.insert({v.getId(), v});
    }
}

template<typename K, typename V>
sf::Packet &operator>>(sf::Packet &packet, std::unordered_map<K,V> mmap)
{
    deserialize(packet, mmap);
    return packet;
}

template<typename K, typename V>
sf::Packet &operator<<(sf::Packet &packet, const std::unordered_map<K,V> mmap)
{
    sf::Uint32 mapSize = static_cast<sf::Uint32>(mmap.size());
    packet << mapSize;
    for(auto it = mmap.begin(); it != mmap.end(); ++it){
        packet << it->first;
        packet << it->second;
    }
    return packet;

}

/**
 * @brief deseralizeVector deseralizes a vector, but construct the elements
 * of the vectors with the given arguments
 * @param packet the packet to use to get the vector's data
 * @param vec the vector in which to deseralize
 * @param argp the argument neede to construct t
 */
template<typename T, typename...Args>
void deseralizeVector(sf::Packet &packet, std::vector<T> &vec, Args&... argp)
{
    sf::Uint32 vecSize;
    packet >> vecSize;
    vec.reserve(vecSize);
    for(int i = 0; i < vecSize; ++i){
        vec.emplace_back(argp...);
        packet >> vec.back();
    }
}


/**
 * @brief operator << serializes a box2d vector
 * @param vec the vector to deserialize
 * @return
 */
inline sf::Packet &operator<<(sf::Packet& packet, const  b2Vec2 &vec)
{
    return packet << vec.x << vec.y;
}

/**
 * @brief operator >> deserializes a vector
 * @param p the packet
 * @param vec the vector
 * @return
 */
inline sf::Packet &operator>>(sf::Packet &packet, b2Vec2 &vec)
{
    return packet >> vec.x >> vec.y;
}

/**
 * @brief operator << serializes the given vector to a packet
 * @param packet the packet in which to serialize
 * @param vec the vector to deseralize
 * @return the packet containing the derliazed vector
 */
template<typename T>
sf::Packet &operator<<(sf::Packet &packet, const std::vector<T> &vec)
{
    packet << static_cast<sf::Uint32>(vec.size());
    for(auto it = vec.cbegin(); it != vec.cend(); ++it)
    {
        packet << *it;
    }
    return packet;
}

/**
 * @brief operator >> deserializes a vector, can only be used
 * when the constructor does not need any arguments
 * @param packet the packet to use to deserliaze
 * @param vec the vector in which to deserialize
 * @return the packet
 */
template<typename T>
sf::Packet &operator>>(sf::Packet &packet, std::vector<T> &vec)
{
    sf::Uint32 vecSize;
    packet >> vecSize;
    vec.reserve(vecSize);
    for(sf::Uint32 i = 0; i < vecSize; ++i){
        T temp;
        packet >> temp;
        vec.push_back(temp);
    }
    return packet;
}

/**
 * @brief operator << serializes any type of rect
 * @param packet the packet in which to seralize
 * @param rect the rectangle to serialize
 * @return
 */
template<typename T>
sf::Packet &operator<<(sf::Packet &packet, const sf::Rect<T> &rect)
{
    return packet << rect.left << rect.top << rect.width << rect.height;
}

/**
 * @brief operator >> deszeralizes any type of rect
 * @param packet the packet to use
 * @param rect the target
 * @return
 */
template<typename T>
sf::Packet &operator>>(sf::Packet &packet, sf::Rect<T> &rect)
{
    return packet >> rect.left >> rect.top >> rect.width >> rect.height;
}

/**
 * @brief operator << serializes any type of vector
 * @param packet the packet in which to serialize
 * @param v the vector to serialize
 * @return the packet containing the serialized vector
 */
template <typename T>
sf::Packet &operator<<(sf::Packet &packet, const sf::Vector2<T> &v)
{
    return packet << v.x << v.y;
}

/**
 * @brief operator >> deserializes the vector
 * @param packet the packet from which to get the data
 * @param v the vector in which to deserialize
 * @return the packet with the deserialized vector
 */
template <typename T>
sf::Packet &operator>>(sf::Packet &packet, sf::Vector2<T> &v)
{
    return packet >> v.x >> v.y;
}

/**
 * @brief operator << used for debugging : shows the vector coordinates
 * @param os the output stream
 * @param v the vector to show
 * @return
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, const sf::Vector2<T> &v)
{
    return os << "(x:" << v.x << ",y:" << v.y << ")";
}

/**
 * @brief normalized returns the normalized vector, works for any type
 * of vector containing an arithmetic type
 * @param v a const reference of the vector to normalize
 * @return the normalized version of the vector
 */
template <typename T>
typename std::enable_if<std::is_integral<T>::value, sf::Vector2<T>>::type
normalized(const sf::Vector2<T> &v)
{
    std::complex<T> c = sqrt(v.x * v.x + v.y * v.y);
    if (c == static_cast<T> (0))return v;
    return sf::Vector2<T>(v.x / c.imag(), v.y / c.imag());
}

/**
 * @brief b2VecToSfVect interface between
 * box2d vector and sfml vector
 * @param vec
 * @return
 */
inline sf::Vector2f b2VecToSfVect(const b2Vec2 &vec)
{
    return sf::Vector2f(vec.x, vec.y);
}

inline b2Vec2 sfVecTob2Vec(const sf::Vector2f &vec, bool convertToMeters = true)
{
    if(convertToMeters)
        return b2Vec2(math::pixToMeters(vec.x), math::pixToMeters(vec.y));
    return b2Vec2(vec.x, vec.y);
}

#endif /* VECTORSUTILS_H */

