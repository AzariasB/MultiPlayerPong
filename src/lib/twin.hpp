
#pragma once

#include <cmath>
#include <type_traits>
#include <functional>
#include <SFML/System/Time.hpp>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace twin {

/**
 *This 'private' namespace
 * contains all the functions used
 * to perform the tweening, inspired from :
 */
/*
 Copyright (c) 2016-2017 Leonardo G. Lucena de Freitas
 Copyright (c) 2016 Guilherme R. Costa

 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 the Software, and to permit persons to whom the Software is furnished to do so,
 subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file easing.h
 * The purpose of this file is to list all bundled easings. All easings are based on Robert Penner's easing
 * functions: http://robertpenner.com/easing/
 */


namespace{
    /**
     * @ingroup linear
     * @brief Values change with constant speed.
     */
    template<typename T>
    static typename std::enable_if<std::is_integral<T>::value, T>::type linearImpl(float position, T start, T end) {
        return static_cast<T>(roundf((end - start) * position + start));
    }

    template<typename T>
    static typename std::enable_if<!std::is_integral<T>::value, T>::type linearImpl(float position, T start, T end) {
        return static_cast<T>((end - start) * position + start);
    }

     /**
      * @ingroup quadratic
      * @brief Accelerate initial values with a quadratic equation.
      */
    template<typename T>
    static T quadraticIn(float position, T start, T end) {
        return static_cast<T>((end - start) * position * position + start);
    }

    /**
      * @ingroup quadratic
      * @brief Deaccelerate ending values with a quadratic equation.
      */
    template<typename T>
    static T quadraticOut(float position, T start, T end) {
        return static_cast<T>((-(end - start)) * position * (position - 2) + start);
    }

    /**
      * @ingroup quadratic
      * @brief Acceelerate initial and deaccelerate ending values with a quadratic equation.
      */
    template<typename T>
    static T quadraticInOut(float position, T start, T end) {
        position *= 2;
        if (position < 1) {
            return static_cast<T>(((end - start) / 2) * position * position + start);
        }

        --position;
        return static_cast<T>((-(end - start) / 2) * (position * (position - 2) - 1) + start);
    }

    /**
      * @ingroup cubic
      * @brief Aaccelerate initial values with a cubic equation.
      */
    template<typename T>
    static T cubicInImpl(float position, T start, T end) {
        return static_cast<T>((end - start) * position * position * position + start);
    }

    /**
      * @ingroup cubic
      * @brief Deaccelerate ending values with a cubic equation.
      */
    template<typename T>
    static T cubicOutImpl(float position, T start, T end) {
        --position;
        return static_cast<T>((end - start) * (position * position * position + 1) + start);
    }

    /**
      * @ingroup cubic
      * @brief Acceelerate initial and deaccelerate ending values with a cubic equation.
      */
    template<typename T>
    static T cubicInOutImpl(float position, T start, T end) {
        position *= 2;
        if (position < 1) {
            return static_cast<T>(((end - start) / 2) * position * position * position + start);
        }
        position -= 2;
        return static_cast<T>(((end - start) / 2) * (position * position * position + 2) + start);
    }

    /**
      * @ingroup quartic
      * @brief Acceelerate initial values with a quartic equation.
      */
    template<typename T>
    static T quarticIn(float position, T start, T end) {
        return static_cast<T>((end - start) * position * position * position * position + start);
    }

    /**
      * @ingroup quartic
      * @brief Deaccelerate ending values with a quartic equation.
      */
    template<typename T>
    static T quarticOut(float position, T start, T end) {
        --position;
        return static_cast<T>( -(end - start) * (position * position * position * position - 1) + start);
    }

    /**
      * @ingroup quartic
      * @brief Acceelerate initial and deaccelerate ending values with a quartic equation.
      */
    template<typename T>
    static T quarticInOut(float position, T start, T end) {
        position *= 2;
        if (position < 1) {
            return static_cast<T>(((end - start) / 2) * (position * position * position * position) +
                                  start);
        }
        position -= 2;
        return static_cast<T>((-(end - start) / 2) * (position * position * position * position - 2) +
                              start);
    }

