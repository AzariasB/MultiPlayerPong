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
 * File:   Renderer.hpp
 * Author: azarias
 *
 * Created on 9 octobre 2017, 19:19
 */

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System.hpp>
#include <unordered_map>
#include "Animation.hpp"

#include "../Powerup.hpp"

class Ball;
class Paddle;
class Wall;
/**
 * @brief The Renderer class used to render every objects of the game
 * knows how to render the game's objects (ball, paddle)
 * needs to be updated for the effects to work (screen shaking for example)
 * has the possibility to trigger a screen shaking for 1 second
 */
class Renderer {
public:
	/**
	 * @brief Renderer constructor
	 * @param target the target that will be used to render all the game's objects
	 */
	Renderer(sf::RenderTarget &target);

	/**
	 * @brief renderBall renders the game's ball (as a blue circle for now)
	 * @param ball the ball to render
	 */
	void renderBall(const Ball &ball);

	/**
	 * @brief renderPaddle renders one paddle. (as a yellow rectangle for now)
	 * @param paddle a const reference to the paddle to render
	 */
	void renderPaddle(const Paddle &paddle);

    /**
     * @brief renderWall renders a wall
     * @param wall
     */
    void renderWall(const Wall &wall);

    /**
     * @brief renderPowerup renders one powerup
     * @param powerup const reference to the powerup to render
     */
    void renderPowerup(const Powerup &powerup);

	/**
	 * @brief shake triggers a slight screen shaking for one second
	 */
	void shake();

	/**
	 * @brief update updates the inner state of this object
	 * @param elapsed the time elapsed since the last update
	 */
	void update(sf::Time elapsed);

	/**
	 * @brief render renders any drawable components, using it's inner renderstate
	 * @param drawable the drawable object to render
	 */
	void render(const sf::Drawable &drawable);

    /**
     * @brief setView changes the view of the renderer
     * @param view the new view
     */
    void setView(const sf::View &view);

    /**
     * @brief resetView sets the view back to the default one
     */
    void resetView();

	/**
	 * @brief getRenderTarget a reference to the renderTarget
	 * @return a reference to the renderTarget
	 */
	sf::RenderTarget &getRenderTarget()
	{
		return target;
	}

	/**
	 * @brief getRenderStates a reference to the current renderStates
	 * @return a reference to the current renderStates
	 */
	sf::RenderStates &getRenderStates()
	{
		return m_renderStates;
	}

	virtual ~Renderer();
private:

    /**
     * @brief addPowerUpAnimation adds the animations for the given powerup to the map
     * @param powerup the new powerup
     */
    Animation &addPowerUpAnimation(const Powerup &powerup);

    /**
     * @brief powerupTexture returns the texture for the type of powerup
     * @param powerup
     * @return
     */
    const sf::Texture &powerupTexture(const Powerup::POWERUP_TYPE &powerupType) const;

    /**
     * @brief powerupSprites return the sprites dimensions depending on the powerup type
     * @param powerupType the powerup to use to find the dimensions
     * @return
     */
    sf::Vector2i powerupSprites(const Powerup::POWERUP_TYPE &powerupType) const;

    /**
     * @brief destroyAnimation when a powerup is destroyed, destroys the animtaion linked to it
     * @param animationId the id of the animation to delete
     */
    void destroyAnimation(sf::Uint64 animationId);

	/**
	 * @brief target the target to use to draw stuff on it
	 */
	sf::RenderTarget &target;

	/**
	 * @brief m_renderStates the current rendering state
	 */
	sf::RenderStates m_renderStates = sf::RenderStates::Default;

	/**
	 * @brief m_shakeTimeout the shake timeout, when at 0 (or less) no need to shake,
	 * otherwise, the screen is shaking
	 */
	sf::Time m_shakeTimeout;

    /**
     * @brief m_powerupAnimations the animations of all the powerups
     */
    std::unordered_map<sf::Uint64, Animation> m_powerupAnimations;
};

#endif /* RENDERER_HPP */

