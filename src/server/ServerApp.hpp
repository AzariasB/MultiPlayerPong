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
 * File:   ServerApp.h
 * Author: azarias
 *
 * Created on 9 octobre 2017, 18:06
 */

#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include "src/common/Application.hpp"
#include "src/common/Game.hpp"
#include "Lobby.hpp"

/**
 * @brief The ServerApp class the application run
 * by the server,
 * listens for any connections, when two players
 * are connected, launcheds a Lobby and wait for
 * the next connection
 */
class ServerApp : public Application {
public:
	ServerApp();

	/**
	 * @brief run wait for the players to connect, launch the lobby once it's ready
	 * @param argc arg count
	 * @param argv arguments
	 */
	void run(int argc, char** argv) override;
	
	virtual ~ServerApp();
private:
	/**
	 * @brief cleanLobbies removes all the lobbies that finished the game
	 * is called when a new lobby is created
	 */
	void cleanLobbies();

	/**
	 * @brief lobbies all the lobbies currently active
	 */
	std::vector<std::unique_ptr<LobbyThread>> lobbies;
};

#endif /* SERVERAPP_H */