    /**
      * @ingroup quintic
      * @brief Acceelerate initial values with a quintic equation.
      */
    template<typename T>
    static T quinticIn(float position, T start, T end) {
        return static_cast<T>((end - start) * position * position * position * position * position + start);
    }

    /**
      * @ingroup quintic
      * @brief Deaccelerate ending values with a quintic equation.
      */
    template<typename T>
    static T quinticOut(float position, T start, T end) {
        position--;
        return static_cast<T>((end - start) * (position * position * position * position * position + 1) +
                              start);
    }

    /**
      * @ingroup quintic
      * @brief Acceelerate initial and deaccelerate ending values with a quintic equation.
      */
    template<typename T>
    static T quinticInOut(float position, T start, T end) {
        position *= 2;
        if (position < 1) {
            return static_cast<T>(
                ((end - start) / 2) * (position * position * position * position * position) +
                start);
        }
        position -= 2;
        return static_cast<T>(
            ((end - start) / 2) * (position * position * position * position * position + 2) +
            start);
    }

    /**
      * @ingroup sinusoidal
      * @brief Acceelerate initial values with a sinusoidal equation.
      */
    template<typename T>
    static T sinusoidalIn(float position, T start, T end) {
        return static_cast<T>(-(end - start) * cosf(position * static_cast<float>(M_PI) / 2) + (end - start) + start);
    }

    /**
      * @ingroup sinusoidal
      * @brief Deaccelerate ending values with a sinusoidal equation.
      */
    template<typename T>
    static T sinusoidalOut(float position, T start, T end) {
        return static_cast<T>((end - start) * sinf(position * static_cast<float>(M_PI) / 2) + start);
    }

    /**
      * @ingroup sinusoidal
      * @brief Acceelerate initial and deaccelerate ending values with a sinusoidal equation.
      */
    template<typename T>
    static T sinusoidalInOut(float position, T start, T end) {
        return static_cast<T>((-(end - start) / 2) * (cosf(position * static_cast<float>(M_PI)) - 1) + start);
    }

    /**
      * @ingroup exponential
      * @brief Acceelerate initial values with an exponential equation.
      */
    template<typename T>
    static T exponentialIn(float position, T start, T end) {
        return static_cast<T>((end - start) * powf(2, 10 * (position - 1)) + start);
    }

    /**
      * @ingroup exponential
      * @brief Deaccelerate ending values with an exponential equation.
      */
    template<typename T>
    static T exponentialOut(float position, T start, T end) {
        return static_cast<T>((end - start) * (-powf(2, -10 * position) + 1) + start);
    }

    /**
      * @ingroup exponential
      * @brief Acceelerate initial and deaccelerate ending values with an exponential equation.
      */
    template<typename T>
    static T exponentialInOut(float position, T start, T end) {
        position *= 2;
        if (position < 1) {
            return static_cast<T>(((end - start) / 2) * powf(2, 10 * (position - 1)) + start);
        }
        --position;
        return static_cast<T>(((end - start) / 2) * (-powf(2, -10 * position) + 2) + start);
    }

    /**
      * @ingroup circular
      * @brief Acceelerate initial values with a circular equation.
      */
    template<typename T>
    static T circularIn(float position, T start, T end) {
        return static_cast<T>( -(end - start) * (sqrtf(1 - position * position) - 1) + start );
    }

    /**
      * @ingroup circular
      * @brief Deaccelerate ending values with a circular equation.
      */
    template<typename T>
    static T circularOut(float position, T start, T end) {
        --position;
        return static_cast<T>((end - start) * (sqrtf(1 - position * position)) + start);
    }

    /**
      * @ingroup circular
      * @brief Acceelerate initial and deaccelerate ending values with a circular equation.
      */
    template<typename T>
    static T circularInOut(float position, T start, T end) {
        position *= 2;
        if (position < 1) {
            return static_cast<T>((-(end - start) / 2) * (sqrtf(1 - position * position) - 1) + start);
        }

        position -= 2;
        return static_cast<T>(((end - start) / 2) * (sqrtf(1 - position * position) + 1) + start);
    }

