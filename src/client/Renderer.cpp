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
 * File:   Renderer.cpp
 * Author: azarias
 *
 * Created on 9 octobre 2017, 19:19
 */
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>

#include "Assets.hpp"
#include "Renderer.hpp"
#include "src/common/Config.hpp"
#include "src/common/Ball.hpp"
#include "src/common/Paddle.hpp"
#include "src/common/Wall.hpp"

#include "Provider.hpp"
#include "ResourcesManager.hpp"
#include "ClientConf.hpp"
#include "Renderable.hpp"

#include <math.h>
#include <functional>

namespace mp {

Renderer::Renderer(sf::RenderTarget *target) :
    m_target(target),
    m_windowTarget(target),
    m_stack()
{
    m_stack.push(sf::RenderStates::Default);
    m_textureTarget.create(target->getSize().x, target->getSize().y);
}

void Renderer::updateRenderTarget(sf::RenderTarget *target)
{
    m_target = target;
    m_windowTarget = target;
    m_textureTarget.create(target->getSize().x, target->getSize().y);
}

Renderer::~Renderer()
{
}

Renderer &Renderer::pop()
{
    if(m_stack.size() == 1){
        std::out_of_range("The stack contains only one element");
    }
    m_stack.pop();

    return *this;
}

Renderer &Renderer::push()
{
    m_stack.push(m_stack.top());
    return *this;
}

Renderer &Renderer::pushShader(const sf::Shader *shader)
{
    sf::RenderStates &top = m_stack.top();
    m_stack.emplace(top.blendMode, top.transform, top.texture, shader);
    return *this;
}

void Renderer::shake()
{
    //   m_shakeTimeout = sf::seconds(1.f);
}

void Renderer::update(const sf::Time &)
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

Renderer &Renderer::renderPaddle(const Paddle& paddle)
{
    return draw(*assertRectExist(&paddle, PADDLE_WIDTH, PADDLE_HEIGHT, cc::Colors::paddleColor));
}

Renderer &Renderer::renderWall(const Wall &wall)
{
    return draw(*assertRectExist(&wall, WALL_WITDH, WALL_HEIGHT, cc::Colors::wallColor));
}

Renderer &Renderer::renderBall(const Ball& ball)
{
    return draw(*assertCircleExist(&ball, BALL_RADIUS, cc::Colors::ballColor));
}

Renderer &Renderer::useTextureTarget()
{
    m_textureTarget.clear(sf::Color::Transparent);
    m_target = &m_textureTarget;
    return *this;
}

Renderer &Renderer::useWindowTarget()
{
    m_target = m_windowTarget;
    return *this;
}

sf::Texture Renderer::getTextureTarget()
{
    m_textureTarget.display();
    return m_textureTarget.getTexture();
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

Renderer &Renderer::draw(const sf::Drawable &drawable)
{
    m_target->draw(drawable, m_stack.top());
    return *this;
}

Renderer &Renderer::render(const Renderable &renderable)
{
    renderable.render(*this);
    return *this;
}

}
