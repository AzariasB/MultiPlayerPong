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
 * File:   Application.h
 * Author: azarias
 *
 * Created on 9 octobre 2017, 08:49
 */

#pragma once


#include <unordered_map>
#include <SFML/System/String.hpp>
#include <SFML/System/NonCopyable.hpp>

namespace mp {


/**
 * @brief The Application class base class for all the applications (client and server)
 * contains a map of string for the configuration,
 * can be used as a singleton
 */
class Application : public sf::NonCopyable {
public:
    /**
     * @brief Application constructor
     */
    Application();

    virtual ~Application();

    /**
     * @brief run starts the main loop of the application (may be an infinite loop)
     * @param argc the number of argument
     * @param argv the arguments
     */
    virtual void run(int, char **);

    /**
     * @brief instance returns and instance of the application
     * @return the single instance of the client
     */
    static Application &instance();
private:
    /**
     * @brief _app static pointer of the application
     */
    static Application *_app;

    /**
     * @brief config the app's configuration
     */
    std::unordered_map<std::string, std::string> config;

};

}



