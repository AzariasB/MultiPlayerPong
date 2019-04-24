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
 * File:   Math.hpp
 * Author: azarias
 *
 * Created on 8 octobre 2017, 19:29
 */

#pragma once


#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <Box2D/Common/b2Math.h>
#include <string>
#include <cstdlib>

namespace mp {

//Meters to pixel ratio
constexpr float M_TO_P = 64.f;
constexpr float P_TO_M = 1/M_TO_P;

/**
 * @brief CHARS used to generated UUID
 */
namespace math{

/**
 * @brief CHARS used to generate the UUID
 */
const std::string CHARS = "0123456789abcdef";

/**
 * @brief uuid universal unique identifier implementation
 * @return an UUID
 */
std::string uuid();

/**
 * @brief rand rand value between the given bounds
 * @param min the min possible value
 * @param max the max possible value
 * @return a pseudo-random value between the given bounds
 */
int rrand(int min, int max);

template<typename T>
T &centerOrigin(T& ref)
{
    auto bounds = ref.getGlobalBounds();
    ref.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    return ref;
}

/**
 * @brief sign returns the sign of the floating number
 * @param f the number
 * @return -1 if the number is less than 0, 1 otherwise
 */
int sign(float f);


/**
 * @brief normalize normalizes the given vector
 * @param orig the original vector
 * @return the normalized vector
 */
sf::Vector2f normalize(const sf::Vector2f &orig);

/**
 * @brief pixToMeters returns the position in meter of the given pixel
 * @param pixels the pixel index
 * @return the meters mesurement of the given pixel
 */
float pixToMeters(int pixels);

/**
 * @brief metersToPix used to convert from meters (box2d) to pixels(sfml)
 * @param meters the meters mesures
 * @return the equivalent pixel value
 */
int metersToPix(float meters);


/**
 * @brief length the lenght of the given vector3
 * @param orig the vector to calculate the length from
 * @return the length of this vector
 */
float length(const sf::Vector3f &orig);

}



}
