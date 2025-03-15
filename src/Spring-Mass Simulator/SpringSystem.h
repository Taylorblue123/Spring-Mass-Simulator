#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Mass.h"
#include "Spring.h"

class SpringSystem {
public:
    SpringSystem(
        float start_x,
        float total_length,
        int num_nodes,
        float spring_mass,
        float object_mass,
        float k,
        float damping
    );

    void StepSimulation(float dt, int method);

    const std::vector<glm::vec2>& GetNodePositions() const; 
    const std::vector<Spring>& GetSprings() const;
    const std::vector<Mass>& GetMasses() const; 

private:
    std::vector<Mass> masses_;
    std::vector<Spring> springs_;
    std::vector<glm::vec2> node_positions_; 
    
    float start_x_;
    float total_length_;
    int num_nodes_;
    float spring_mass_;
    float object_mass_;
    float k_;
    float damping_;
};