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
 * File:   ServerApp.cpp
 * Author: azarias
 * 
 * Created on 9 octobre 2017, 18:06
 */

#include "ServerApp.hpp"
#include <SFML/Network.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>
#include <time.h>

ServerApp::ServerApp()
{
}

ServerApp::~ServerApp()
{
}

void ServerApp::run(int argc, char** argv)
{
    srand(time(NULL));
	sf::TcpListener listener;

	sf::Socket::Status status = listener.listen(5300);

	if (status != sf::Socket::Done) {
		std::cerr << "Could not start server\n";
		exit(-1);
	}

	std::cout << "Listening for any incomming connections\n";
	while (1) {
		lobbies.push_back(std::make_unique<LobbyThread>());
		lobbies.back()->lobby.receivePlayers(listener);
		lobbies.back()->thread.launch();
		cleanLobbies();
	}

	listener.close(); //If ever ....
}

void ServerApp::cleanLobbies()
{
	for (auto it = lobbies.begin(); it != lobbies.end();) {
		if ((*it)->lobby.isFinished()) {
			(*it)->thread.terminate();
			it = lobbies.erase(it);
		} else {
			++it;
		}
	}
}

