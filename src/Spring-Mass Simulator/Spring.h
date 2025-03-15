#pragma once
#include <glm/glm.hpp>
#include "Mass.h"

class Spring {
public:
    Spring(float k, float dampingFactor, float restLength, Mass* mass1, Mass* mass2);
    void applyForceToMasses();

    Mass* getMass1() const;
    Mass* getMass2() const;

private:
    float k_;
    float dampingFactor_;
    float restLength_; 
    Mass* mass1_;
    Mass* mass2_;
};