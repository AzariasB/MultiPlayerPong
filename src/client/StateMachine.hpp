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
#include "widgets/BackgroundParallax.hpp"
#include "transitions/SlideTransition.hpp"
#include "transitions/FadeTransition.hpp"

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
     * @brief slideTo expanded version of the previous method
     * @param statelabel
     * @param dir
     */
    template<typename STATE>
    void slideTo(SlideData::SLIDE_DIRECTION dir);

    /**
     * @brief fadeTo does a fade between the current state and the next state
     * @param stateLabel the state to go to while fading
     */
    template<typename STATE>
    void fadeTo();

    /**
     * @brief goToState changes the state, with an animation
     * @param statelabel thelabel of the state to go to
     * @param dir direction of animation
     * @param data data to pass to the next state
     */
    template<typename STATE, typename T>
    void slideTo(SlideData::SLIDE_DIRECTION dir, const T & data);

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
     * @brief setCurrentState changes the current state, calls onLeave and onEnter for the current state and the new state
     * @param stateLabel id of the label to set, if the id is not in the bound of the known states, throws an error
     */
    template<typename STATE>
    void setCurrentState();

    /**
     * @brief setCurrentState sets the current state, and passes some data to the entering state
     * @param stateLabel id of the label to set
     * @param data data to pass to the entering state
     */
    template<typename STATE, typename T>
    void setCurrentState(const T &data);

    /**
     * @brief setCurrentState overriden function, when
     * a state data is directly given in parameter, no need
     * to create one
     * @param stateLabel
     * @param data
     */
    template<typename STATE>
    void setCurrentState(BaseStateData &data);

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
    State &get() const;

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

    /**
     * @brief setStateFromId used only by friend classes who know what they are doing
     * to change the current state, based on the id of the state
     * @param classId id of the class to change
     */
    void setStateFromId(std::size_t classId);

    template<typename T>
    void setStateFromId(std::size_t index, const T &data);

    /**
     * @brief getStateFromId used only by friend class who know what they are doing
     * to get a reference to a state, from the state's ID
     * @param index index of the class searched for
     * @return a reference to the class if found, an exception otherwise
     */
    State &getStateFromId(std::size_t index) const;


    friend class Transition;
};

template<typename STATE>
void StateMachine::slideTo(SlideData::SLIDE_DIRECTION dir)
{
    std::size_t statelabel = typeid(STATE).hash_code();
    get<STATE>().onBeforeEnter();
    SlideData td;
    td.enteringStateLabel = statelabel;
    td.exitingStateLabel = m_currentState;
    td.direction = dir;
    setCurrentState<SlideTransition>(&td);
    pr::soundEngine().playSound(Assets::Sounds::Rollover1);
}

template<typename STATE>
void StateMachine::fadeTo()
{
    std::size_t stateLabel = typeid(STATE).hash_code();
    get<STATE>().onBeforeEnter();
    TransitionData td;
    td.enteringStateLabel = stateLabel;
    td.exitingStateLabel = m_currentState;
    setCurrentState<FadeTransition>(&td);
}

template<typename STATE, typename T>
void StateMachine::slideTo(SlideData::SLIDE_DIRECTION dir, const T & data)
{
    SlideData td;
    td.enteringStateLabel = typeid (STATE).hash_code();
    td.exitingStateLabel = m_currentState;
    td.direction = dir;
    td.enteringData = std::make_unique<StateData<T>>(data);
    setCurrentState<SlideTransition>(&td);
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

template<typename STATE>
void StateMachine::setCurrentState()
{
    std::size_t stateLabel = typeid(STATE).hash_code();
    m_background.setOffset();
    if (m_currentState != 0)
        m_states[m_currentState]->onBeforeLeaving();
    m_currentState = stateLabel;
    BaseStateData dat;
    m_states[m_currentState]->onEnter(&dat);
}

template<typename STATE, typename T>
void StateMachine::setCurrentState(const T &data)
{
    std::size_t stateLabel = typeid (STATE).hash_code();
    if (m_currentState != 0) m_states[stateLabel]->onBeforeLeaving();
    m_currentState = stateLabel;

    StateData<T> dat(data);
    m_states[m_currentState]->onEnter(&dat);
}

template<typename STATE>
void StateMachine::setCurrentState(BaseStateData &data)
{
    m_background.setOffset();
    m_states[m_currentState]->onBeforeLeaving();
    m_currentState = typeid (STATE).hash_code();
    m_states[m_currentState]->onEnter(&data);
}

template<typename STATE>
State &StateMachine::get() const
{
    std::size_t index = typeid(STATE).hash_code();
    if(m_states.find(index) == m_states.end())
        throw std::out_of_range("Index not found");

    auto found = m_states.find(index);
    if(found == m_states.end()) throw "State index not found";
    return *found->second;
}

template<typename T>
void StateMachine::setStateFromId(std::size_t index, const T &data)
{
    m_background.setOffset();
    m_states[m_currentState]->onBeforeLeaving();
    m_currentState = index;

    StateData<T> dat(data);
    m_states[m_currentState]->onEnter(&dat);
}

}

