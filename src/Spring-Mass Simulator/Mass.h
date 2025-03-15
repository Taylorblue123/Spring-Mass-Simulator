
#pragma once
#include <glm/glm.hpp>

class Mass {
public:
    struct State {
        glm::vec2 position;
        glm::vec2 velocity;
    };

    Mass(float mass, bool isFixed, int index, State initialState);
    
    void applyForce(const glm::vec2& force);
    void resetForce();
    State derivative(const State& state) const; 
    void updateState(const State& state);

    State currentState;
    bool isFixed;
    int index; // index of the mass in the spring system

private:
    float mass_;
    glm::vec2 accumulatedForce_; 

};