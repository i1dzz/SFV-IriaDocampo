#pragma once


#include "Particle.h"

//Clase abstracta para los generadores de fuerzas
class ForceGenerator
{
public:

    virtual void updateForce(Particle* particle) = 0;
    virtual void update(float dt) {}
    virtual ~ForceGenerator() = default;
};
