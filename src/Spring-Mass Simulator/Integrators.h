#pragma once
#include "Mass.h"

namespace Integrators {
    inline Mass::State eulerStep(const Mass::State& s, float dt,
        const Mass& mass) {
        auto dsdt = mass.derivative(s);
        return {
            s.position + dsdt.position * dt,
            s.velocity + dsdt.velocity * dt
        };
    }

    inline Mass::State midPointStep(const Mass::State& s, float dt, const Mass& mass) {
        auto k1 = mass.derivative(s);

        glm::vec2 midPointPos = s.position + k1.position * (dt / 2.0f);
        glm::vec2 midPointVel = s.velocity + k1.velocity * (dt / 2.0f);
        Mass::State midPoint = { midPointPos, midPointVel };

        auto k2 = mass.derivative(midPoint);

        return {
            s.position + k2.position * dt,
            s.velocity + k2.velocity * dt
        };
    }

    inline Mass::State rk4Step(const Mass::State& s, float dt, const Mass& mass) {
        auto k1 = mass.derivative(s);

        glm::vec2 midPointPos = s.position + k1.position * (dt / 2.0f);
        glm::vec2 midPointVel = s.velocity + k1.velocity * (dt / 2.0f);
        Mass::State midPoint = { midPointPos, midPointVel };

        auto k2 = mass.derivative(midPoint);

        midPointPos = s.position + k2.position * (dt / 2.0f);
        midPointVel = s.velocity + k2.velocity * (dt / 2.0f);
        midPoint = { midPointPos, midPointVel };

        auto k3 = mass.derivative(midPoint);

        midPointPos = s.position + k3.position * dt;
        midPointVel = s.velocity + k3.velocity * dt;
        midPoint = { midPointPos, midPointVel };

        auto k4 = mass.derivative(midPoint);

        return {
            s.position + (k1.position + 2.0f * k2.position + 2.0f * k3.position + k4.position) * (dt / 6.0f),
            s.velocity + (k1.velocity + 2.0f * k2.velocity + 2.0f * k3.velocity + k4.velocity) * (dt / 6.0f)
        };
    }

}