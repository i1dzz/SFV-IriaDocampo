
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
        bool activo = true;
    };

    std::vector<Emisor> emisores;
    std::vector<ForceGenerator*> generadoresFuerza;

public:
    SistemaDeParticulas() = default;
    ~SistemaDeParticulas();

    void addForceGenerator(ForceGenerator* fuerza);

    void addParticleGenerator( GeneradorDeParticulas* generador, const std::vector<ForceGenerator*>& fuerzas);

    void update(double dt);

    void activarEmisor(GeneradorDeParticulas* generador);
    void desactivarEmisor(GeneradorDeParticulas* generador);

    bool SistemaDeParticulas::isActivo(GeneradorDeParticulas* generador)
    {
        auto it = std::find_if(  emisores.begin(),
            emisores.end(),
            [generador](const Emisor& emisor) {
                return emisor.generador == generador;
            }
        );

        if (it != emisores.end())
            return it->activo;

        return false;
    }
};
