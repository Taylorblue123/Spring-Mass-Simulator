#include "Spring.h"
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include "Mass.h"
#include "Integrators.h"
#include "SpringSystem.h"

Spring::Spring(float k, float dampingFactor, float restLength, Mass* mass1, Mass* mass2) 
    : k_(k), dampingFactor_(dampingFactor), restLength_(restLength), 
      mass1_(mass1), mass2_(mass2) {} 

void Spring::applyForceToMasses() {
    glm::vec2 delta = mass2_->currentState.position - mass1_->currentState.position;
    float currentLength = glm::length(delta);
    if (currentLength < 1e-5) return;

    glm::vec2 dir = delta / currentLength;

    // Hooke's Law: F = k * Δx 
    float springForce = k_ * (currentLength - restLength_);

    // 阻尼力与相对速度反向
    float velDot = glm::dot(mass2_->currentState.velocity - mass1_->currentState.velocity, dir);
    float dampingForce = -dampingFactor_ * velDot;

    glm::vec2 totalForce = (springForce - dampingForce) * dir;

    mass1_->applyForce(totalForce);
    mass2_->applyForce(-totalForce);
}

Mass* Spring::getMass1() const {
    return mass1_;
}

Mass* Spring::getMass2() const {
    return mass2_;
}
