#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include "SpringSystem.h"
#include "Mass.h"
#include "Spring.h"
#include "Integrators.h"

Mass::Mass(float mass, bool isFixed, int index, State initialState) 
    : mass_(mass), isFixed(isFixed), index(index), currentState(initialState) 
{
    accumulatedForce_ = glm::vec2(0.0f);
   
    if (isFixed) {
        currentState.velocity = glm::vec2(0.0f);
    } else {
        
        applyForce(glm::vec2(0.0f,-9.8f * mass_));
    }
}

void Mass::applyForce(const glm::vec2& force) {
    if(!isFixed){this->accumulatedForce_ += force;}
}

// resetForce
void Mass::resetForce() {
    accumulatedForce_ = glm::vec2(0.0f);
    if (!isFixed) {
        applyForce(glm::vec2(0.0f, -9.8f * mass_));
    }
}

Mass::State Mass::derivative(const State& state) const {
    return { state.velocity, accumulatedForce_ / mass_ };
}

void Mass::updateState(const State& state) {
    currentState = state;
}

