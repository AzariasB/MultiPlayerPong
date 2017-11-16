/* 
 * File:   ClientApp.h
 * Author: azarias
 *
 * Created on 9 octobre 2017, 18:06
 */

#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Network/Socket.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <deque>

#include "../Application.hpp"
#include "Renderer.hpp"
#include "../Game.hpp"
#include "StateMachine.hpp"
#include "ResourcesManager.hpp"
#include "SoundEngine.hpp"
#include "ParticleGenerator.hpp"
#include "KeyBinding.hpp"

/**
 * @brief The STATE_TYPE enum associate with each state, an int (enum)
 * to store these in the state machine, and retrieve them later
 */
enum STATE_TYPE {
	MENU,//First state
	PLAY,
	OPTIONS,
    KEY_BINDINGS,
	WAITING,
	FINISHED
};

/**
 * @brief The ClientApp class the client application
 * contains the game, and all the data necessary for the client
 * to run (the socket, the rendrer, the resource manager, the soundEngine, ...)
 * Could be designed as a Singleton. Is passed to all the sub-instances of the widgets
 */
class ClientApp : public Application {
public:
	/**
	 * @brief ClientApp default constructor, no data to input
	 */
	ClientApp();

	/**
	 * @brief run starts the main loop, until the window closes
	 * @param argc the number of argument received
	 * @param argv the arguments
	 */
	void run(int argc, char** argv) override;

	/**
	 * @brief getGame the game object
	 * @return the game object
	 */
	Game& getGame();

	/**
	 * @brief getGame const version of getGame
	 * @return a const reference to the game
	 */
	const Game &getGame() const;

	/**
	 * @brief getRenderer the renderer
	 * @return the renderer
	 */
	Renderer &getRenderer();

	/**
	 * @brief getPlayer the player for this client application (could be player1 or player2 of the
	 * game object)
	 * @return the player associated with this application
	 */
	Player &getPlayer();

	/**
	 * @brief getPlayer const version of getPlayer
	 * @return a const reference to the player
	 */
	const Player &getPlayer() const;

	/**
	 * @brief getSocket reference to the client's socket
	 * @return a reference to the socket
	 */
	sf::TcpSocket &getSocket();

	/**
	 * @brief setPNumber sets the player number (1 or 2)
	 * @param pNumber the number of the player
	 */
	void setPNumber(int pNumber);

	/**
	 * @brief getStateMachine reference to the state machine
	 * @return a reference to the state machine
	 */
	StateMachine &getStateMachine();

	/**
	 * @brief getSoundEngine reference to the sound engine
	 * @return a reference to the sound engine
	 */
	SoundEngine &getSoundEngine();

	/**
	 * @brief getSoundEngine const reference to const sound engine
	 * @return const reference to const sound engine
	 */
	const SoundEngine &getSoundEngine() const;

	/**
	 * @brief getParticleGenerator reference to the particle generator
	 * @return a reference to the particle generator
	 */
	ParticleGenerator &getParticleGenerator();

	/**
	 * @brief getParticleGenerator const reference to the particle generator
	 * @return a const reference to the particle generator
	 */
	const ParticleGenerator &getParticleGenerator() const;


	sf::RenderWindow &getWindow();

	/**
	 * @brief getWindow const reference to the renderWindow
	 * @return a const reference to the render window
	 */
	const sf::RenderWindow &getWindow() const;

	/**
	 * @brief getResourcesManager const reference to the resource manager
	 * @return const reference to the resource manager
	 */
	const ResourcesManager &getResourcesManager();


	KeyBinding &getKeyBindings();

	const KeyBinding &getKeyBindings() const;

	/**
	 * @brief isWinner wether the app's client is the winner (false if the game is still running)
	 * @return wether the app's client won the game
	 */
	bool isWinner() const;
	
	/**
	 * @brief quit closes the window to finish the main loop
	 */
	void quit();

	virtual ~ClientApp();
private:
	/**
	 * @brief hasPNumber if the current number of the app is 1 or 2
	 * @return wether the client number is a valid client number
	 */
	bool hasPNumber() const;

	/**
	 * @brief handleEvent handles the sfml event (closes the window if necessary)
	 * otherwise, call the event handler of the current state
	 * @param event the event to handle
	 */
	void handleEvent(const sf::Event &event);

	/**
	 * @brief resizeEvent when the window is resized
	 * @param event the event object
	 */
	void resizeEvent(const sf::Event &event);

	/**
	 * @brief window window to use to get events
	 * and render stuff
	 */
	sf::RenderWindow window;

	/**
	 * @brief renderer Object to use to render the game objects,
	 * and all the drawable objects
	 */
	Renderer renderer;

	/**
	 * @brief game the game
	 */
	Game game;

	/**
	 * @brief stateMachine the state machine, in which we'll store
	 * all our states
	 */
	StateMachine stateMachine;

	/**
	 * @brief m_number the number of the player
	 * is sent by the server
	 */
	int m_number = -1;

	/**
	 * @brief socket the socket used to connect to the
	 * server
	 */
	sf::TcpSocket socket;

	/**
	 * @brief rManager the resource manager, holds all the data
	 * used for the graphics and the sound (client related)
	 */
	ResourcesManager rManager;

	/**
	 * @brief m_sEngine the sound engine : to have an easy
	 * access to play sounds
	 */
	SoundEngine m_sEngine;

	/**
	 * @brief m_particleGenerator particle generator
	 * used to create explosions effects an such
	 */
	ParticleGenerator m_particleGenerator;

	/**
	 * @brief m_keyBinding the objects that contains all
	 * the key bindings
	 */
	KeyBinding m_keyBinding;
};

#endif /* CLIENTAPP_H */

