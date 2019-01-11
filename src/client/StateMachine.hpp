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
 * File:   StateMachine.h
 * Author: azarias
 *
 * Created on 16 octobre 2017, 19:04
 */

#pragma once


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unordered_map>

#include "ClientConf.hpp"
#include "SoundEngine.hpp"
#include "State.hpp"
#include "Provider.hpp"
#include "Renderer.hpp"
#include "widgets/BackgroundParallax.hpp"
#include "src/lib/twin.hpp"

namespace mp {

class ClientApp;

/**
 * @brief The StateMachine class class that holds all the different possible states
 * of the application. it will also handle the states changes
 */
class StateMachine : public sf::NonCopyable, public Renderable {
public:
    /**
     * @brief StateMachine constructor
     */
    StateMachine();


    /**
     * @brief render inherited function
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief initiliaze initializes the blackboard background
     */
    void initiliaze();

    void translate(float nwX, float nwY);

    /**
     * @brief fadeTo does a fade between the current state and the next state
     * @param stateLabel the state to go to while fading
     */
    template<typename STATE, typename ...Args>
    void fadeTo(Args ...args);

    /**
     * @brief goToState changes the state, with an animation
     * @param statelabel thelabel of the state to go to
     * @param dir direction of animation
     * @param data data to pass to the next state
     */
    template<typename STATE, typename ...Args>
    void slideTo(cc::SLIDE_DIRECTION dir, Args... data);

    /**
     * @brief addState adds the state given as template parameter to the list of states (creates a new state object)
     * @param stateLabel the id for the inserted state, will be used to retreive the state later
     */
    template<typename T>
    typename std::enable_if<std::is_base_of<State,T>::value, State&>::type
    addState();

    template<typename STATE>
    bool currentIs();

    /**
     * @brief setCurrentState overriden function, when
     * a state data is directly given in parameter, no need
     * to create one
     * @param stateLabel
     * @param data
     */
    template<typename STATE, typename ...Args>
    void setCurrentState(Args ...data);

    /**
     * @brief getCurrentState a reference to the current state
     * @return a reference to the current state
     */
    const State &getCurrentState() const;

    /**
     * @brief getCurrentState
     * @return non-const version of getCurrentState
     */
    State &getCurrentState();

    /**
     * @brief getStateAt
     * @param index
     * @return
     */
    template<typename STATE>
    STATE &get() const;

    /**
     * @brief getCurrentStateIndex the index of the current state (-1 if no states was set)
     * @return the index of the current state (-1 if no states was set)
     */
    std::size_t getCurrentStateIndex()
    {
        return m_currentState;
    }

    virtual ~StateMachine() override;
private:
    /**
     * @brief states keep in memory all the newly created states
     * using smart pointers in order to delete them when getting out of scope
     */
    std::unordered_map<std::size_t, std::unique_ptr<State>> m_states;

    /**
     * @brief currentStateIndex index of the current state
     */
    std::size_t m_currentState = 0;

    /**
     * @brief m_blackboard the blackboard background
     */
    BackgroundParallax m_background;

    State &getStateFromId(std::size_t state) const;

    friend class Transition;
};

/**
 * @brief The TransitionState class
 * state used when a transition is happening
 * between two states, in order to create
 * an animation
 */
class Transition : public State
{
public:
    /**
     * @brief TransitionState constructor
     */
    Transition();

    /**
     * @brief draw draws the two currently transitioning states
     * @param renderer
     */
   virtual  void render(Renderer &renderer) const override = 0;

    /**
     * @brief update updates the current transition
     * @param elapsed time elapsed since last frame
     */
    void update(const sf::Time &elapsed) override;

    /**
     * @brief progress method that must be delcared
     * in the sub-functions in order to progress
     * the transition state, it must
     * return a boolean to tell wether the progress is finished
     * @param elapsed
     * @return true when the transition is over
     */
    virtual bool progress(const sf::Time &elapsed) = 0;

    /**
     * @brief handleEvent handles the event : the entering state is the one handling the event
     * @param ev
     */
    virtual void handleEvent(const sf::Event &ev) override;

    /**
     * @brief onEnter inherited function
     * @param data
     */
    template<typename STATE, typename ...Args>
    void setup(TransitionData<STATE, Args...> &data);

    /**
     * @brief onBeforeLeaving inherited function
     */
    virtual void onBeforeLeaving() override;
protected:

