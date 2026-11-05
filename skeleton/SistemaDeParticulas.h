
#pragma once

#include <vector>
#include "Particle.h"
#include "ForceGenerator.h"
#include "GeneradorDeParticulas.h"

class SistemaDeParticulas
{
private:
    struct Emisor
    {
        GeneradorDeParticulas* generador;
        std::vector<ForceGenerator*> fuerzas;
    };

    std::vector<Emisor> emisores;
    std::vector<ForceGenerator*> generadoresFuerza;

public:
    SistemaDeParticulas() = default;
    ~SistemaDeParticulas();

    void addForceGenerator(ForceGenerator* fuerza);

    void addParticleGenerator(
        GeneradorDeParticulas* generador,
        const std::vector<ForceGenerator*>& fuerzas
    );

    void update(double dt);
};
