
/* 
 * File:   Math.h
 * Author: azarias
 *
 * Created on 8 octobre 2017, 19:29
 */

#ifndef MATH_H
#define MATH_H

#include <SFML/System/Vector2.hpp>
#include <Box2D/Common/b2Math.h>

//Meters to pixel ratio
#define M_TO_P 120.f

/**
 * @brief rand rand value between the given bounds
 * @param min the min possible value
 * @param max the max possible value
 * @return a pseudo-random value between the given bounds
 */
inline int rrand(int min, int max)
{
    return (rand() % (max -min + 1)) + min;
}

/**
 * @brief clampf floating clamp, returns value if value is between min and max, min if the value is less than min
 * max if value is more than max
 * @param min the min value
 * @param max the max value
 * @param val the value to evaluate
 * @return
 */
inline float clampf(float min, float max, float val)
{
	return val < min ? min : val > max ? max : val;
}

/**
 * @brief clampi integer clamp, the same of clampf, for the ints
 * @param min min value
 * @param max max value
 * @param val value to evaluate
 * @return
 */
inline int clampi(int min, int max, int val)
{
	return val < min ? min : val > max ? max : val;
}

/**
 * @brief sign returns the sign of the floating number
 * @param f the number
 * @return -1 if the number is less than 0, 1 otherwise
 */
inline int sign(float f)
{
	return f < 0 ? -1 : 1;
}

/**
 * @brief normalize normalizes the given vector
 * @param orig the original vector
 * @return the normalized vector
 */
inline sf::Vector2f normalize(const sf::Vector2f &orig)
{
	float length = sqrtf((orig.x * orig.x) + (orig.y * orig.y));
	if (length != 0)
		return sf::Vector2f(orig.x / length, orig.y / length);
	else
		return orig;
}


inline float pixToMeters(int pixels)
{
    return pixels/M_TO_P;
}

inline int metersToPix(float meters)
{
    return static_cast<int>(meters*M_TO_P);
}

#endif /* MATH_H */

