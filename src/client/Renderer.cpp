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
 * File:   Renderer.cpp
 * Author: azarias
 * 
 * Created on 9 octobre 2017, 19:19
 */

#include "Renderer.hpp"
#include "../Config.hpp"
#include <math.h>

Renderer::Renderer(sf::RenderTarget &target) :
target(target)
{
}

Renderer::~Renderer()
{
}

void Renderer::shake()
{
	m_shakeTimeout = sf::seconds(1.f);
}

void Renderer::update(sf::Time elapsed)
{
	if(m_shakeTimeout > sf::Time::Zero){
		m_shakeTimeout -= elapsed;
		float randAngle = (std::rand() % 360);
		float radius = m_shakeTimeout.asSeconds();
		sf::Vector2f offset(std::cos(randAngle) * radius, std::sin(randAngle) * radius );
		m_renderStates = sf::RenderStates::Default;
		m_renderStates.transform.translate(offset);
	}else{
		m_renderStates = sf::RenderStates::Default;
	}

}

void Renderer::renderBall(const Ball& ball)
{
	sf::CircleShape circle(BALL_RADIUS);

	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(ball.getPosition());

	render(circle);
}

void Renderer::renderPowerup(const Powerup &powerup)
{

    sf::RectangleShape rect(sf::Vector2f(POWERUP_SIDE, POWERUP_SIDE));
    rect.setPosition(powerup.getHitbox().left,powerup.getHitbox().top);

    rect.setFillColor(sf::Color::Green);//Green rectangle for now, animations later
    render(rect);
}

void Renderer::renderPaddle(const Paddle& paddle)
{
	sf::RectangleShape rectangle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));

	rectangle.setFillColor(sf::Color::Yellow);

	rectangle.setPosition(paddle.getPosition());

	render(rectangle);
}


void Renderer::render(const sf::Drawable& drawable)
{
	target.draw(drawable, m_renderStates);
}