    /**
      * @ingroup bounce
      * @brief Deaccelerate ending values with a "bounce" equation.
      */
    template<typename T>
    static T bounceOutImpl(float position, T start, T end) {
        T c = end - start;
        if (position < (1 / 2.75f)) {
            return static_cast<T>(c * (7.5625f * position * position) + start);
        } else if (position < (2.0f / 2.75f)) {
            float postFix = position -= (1.5f / 2.75f);
            return static_cast<T>(c * (7.5625f * (postFix) * position + .75f) + start);
        } else if (position < (2.5f / 2.75f)) {
            float postFix = position -= (2.25f / 2.75f);
            return static_cast<T>(c * (7.5625f * (postFix) * position + .9375f) + start);
        } else {
            float postFix = position -= (2.625f / 2.75f);
            return static_cast<T>(c * (7.5625f * (postFix) * position + .984375f) + start);
        }
    }

    /**
      * @ingroup bounce
      * @brief Acceelerate initial values with a "bounce" equation.
      */
    template<typename T>
    static T bounceInImpl(float position, T start, T end) {
        return (end - start) - bounceOutImpl((1 - position), T(), end) + start;
    }

    /**
    * @ingroup bounce
    * @brief Acceelerate initial and deaccelerate ending values with a "bounce" equation.
    */
    template<typename T>
    static T bounceInOutImpl(float position, T start, T end) {
        if (position < 0.5f) return static_cast<T>(bounceInImpl(position * 2, T(), end) * .5f + start);
        else return static_cast<T>(bounceOutImpl((position * 2 - 1), T(), end) * .5f + (end - start) * .5f + start);
    }

    /**
      * @ingroup elastic
      * @brief Acceelerate initial values with an "elastic" equation.
      */
    template<typename T>
    static T elasticIn(float position, T start, T end) {
        if (position <= 0.00001f) return start;
        if (position >= 0.999f) return end;
        float p = .3f;
        float a = end - start;
        float s = p / 4;
        float postFix =
            a * powf(2, 10 * (position -= 1)); // this is a fix, again, with post-increment operators
        return static_cast<T>(-(postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p)) + start);
    }

    /**
      * @ingroup elastic
      * @brief Deaccelerate ending values with an "elastic" equation.
      */
    template<typename T>
    static T elasticOut(float position, T start, T end) {
        if (position <= 0.00001f) return start;
        if (position >= 0.999f) return end;
        float p = .3f;
        float a = end - start;
        float s = p / 4;
        return static_cast<T>(a * powf(2, -10 * position) * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p) + end);
    }

    /**
    * @ingroup elastic
    * @brief Acceelerate initial and deaccelerate ending values with an "elastic" equation.
    */
    template<typename T>
    static T elasticInOut(float position, T start, T end) {
        if (position <= 0.00001f) return start;
        if (position >= 0.999f) return end;
        position *= 2;
        float p = (.3f * 1.5f);
        float a = end - start;
        float s = p / 4;
        float postFix;

        if (position < 1) {
            postFix = a * powf(2, 10 * (position -= 1)); // postIncrement is evil
            return static_cast<T>(-0.5f * (postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p)) + start);
        }
        postFix = a * powf(2, -10 * (position -= 1)); // postIncrement is evil
        return static_cast<T>(postFix * sinf((position - s) * (2 * static_cast<float>(M_PI)) / p) * .5f + end);
    }

    /**
      * @ingroup back
      * @brief Acceelerate initial values with a "back" equation.
      */
    template<typename T>
    static T backInImpl(float position, T start, T end) {
        float s = 1.70158f;
        float postFix = position;
        return static_cast<T>((end - start) * (postFix) * position * ((s + 1) * position - s) + start);
    }

    /**
      * @ingroup back
      * @brief Deaccelerate ending values with a "back" equation.
      */
    template<typename T>
    static T backOutImpl(float position, T start, T end) {
        float s = 1.70158f;
        position -= 1;
        return static_cast<T>((end - start) * ((position) * position * ((s + 1) * position + s) + 1) + start);
    }

    /**
    * @ingroup back
    * @brief Acceelerate initial and deaccelerate ending values with a "back" equation.
    */
    template<typename T>
    static T backInOutImpl(float position, T start, T end) {
        float s = 1.70158f;
        float t = position;
        T b = start;
        T c = end - start;
        float d = 1;
        s *= (1.525f);
        if ((t /= d / 2) < 1) return static_cast<T>(c / 2 * (t * t * (((s) + 1) * t - s)) + b);
        float postFix = t -= 2;
        return static_cast<T>(c / 2 * ((postFix) * t * (((s) + 1) * t + s) + 2) + b);
    }

}

