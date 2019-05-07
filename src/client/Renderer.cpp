/*
 * The MIT License
 *
 * Copyright 2017-2019 azarias.
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
#include "widgets/RandomAnimation.hpp"

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

void Renderer::update(const sf::Time &delta)
{
    /*  if(m_shakeTimeout > sf::Time::Zero){
        m_shakeTimeout -= elapsed;
        float randAngle = (std::rand() % 360);
        float radius = m_shakeTimeout.asSeconds();
        sf::Vector2f offset(std::cos(randAngle) * radius, std::sin(randAngle) * radius );
        top().transform.translate(offset);
    }else{
        top().transform.

    }*/

    for(auto &it : m_objectsAnimations){
       it.second.update(delta);
    }
}

sf::RenderStates &Renderer::top()
{
    return m_stack.top();
}

Renderer &Renderer::scale(float nwScale)
{
    return scale(nwScale, nwScale);
}

Renderer &Renderer::scale(float xScale, float yScale)
{
    top().transform.scale(xScale, yScale);
    return *this;
}

Renderer &Renderer::scale(float nwScale, const sf::Vector2f &center)
{
    top().transform.scale(nwScale, nwScale, center.x, center.y);
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
    Assets::Animations anim = paddle.getNum() == 1 ? Assets::Animations::Paddle1 : Assets::Animations::Paddle2;
    return render(assertObjectExist(&paddle, anim, sf::Vector2i(20, 1), sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT)));
}

Renderer &Renderer::renderWall(const Wall &wall)
{
    return render(assertObjectExist(&wall, Assets::Animations::Wall, sf::Vector2i(1, 20), sf::Vector2f(WALL_WITDH, WALL_HEIGHT)));
}

Renderer &Renderer::renderBall(const Ball& ball)
{
    return render(assertObjectExist(&ball, Assets::Animations::Ball, sf::Vector2i(20, 1), sf::Vector2f(BALL_RADIUS * 2, BALL_RADIUS * 2)));
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

RandomAnimation &Renderer::assertObjectExist(const PhysicObject *obj, Assets::Animations animation, const sf::Vector2i &sprites, const sf::Vector2f &size)
{
    auto found = m_objectsAnimations.find(obj);
    if(found == m_objectsAnimations.end()){
        RandomAnimation &ra = m_objectsAnimations.insert(std::make_pair(obj, RandomAnimation(
                                                  pr::resourceManager().get(animation),
                                                  sprites,
                                                  sf::milliseconds(50)
        ))).first->second;
        ra.setPosition(b2VecToSfVect(obj->getPosition()));
        ra.setSize(size);
        return ra;
    }

    found->second.setPosition(b2VecToSfVect(obj->getPosition()));
    return found->second;
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
