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
 * File:   Renderer.hpp
 * Author: azarias
 *
 * Created on 9 octobre 2017, 19:19
 */

#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System.hpp>
#include <unordered_map>
#include <stack>

#include "Animation.hpp"

namespace mp {

class Ball;
class Paddle;
class Wall;
class PhysicObject;
class Renderable;

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
    Renderer(sf::RenderTarget *target);

    /**
     * @brief updateRenderTarget whenever the client toggles
     * the screen state, we create a new window
     * thus, we need to be able to change the render target
     * @param target
     */
    void updateRenderTarget(sf::RenderTarget *target);

    /**
     * @brief renderBall renders the game's ball (as a blue circle for now)
     * @param ball the ball to render
     */
    Renderer &renderBall(const Ball &ball);

    /**
     * @brief renderPaddle renders one paddle. (as a yellow rectangle for now)
     * @param paddle a const reference to the paddle to render
     */
    Renderer &renderPaddle(const Paddle &paddle);

    /**
     * @brief renderWall renders a wall
     * @param wall
     */
    Renderer &renderWall(const Wall &wall);

    /**
     * @brief shake triggers a slight screen shaking for one second
     */
    void shake();

    /**
     * @brief update updates the inner state of this object
     * @param elapsed the time elapsed since the last update
     */
    void update(const sf::Time &);

    /**
     * @brief render renders any sfml drawable components, using it's inner renderstate
     * @param drawable the drawable object to render
     */
    Renderer &draw(const sf::Drawable &drawable);

    /**
     * @brief render renders any custom object with the "render" method
     * @param renderable the object to render
     * @return itself
     */
    Renderer &render(const Renderable& renderable);

    /**
     * @brief scale scales the next object to render
     * @param nwScale the new scale the use
     */
    Renderer &scale(float nwScale);


    /**
     * @brief translateY translates the current render states by the given y
     * @param yTranslation the y to translate
     * @return this renderer
     */
    Renderer &translate(const sf::Vector2f &translation);

    /**
     * @brief setTexture changes the texture
     * of the renderstates
     */
    Renderer &setTexture(const sf::Texture *texture);

    /**
     * @brief rotate rotates the next objects to render
     * @param angle the angle to rotate
     */
    Renderer &rotateAround(const sf::Vector2f &center, float angle);

    /**
     * @brief rotate rotates all the view
     * @param angle the angle of rotation
     */
    Renderer &rotate(float angle);

    /**
     * @brief push pushes the current renderstate
     * on the stack, all the data of the last renderstate
     * is kept and can be modified without changing
     * the other render states
     */
    Renderer &push();

    /**
     * @brief pop pops the current render states,
     * and changes the current render state to the one under the current
     * throws exception if stack only contains one renderstate
     */
    Renderer &pop();

    /**
     * @brief createShader creates a shader and adds it to the current
     * render state
     * @param shaderId id of the shader in the assets
     * @return
     */
    Renderer &createShader(const sf::Uint64 &shaderId);

    /**
     * @brief setUniform sets a float uniform
     * to the current shader
     * @param name name of the uniform
     * @param value float value of the uniform
     * @return
     */
    Renderer &setUniform(const std::string &name, float value);

    /**
     * @brief setUniform sets a texture uniform
     * @param name name of the uniform
     * @param texture value of the texture
     * @return
     */
    Renderer &setUniform(const std::string &name, const sf::Texture &texture);

    /**
     * @brief useTextureTarget changes the render target
     * to use a texture
     * @return
     */
    Renderer &useTextureTarget();

    /**
     * @brief getTextureTarget returns a copy
     * to the texture that was painted (if it was painted
     * @return
     */
    sf::Texture getTextureTarget();

    /**
     * @brief useWindowTarget changes the render target
     * to directly draw on the window
     * @return
     */
    Renderer &useWindowTarget();

    virtual ~Renderer();
private:

    /**
     * @brief top the current render state
     * @return
     */
    sf::RenderStates &top();

    /**
     * @brief destroyAnimation when a powerup is destroyed, destroys the animtaion linked to it
     * @param animationId the id of the animation to delete
     */
    void destroyAnimation(sf::Uint64 animationId);

    /**
     * @brief assertRectExist
     * @param obj
     * @param width
     * @param height
     * @param fillColor
     * @return
     */
    std::unique_ptr<sf::Shape> &assertRectExist(const PhysicObject *obj, float width, float height, const sf::Color &fillColor);


    /**
     * @brief assertCircleExist
     * @param obj
     * @param radius
     * @param fillColor
     * @return
     */
    std::unique_ptr<sf::Shape> &assertCircleExist(const PhysicObject *obj, float radius, const sf::Color &fillColor);

    /**
     * @brief target the target to use to draw stuff on it
     * (can be a window or a texture)
     */
    sf::RenderTarget *m_target;

    /**
     * @brief m_windowTarget directly draw on the window
     */
    sf::RenderTarget *m_windowTarget;

    /**
     * @brief m_texture texture that can be used to render stuff
     */
    sf::RenderTexture m_textureTarget;

    /**
     * @brief m_shakeTimeout the shake timeout, when at 0 (or less) no need to shake,
     * otherwise, the screen is shaking
     */
    sf::Time m_shakeTimeout;

    /**
     * @brief m_powerupAnimations the animations of all the powerups
     */
    std::unordered_map<sf::Uint64, Animation> m_powerupAnimations;

    /**
     * @brief m_shapes store the shapes to draw
     * in order to avoid having to instanciate
     * them at every draw call
     */
    std::unordered_map<const PhysicObject*, std::unique_ptr<sf::Shape>> m_shapes;

    /**
     * @brief m_stack stack system to be able to modify a
     * render state, push it or pop it
     */
    std::stack<sf::RenderStates> m_stack;

    /**
     * @brief m_shaders all the
     * shaders creatd by the user
     */
    std::stack<sf::Shader*> m_shaders;
};


}
