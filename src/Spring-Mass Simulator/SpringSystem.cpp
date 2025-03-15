#include "SpringSystem.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <glm/glm.hpp>
#include "Integrators.h"


SpringSystem::SpringSystem(
    float start_x,
    float total_length,
    int num_nodes,
    float spring_mass,
    float object_mass,
    float k,
    float damping
) : start_x_(start_x), total_length_(total_length), num_nodes_(num_nodes),
    spring_mass_(spring_mass), object_mass_(object_mass), k_(k), damping_(damping) 
{
    // check if the number of nodes is at least 2
    if (num_nodes_ < 2) {
        throw std::invalid_argument("Number of nodes must be at least 2");
    }

    // calculate the spacing between nodes
    const float node_spacing = total_length_ / (num_nodes_ - 1);

    // create masses
    for (int i = 0; i < num_nodes_; ++i) {
        const bool isFixed = (i == 0);
        const float mass = (i == num_nodes_-1) ? 
            (spring_mass_ / num_nodes_ + object_mass_) : 
            (spring_mass_ / num_nodes_);

        const glm::vec2 position(start_x_ + i * node_spacing, 0.0f);
        const Mass::State initialState{position, glm::vec2(0.0f)};

        masses_.emplace_back(mass, isFixed, i, initialState);
        node_positions_.push_back(position);
    }

    // create springs
    for (int i = 0; i < num_nodes_ - 1; ++i) {
        springs_.emplace_back(
            k_, 
            damping_,
            node_spacing,  // rest length
            &masses_[i],   // mass1
            &masses_[i+1]  // mass2
        );
    }
}


void SpringSystem::StepSimulation(float dt, int method){


    //Step the simulation forward by dt seconds
    //Temporary storage for the new state of the masses 
    std::vector<Mass::State> newStates(masses_.size());

    //Apply the forces to the masses
    for (int i = 0; i < num_nodes_; i++) {
        masses_[i].resetForce();
    }

    //Iterate each spring to apply the springs & damping forces for each nodes
    for (int i = 0; i < num_nodes_ - 1; i++) {
        springs_[i].applyForceToMasses();
    }

    //Integrate the masses
    for (int i = 0; i < num_nodes_; i++) {
        if (!masses_[i].isFixed) {
            if (method == 0) {
                //Euler Integration
                newStates[i] = Integrators::eulerStep(masses_[i].currentState, dt, masses_[i]);
            } else if (method == 1) {
                //Midpoint Integration
                newStates[i] = Integrators::midPointStep(masses_[i].currentState, dt, masses_[i]);
            } else if (method == 2) {
                //RK4 Integration
                newStates[i] = Integrators::rk4Step(masses_[i].currentState, dt, masses_[i]);
            }
        } else {
            newStates[i] = masses_[i].currentState;
        }
    }

    //Update the state of the masses
    for (int i = 0; i < num_nodes_; i++) {
        masses_[i].updateState(newStates[i]);
        node_positions_[i] = masses_[i].currentState.position;
    }
    
}


const std::vector<glm::vec2>& SpringSystem::GetNodePositions() const {
    return node_positions_;
}

const std::vector<Spring>& SpringSystem::GetSprings() const {
    return springs_;
}

// Added implementation for GetMasses method
const std::vector<Mass>& SpringSystem::GetMasses() const {
    return masses_;
}