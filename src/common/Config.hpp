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

namespace mp {

//Server
constexpr int DEFAULT_PORT = 5300;

constexpr float ARENA_WIDTH = 18.75;
constexpr float ARENA_HEIGHT = 14.0625;

//Paddle
constexpr float PADDLE_WIDTH = 0.1F;
constexpr float PADDLE_HEIGHT = 1;

//Ball
constexpr float BALL_RADIUS = 0.2F;
constexpr float BALL_START_X = ARENA_WIDTH / 2.f;
constexpr float BALL_START_Y = ARENA_HEIGHT  / 2.f;

constexpr float BALL_DIR_X = -3;
constexpr float BALL_DIR_Y = 1;

//Wall
constexpr float WALL_WITDH = ARENA_WIDTH;
constexpr float WALL_HEIGHT = PADDLE_WIDTH;

//Powerups
constexpr float POWERUP_SIDE = 50;

//Physics
constexpr int VELOCITY_ITERATIONS = 8;
constexpr int POSITION_ITERATIONS = 3;

}