    /**
     * @brief enteringState access to all the childs transition directly
     * to the state currently entering the transition
     * @return the state associated with the entering state
     */
    State &enteringState() const;

    /**
     * @brief exitingState access to all the childs transition
     * to the state currently exiting the transition
     * @return the state associated with the exiting state id
     */
    State &exitingState() const;

    /**
     * @brief m_tickEnteringState if we need to start
     * updating the state that's going to enter
     * same for the exiting state
     */
    bool m_tickEnteringState = false;
    bool m_tickExistingState = false;

private:
    /**
     * @brief mExitingStateLabel label of the state
     * that is going to leave the scene
     */
    std::size_t m_exitingStateLabel = 0;

    /**
     * @brief mEnteringStateLabel label of the state
     * that is going to enter on the scene
     */
    std::size_t m_enteringStateLabel = 0;

    /**
     * @brief m_switchState function called when the transition
     * is over, and a new state must be active for the state machine
     */
    std::function<void()> m_switchState;
};

/**
 * @brief The SlideTransition class used
 * to create a sliding transition between two states
 * the transition receives the direction data
 * with the 'onEnter' method
 */
class SlideTransition  : public Transition
{
public:
    /**
     * @brief SlideTransition empty constructor
     */
    SlideTransition();

    /**
     * @brief render renders the current sliding transition
     * @param renderer
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief progress moves the current transition
     * @param elapsed
     * @return
     */
    bool progress(const sf::Time &elapsed) override;

    /**
     * @brief onEnter function called when starting the transition
     * @param data containing the information about where to slide
     * and what data to pass to the next state
     */
    template<typename STATE, typename ...Args>
    void onEnter(SlideData<STATE, Args...> &data);

private:


    /**
     * @brief mEnteringTranslate current translating of the
     * entering state
     */
    sf::Vector2f m_enteringTranslate;

    /**
     * @brief mExitingTranslate current translating
     * of the exiting state
     */
    sf::Vector2f m_exitingTranslate;

    /**
     * @brief updateCenters called to update
     * the translation of the transitionning
     * states
     */
    void updateCenters();


    /**
     * @brief mTweening tweening for the
     * center position of the states
     */
    twin::Twin<float> m_tweening;

    /**
     * @brief m_direction direction of the slide
     */
    cc::SLIDE_DIRECTION m_direction;
};

/**
 * @brief The FadeTransition class
 * used to create a fade transition between two states
 * starts with creating two textures and uses a shader
 * to create the fade effect
 */
class FadeTransition : public Transition
{
public:
    /**
     * @brief FadeTransition empty constructor
     */
    FadeTransition();

    /**
     * @brief render inherited function
     * @param renderer renders the fade effect
     */
    void render(Renderer &renderer) const override;

    /**
     * @brief progress update the fade effect
     * @param elapsed time since las frame
     * @return true if the fade effect is over
     */
    bool progress(const sf::Time &elapsed) override;

    /**
     * @brief onEnter when the transition starts
     * @param data the data used to  configure the transition and the state
     */
    template<typename STATE, typename ...Args>
    void onEnter(TransitionData<STATE, Args...> &data);

    ~FadeTransition() override;

private:
    /**
     * @brief m_shader the shader used
     * to create the fade effect
     * is destroyed at the same time as the transition
     */
    sf::Shader *m_shader;

    /**
     * @brief m_fromTexture keep the texture of the state
     * we come from
     */
    sf::Texture m_fromTexture;

    /**
     * @brief m_toTexture keep the texture of the state
     * we go to
     */
    sf::Texture m_toTexture;

    /**
     * @brief m_alpha tweening used
     * to change the alpha uniform of the shader
     */
    twin::Twin<float> m_alpha;

