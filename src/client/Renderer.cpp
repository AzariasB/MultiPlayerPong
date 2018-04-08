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
#include "src/common/Config.hpp"
#include "src/common/Ball.hpp"
#include "src/common/Paddle.hpp"
#include "src/common/Wall.hpp"

#include "Provider.hpp"
#include "ResourcesManager.hpp"
#include "ClientConf.hpp"

#include <math.h>

Renderer::Renderer(sf::RenderTarget &target) :
    target(target)
{
    m_stack.push(sf::RenderStates::Default);
}

Renderer::~Renderer()
{
}

Renderer &Renderer::pop()
{
    if(m_stack.size() == 0){
        std::out_of_range("The contains only one element");
    }
    m_stack.pop();

    return *this;
}

Renderer &Renderer::push()
{
    m_stack.push(m_stack.top());
    return *this;
}


void Renderer::shake()
{
 //   m_shakeTimeout = sf::seconds(1.f);
}

void Renderer::update(sf::Time elapsed)
{
  /*  if(m_shakeTimeout > sf::Time::Zero){
        m_shakeTimeout -= elapsed;
        float randAngle = (std::rand() % 360);
        float radius = m_shakeTimeout.asSeconds();
        sf::Vector2f offset(std::cos(randAngle) * radius, std::sin(randAngle) * radius );
        top().transform.translate(offset);
    }else{
        top().transform.
    }

    //update all powerup animations
    for(auto it = m_powerupAnimations.begin(); it != m_powerupAnimations.end(); ++it){
        it->second.update(elapsed);
    }*/
}

sf::RenderStates &Renderer::top()
{
    return m_stack.top();
}

Renderer &Renderer::scale(float nwScale)
{
    top().transform.scale(nwScale, nwScale);
    return *this;
}

Renderer &Renderer::setTexture(const sf::Texture *texture)
{
    top().texture = texture;
    return *this;
}

Renderer &Renderer::rotateAround(const sf::Vector2f &center, float angle)
{
    top().transform.rotate(angle, center);
    return *this;
}

Renderer &Renderer::translate(const sf::Vector2f &translation)
{
    top().transform.translate(translation);
    return *this;
}

Renderer &Renderer::rotate(float angle)
{
    top().transform.rotate(angle);
    return *this;
}

void Renderer::renderPowerup(const Powerup &powerup)
{
    if(powerup.isHidden())return;

    if(m_powerupAnimations.count(powerup.getId()) == 0){
        addPowerUpAnimation(powerup);
    }
    Animation &anim = m_powerupAnimations.find(powerup.getId())->second;

    sf::Vector2f position(powerup.getHitbox().left, powerup.getHitbox().top);
    anim.setPosition(position);
    render(anim);
}

Animation &Renderer::addPowerUpAnimation(const Powerup &powerup)
{
    const sf::Texture &texture = powerupTexture(powerup.getType());
    sf::Vector2i sprites = powerupSprites(powerup.getType());
    auto pair = m_powerupAnimations.emplace(std::piecewise_construct,
                                   std::forward_as_tuple(powerup.getId()),
                                   std::forward_as_tuple(texture, sprites, sf::seconds(1))
                                   );
    pr::connect(powerup.powerupDestroyed, &Renderer::destroyAnimation, this, powerup.getId());
    return pair.first->second;
}

void Renderer::destroyAnimation(sf::Uint64 animationId)
{
    m_powerupAnimations.erase(animationId);
}

const sf::Texture &Renderer::powerupTexture(const Powerup::POWERUP_TYPE &powerupType) const
{
    switch(powerupType){
    case Powerup::BALL_EXTEND:
        return pr::resourceManager().getTexture("ball_extend");
    case Powerup::BALL_RETRACT:
        return pr::resourceManager().getTexture("ball_retract");
    case Powerup::PADDLE_EXTEND:
        return pr::resourceManager().getTexture("paddle_extend");
    case Powerup::PADDLE_RETRACT:
        return pr::resourceManager().getTexture("paddle_retract");
    default:
        return pr::resourceManager().getTexture("empty_texture");
    }
}

sf::Vector2i Renderer::powerupSprites(const Powerup::POWERUP_TYPE &powerupType) const
{
    switch(powerupType){
    case Powerup::PADDLE_EXTEND:
    case Powerup::PADDLE_RETRACT:
        return sf::Vector2i(6,1);
    default:
        return sf::Vector2i(4,1);
    }
}

void Renderer::renderPaddle(const Paddle& paddle)
{
    render(*assertRectExist(&paddle, PADDLE_WIDTH, PADDLE_HEIGHT, cc::colors::paddleColor));
}

void Renderer::renderWall(const Wall &wall)
{
    render(*assertRectExist(&wall, WALL_WITDH, WALL_HEIGHT, cc::colors::wallColor));
}

void Renderer::renderBall(const Ball& ball)
{
    render(*assertCircleExist(&ball, BALL_RADIUS, cc::colors::ballColor));
}

std::unique_ptr<sf::Shape> &Renderer::assertCircleExist(const PhysicObject *obj, float radius, const sf::Color &fillColor)
{
    if(m_shapes.find(obj) == m_shapes.end()){
        std::unique_ptr<sf::Shape> &target = (m_shapes[obj] = std::make_unique<sf::CircleShape>(radius));
        target->setOrigin(radius, radius);
        target->setFillColor(fillColor);
        const b2Vec2 &pos = obj->getPosition();
        target->setPosition(pos.x, pos.y);
    }else if(!obj->isStatic()){
        const b2Vec2 &pos = obj->getPosition();
        m_shapes[obj]->setPosition(pos.x, pos.y);
    }
    return m_shapes[obj];
}


std::unique_ptr<sf::Shape> &Renderer::assertRectExist(const PhysicObject *obj, float width, float height, const sf::Color &fillColor)
{
    if(m_shapes.find(obj) == m_shapes.end()){//not found
        std::unique_ptr<sf::Shape> &target = (m_shapes[obj] = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height)));
        target->setOrigin(width/2, height/2);
        target->setFillColor(fillColor);
        const b2Vec2 &pos = obj->getPosition();
        target->setPosition(pos.x, pos.y);
    }else if(!obj->isStatic()){//object can move
        const b2Vec2 &pos = obj->getPosition();
        m_shapes[obj]->setPosition(pos.x, pos.y);
    }
    return m_shapes[obj];
}

void Renderer::render(const sf::Drawable& drawable)
{
    target.draw(drawable, m_stack.top());
}

