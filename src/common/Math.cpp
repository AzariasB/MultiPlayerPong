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
 * File:   Math.cpp
 * Author: azarias
 *
 * Created on 15/3/2018
 */

#include "Math.hpp"

namespace mp {

std::string math::uuid()
{
    std::string uuid = std::string(36,' ');
    uuid[8] = '-';
    uuid[13] = '-';
    uuid[18] = '-';
    uuid[23] = '-';

    uuid[14] = '4';

    for(std::size_t i=0;i<36;i++){
        if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23) {
            uuid[i] = math::CHARS[std::rand() % math::CHARS.size()];
        }
    }
    return uuid;
}


int math::rrand(int min, int max)
{
    return (rand() % (max -min + 1)) + min;
}


int math::sign(float f)
{
    return f < 0 ? -1 : 1;
}

float math::length(const sf::Vector3f &orig)
{
    return sqrtf((orig.x * orig.x) + (orig.y * orig.y) + (orig.z * orig.z));
}

sf::Vector2f math::normalize(const sf::Vector2f &orig)
{
    float length = sqrtf((orig.x * orig.x) + (orig.y * orig.y));
    if (length != 0.f)
        return sf::Vector2f(orig.x / length, orig.y / length);
    else
        return orig;
}

float math::pixToMeters(int pixels)
{
    return pixels/M_TO_P;
}

int math::metersToPix(float meters)
{
    return static_cast<int>(meters*M_TO_P);
}

}