    /**
     * @brief m_background using a sprite
     * to render the texture with the shader
     */
    sf::Sprite m_background;
};


//----------------------------------------------------
// FADE
//----------------------------------------------------
template<typename STATE, typename ...Args>
void FadeTransition::onEnter(TransitionData<STATE, Args...> &data)
{
    Transition::setup(data);

    m_toTexture = pr::renderer()
                        .useTextureTarget()
                        .render(enteringState())
                        .useWindowTarget()
                        .getTextureTarget();

    m_fromTexture = pr::renderer()
                        .useTextureTarget()
                        .render(exitingState())
                        .useWindowTarget()
                        .getTextureTarget();

    m_alpha = twin::makeTwin(0.f, 1.f, sf::milliseconds(400), twin::easing::circOut);
    m_shader->setUniform("progress", 0.f);
    m_shader->setUniform("resolution", sf::Vector2f(SF_ARENA_WIDTH, SF_ARENA_HEIGHT));
    m_shader->setUniform("from", m_fromTexture);
    m_shader->setUniform("to", m_toTexture);
    m_background = sf::Sprite(m_fromTexture);
}

//----------------------------------------------------
// SLIDE
//----------------------------------------------------
template<typename STATE, typename ...Args>
void SlideTransition::onEnter(SlideData<STATE, Args...> &data)
{
    m_enteringTranslate = sf::Vector2f();
    m_exitingTranslate = sf::Vector2f();

    cc::SLIDE_DIRECTION dir = data.direction;

    std::pair<float,float> tweening = {0,0};

    if(dir == cc::SLIDE_DIRECTION::SLIDE_RIGHT || dir == cc::SLIDE_DIRECTION::SLIDE_LEFT){
        tweening.second = SF_ARENA_WIDTH;
    }else if(dir == cc::SLIDE_DIRECTION::SLIDE_DOWN || dir == cc::SLIDE_DIRECTION::SLIDE_UP){
        tweening.second = SF_ARENA_HEIGHT;
    }

    m_tweening = twin::makeTwin(tweening.first, tweening.second, cc::Times::transitionTime, twin::easing::backInOut);
    m_direction = dir;
    updateCenters();

    Transition::setup(static_cast<TransitionData<STATE, Args...>&>(data));
}

//----------------------------------------------------
// TRANSITION
//----------------------------------------------------
template<typename STATE, typename ...Args>
void Transition::setup(TransitionData<STATE, Args...> &data)
{
    m_enteringStateLabel = data.enteringStateLabel;
    m_exitingStateLabel = data.exitingStateLabel;
    m_tickEnteringState = data.updateEnteringState;
    m_tickExistingState = data.updateExistingState;
    m_switchState = [data, this](){
        std::apply(&StateMachine::setCurrentState<STATE, Args...>,
           std::tuple_cat(std::make_tuple(std::ref(pr::stateMachine())),
           data.enteringData
        ));
    };
}


//-------------
// STATEMACHINE
//-------------
template<typename STATE, typename ...Args>
void StateMachine::fadeTo(Args ...args)
{
    std::size_t stateLabel = typeid(STATE).hash_code();
    get<STATE>().onBeforeEnter();
    TransitionData<STATE, Args...> td;
    td.enteringStateLabel = stateLabel;
    td.exitingStateLabel = m_currentState;
    td.enteringData = std::make_tuple(std::forward(args)...);
    setCurrentState<FadeTransition>(td);
}

template<typename STATE, typename ...Args>
void StateMachine::slideTo(cc::SLIDE_DIRECTION dir, Args ...data)
{
    SlideData<STATE, Args...> td;
    get<STATE>().onBeforeEnter();
    td.enteringStateLabel = typeid (STATE).hash_code();
    td.exitingStateLabel = m_currentState;
    td.direction = dir;
    td.enteringData = std::make_tuple(std::forward<Args>(data)...);
    setCurrentState<SlideTransition>(td);
    pr::soundEngine().playSound(Assets::Sounds::Rollover1);
}

template<typename T>
typename std::enable_if<std::is_base_of<State,T>::value, State&>::type
StateMachine::addState()
{
    return *(m_states[typeid(T).hash_code()] = std::make_unique<T>());
}

template<typename STATE>
bool StateMachine::currentIs()
{
    return m_currentState == typeid(STATE).hash_code();
}

template<typename STATE, typename ...Args>
void StateMachine::setCurrentState(Args...data)
{
    m_background.setOffset();
    if(m_currentState != 0)
        static_cast<STATE*>(m_states[m_currentState].get())->onBeforeLeaving();
    std::size_t  oldState = m_currentState;
    m_currentState = typeid (STATE).hash_code();
    static_cast<STATE*>(m_states[m_currentState].get())->onEnter(data...);
    if(oldState != 0)
        m_states[oldState]->onAfterLeaving();
}

template<typename STATE>
STATE &StateMachine::get() const
{
    std::size_t index = typeid(STATE).hash_code();
    if(m_states.find(index) == m_states.end())
        throw std::out_of_range("Index not found");

    auto found = m_states.find(index);
    if(found == m_states.end()) throw "State index not found";
    return static_cast<STATE&>(*found->second);
}

}

