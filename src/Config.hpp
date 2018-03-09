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
 * File:   Config.h
 * Author: azarias
 *
 * Created on 24/10/2017
 */
#ifndef CONFIG_H
#define CONFIG_H

#define b2_velocityThreshold		0.0f

//Dimensions
#define ARENA_WIDTH 800
#define ARENA_HEIGHT 600
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 120
#define BALL_RADIUS  50
#define DIALOG_WIDTH 700
#define DIALOG_HEIGHT 200
#define POWERUP_SIDE 50

//walls
#define WALL_WITDH ARENA_WIDTH
#define WALL_HEIGHT PADDLE_WIDTH

//speeds
#define PADDLE_SPEED 2
#define BALL_SPEED 2

//Starting conf
#define BALL_START_POS sf::Vector2f(ARENA_WIDTH/2 - BALL_RADIUS, ARENA_HEIGHT/2 - BALL_RADIUS)
#define BALL_START_DIR sf::Vector2f(2.3,1)

//Powerups
#define PADDLE_WIDTH_POWERUP 10
#define BALL_RADIUS_POWERUP 10

#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3

#endif // CONFIG_H
