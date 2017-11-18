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
 * File:   main.cpp
 * Author: azarias
 *
 * Created on 8 octobre 2017, 18:35
 */

#include <cstdlib>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include "Paddle.hpp"
#include "Application.hpp"

#ifdef CLIENT
#include "client/ClientApp.hpp"
#elif SERVER
#include "server/ServerApp.hpp"
#endif

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

/*
 * 
 */
int main(int argc, char** argv)
{

#ifdef CLIENT
    ClientApp &app = ClientApp::getInstance();
    app.initStates();
#elif SERVER
	ServerApp app;
#else
#error "Found neither of configuration 'client' or 'server'"
#endif
	app.run(argc, argv);
	return 0;
}

