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
 * File:   VectorsUtils.h
 * Author: azarias
 *
 * Created on 11 octobre 2017, 18:03
 */

#ifndef VECTORSUTILS_H
#define VECTORSUTILS_H

#include <SFML/Network/Packet.hpp>
#include <SFML/System/Vector2.hpp>
#include <complex>
#include <iosfwd>

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
template <
typename T,
typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type
>
sf::Vector2<T> normalized(const sf::Vector2<T> &v)
{
	std::complex<T> c = sqrt(v.x * v.x + v.y * v.y);
	if (c == static_cast<T> (0))return v;
	return sf::Vector2<T>(v.x / c.imag(), v.y / c.imag());
}

#endif /* VECTORSUTILS_H */

