#pragma once

#include "Particle.h"

class Proyectil : public Particle
{
public:

    Proyectil(
        const physx::PxTransform& camera,
        float velSim,
        float masaReal,
        float velReal,
        float signo
    );

};