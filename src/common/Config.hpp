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
 * File:   Config.h
 * Author: azarias
 *
 * Created on 24/10/2017
 */
#pragma once


//Netorking
#define DEFAULT_PORT 5300

//Dimensions (all in meters)
//Arena
#define SF_ARENA_WIDTH 800
#define SF_ARENA_HEIGHT 600

#define ARENA_WIDTH 12.5
#define ARENA_HEIGHT 9.375

//Paddle
#define PADDLE_WIDTH 0.1
#define PADDLE_HEIGHT 1

//ball
#define BALL_RADIUS  0.2

//dialog
#define SF_DIALOG_WIDTH 700
#define SF_DIALOG_HEIGHT 200

//powerup
#define POWERUP_SIDE 50

//walls
#define WALL_WITDH ARENA_WIDTH
#define WALL_HEIGHT PADDLE_WIDTH

//Starting conf
#define BALL_START_X (ARENA_WIDTH/2.f)
#define BALL_START_Y (ARENA_HEIGHT/2.f)

#define BALL_DIR_X -3
#define BALL_DIR_Y 1

//Powerups
#define PADDLE_WIDTH_POWERUP 10
#define BALL_RADIUS_POWERUP 10

#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3
