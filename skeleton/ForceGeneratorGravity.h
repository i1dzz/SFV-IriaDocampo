#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class ForceGeneratorGravity : public ForceGenerator
{
public:
    ForceGeneratorGravity(Vector3D gravity): _gravity(gravity) {}

    void updateForce(Particle* particle) override {


        particle->addForce(_gravity);

    }

private:
    Vector3D _gravity;
};