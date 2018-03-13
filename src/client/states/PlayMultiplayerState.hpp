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
 * File:   PlayState.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 17:49
 */

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <SFML/System/Thread.hpp>
#include "PlayState.hpp"

namespace sf{
    class Event;
}
class Player;


/**
 * @brief The PlayState class state when the player is actually playing
 * the state has two threads : one that listens for the events and draws
 * stuff in the screen, and another thread to listen at the sockets, for
 * the server's input
 */
class PlayMultiplayerState : public PlayState {
public:

	/**
	 * @brief PlayState constructor
	 * @param client a reference to the client's app
	 */
    PlayMultiplayerState();

	/**
	 * @brief handleEvent inherited function
	 * @param ev
	 */
	void handleEvent(const sf::Event& ev) override;

	/**
	 * @brief onEnter inherited function
	 * @param data
	 */
	void onEnter(BaseStateData *data) override;

	/**
	 * @brief onLeave inherited function
	 */
	void onLeave() override;

	/**
	 * @brief listenSocket function run by the thread
	 */
	void listenSocket();

    void bounced(int pNum, sf::Vector2f position);

    virtual ~PlayMultiplayerState();

private:

	/**
	 * @brief listeningThread the threads that listens at
	 * the sockets input from the server
	 */
	sf::Thread listeningThread;

	/**
	 * @brief gameFinisehd wether the game ended
	 */
	bool gameFinisehd = false;
};

#endif /* PLAYSTATE_H */
