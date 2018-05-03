
/* 
 * File:   Math.h
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
const std::string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

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

/**
 * @brief clampf floating clamp, returns value if value is between min and max, min if the value is less than min
 * max if value is more than max
 * @param min the min value
 * @param max the max value
 * @param val the value to evaluate
 * @return
 */
template<typename T>
T clampf(T min, T max, T val)
{
    return val < min ? min : val > max ? max : val;
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