/*
MIT License

Copyright (c) 2018 Azarias Boutin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


    /**
     * @brief The easing class holds all the bundled easings.
     *
     * You should pass the easing function to the @p tweeny::tween::via method, to set the easing function that will
     * be used to interpolate values in a tween currentPoint.
     *
     * **Example**:
     *
     * @code
     * auto tween = tweeny::from(0).to(100).via(tweeny::easing::linear);
     * @endcode
     */

enum easing{
    linear,
    sineIn, sineOut, sineInOut,
    quadIn, quadOut, quadInOut,
    cubicIn, cubicOut, cubicInOut,
    quartIn, quartOut, quartInOut,
    quintIn, quintOut, quintInOut,
    expoIn, expoOut, expoInOut,
    circIn, circOut, circInOut,
    backIn, backOut, backInOut,
    elastIn, elastOut, elastInOut,
    bounceIn, bounceOut, bounceInOut
};


/**
     * @brief The Twin class the main class of the library,
     * has only three usefull functions : update to update the internal
     * progress,
     * get, to get the current value of the object
     * and progress to get the value of the progress
     * 0 means starting
     * 1 means finished
     */
    template<typename BOUND,//type of bounds
             typename F = std::function<void()>>//type of callbak function
    class Twin
    {

    public:
        /**
         * @brief Twin first constructor
         * @param from the begining value
         * @param to the value to reach
         * @param time the time it takes to go from 'from' to 'to'
         * @param ease the easing function to use
         * @param finalCallback the function to call when the tweening
         * is over
         */
        Twin(const BOUND &from, const BOUND& to, const sf::Time &time, easing ease, const F finalCallback):
            from(from),
            to(to),
            totalTime(time),
            advance(),
            totalProgress(0.f),
            finishCallback(finalCallback),
            easingF(getEasing(ease))
        {
        }

        /**
         * @brief Twin second constructor (without callback)
         * @param from the begning value
         * @param to the value to reach
         * @param time the time it takes to go from 'from' to 'to'
         * @param ease the easing function
         */
        Twin(const BOUND &from, const BOUND &to, const sf::Time &time, easing ease):
            from(from),
            to(to),
            totalTime(time),
            advance(),
            totalProgress(0.f),
            finishCallback(noop),
            easingF(getEasing(ease))
        {
        }

        Twin():
            from(0),
            to(0),
            totalTime(),
            advance(),
            totalProgress(0.f),
            finishCallback(noop),
            easingF(getEasing(linear))
        {

        }

        /**
         * @brief step steps of the given progress
         * @param progress the progress made since the last step
         */
        void step(const sf::Time &progress)
        {
            if(totalProgress == 1.f)return;

            advance += progress;
            totalProgress = advance/totalTime;
            if(advance >= totalTime){
                advance = totalTime;
                totalProgress = advance/totalTime;

                if(finishCallback) finishCallback();
            }
        }

        /**
         * @brief get returns the current value of the data held,
         * the data is calculated each time this function is called
         * in order to gain performance if you call the function
         * several times, it is advised to store the result of the
         * function in a variable
         * @return the value of the data held
         */
        BOUND get() const
        {
            return easingF(totalProgress, from,to);
        }

        /**
         * @brief progresss current progress of the tweening, 0 means starting, 1 means finished
         * @return the progress of the tweening
         */
        float progress() const
        {
            return totalProgress;
        }

        void setCallback(const F cb)
        {
            finishCallback = cb;
        }

        virtual ~Twin()
        {

        }

    private:
        /**
         * @brief getEasing turns the enum into a function
         * @param easingType the easing enum
         * @return the function corresponding to the enum
         */
        std::function<BOUND(float, BOUND,BOUND)> getEasing(twin::easing easingType) const
        {
            switch (easingType) {
            case linear:return linearImpl<BOUND>;
            case sineIn:return sinusoidalIn<BOUND>;
            case sineOut:return sinusoidalOut<BOUND>;
            case sineInOut:return sinusoidalInOut<BOUND>;
            case quadIn:return quadraticIn<BOUND>;
            case quadOut:return quadraticOut<BOUND>;
            case quadInOut:return quadraticInOut<BOUND>;
            case cubicIn:return cubicInImpl<BOUND>;
            case cubicOut:return cubicOutImpl<BOUND>;
            case cubicInOut:return cubicInOutImpl<BOUND>;
            case quartIn:return quarticIn<BOUND>;
            case quartOut:return quarticOut<BOUND>;
            case quartInOut:return quarticInOut<BOUND>;
            case quintIn:return quinticIn<BOUND>;
            case quintOut:return quinticOut<BOUND>;
            case quintInOut:return quinticInOut<BOUND>;
            case expoIn:return exponentialIn<BOUND>;
            case expoOut:return exponentialOut<BOUND>;
            case expoInOut:return exponentialInOut<BOUND>;
            case circIn:return circularIn<BOUND>;
            case circOut:return circularOut<BOUND>;
            case circInOut:return circularInOut<BOUND>;
            case backIn:return backInImpl<BOUND>;
            case backOut:return backOutImpl<BOUND>;
            case backInOut:return backInOutImpl<BOUND>;
            case elastIn:return elasticIn<BOUND>;
            case elastOut:return elasticOut<BOUND>;
            case elastInOut:return elasticInOut<BOUND>;
            case bounceIn:return bounceInImpl<BOUND>;
            case bounceOut:return bounceOutImpl<BOUND>;
            case bounceInOut:return bounceInOutImpl<BOUND>;
            }
            return linearImpl<BOUND>;
        }

        /**
          No operation function, called whenever
          no callback is set at the end of the tweening
        */
        std::function<void()> noop = [](){};

        //the value from where the tweening starts
        BOUND from;

        //The value the tweening must reach
        BOUND to;

        float totalProgress;//total progress  0 = begin, 1 = finished

        //The time it must take to reach the value
        sf::Time totalTime;

        //The current time value
        sf::Time advance;

        //the function to call whenever the tweening is over
        F finishCallback;

        //The easing function to get the value
        std::function<BOUND(float,BOUND,BOUND)> easingF;
    };

    /**
     * @brief makeTwin util function to create a twin object with template type deduction
     * @param from the original value
     * @param to the value to reach
     * @param time the time it must take to complete the tweening
     * @param ez the easing function to use
     * @param func the callback function when the tweening is over
     * @return a twin object
     */
    template<typename BOUND,
             typename CALLBACK>
    Twin<BOUND,CALLBACK> makeTwin(const BOUND &from, const BOUND &to, const sf::Time &time, easing ez, const CALLBACK &func)
    {
        return Twin<BOUND,CALLBACK>(from, to, time, ez, func);
    }

    /**
     * @brief makeTwin util function to create a twin object withe template type deduction
     * @param from the original value
     * @param to the value to reach
     * @param time time it must take to complete the tweening
     * @param ez the easing function to use
     * @return a twing object
     */
    template<typename BOUND>
    Twin<BOUND> makeTwin(const BOUND &from, const BOUND &to, const sf::Time &time, easing ez, const std::function<void()> callback = {})
    {
        return Twin<BOUND>(from,to, time, ez, callback);
    }
}

