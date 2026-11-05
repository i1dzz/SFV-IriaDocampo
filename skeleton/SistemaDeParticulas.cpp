
#include "SistemaDeParticulas.h"
#include <algorithm>

SistemaDeParticulas::~SistemaDeParticulas()
{
    // Primero destruir los emisores y sus particulas
    for (Emisor& emisor : emisores)
        delete emisor.generador;

    emisores.clear();

    // Despues destruir los generadores de fuerzas
    for (ForceGenerator* fuerza : generadoresFuerza)
        delete fuerza;

    generadoresFuerza.clear();
}

void SistemaDeParticulas::addForceGenerator(ForceGenerator* fuerza)
{
    if (fuerza != nullptr &&
        std::find(generadoresFuerza.begin(),
            generadoresFuerza.end(),
            fuerza) == generadoresFuerza.end())
    {
        generadoresFuerza.push_back(fuerza);
    }
}

void SistemaDeParticulas::addParticleGenerator(
    GeneradorDeParticulas* generador,
    const std::vector<ForceGenerator*>& fuerzas)
{
    if (generador != nullptr)
    {
        emisores.push_back({ generador, fuerzas });
    }
}


void SistemaDeParticulas::update(double dt)
{
    // Actualizar los generadores de fuerzas
    for (ForceGenerator* fuerza : generadoresFuerza)
        fuerza->update(static_cast<float>(dt));

    // Actualizar únicamente los emisores activos
    for (Emisor& emisor : emisores)
    {
        if (emisor.activo)
            emisor.generador->update(dt, emisor.fuerzas);
    }
}
void SistemaDeParticulas::activarEmisor(GeneradorDeParticulas* generador)
{
    for (Emisor& emisor : emisores)
    {
        if (emisor.generador == generador)
            emisor.activo = true;
    }
}

void SistemaDeParticulas::desactivarEmisor(GeneradorDeParticulas* generador)
{
    for (Emisor& emisor : emisores)
    {
        if (emisor.generador == generador)
            emisor.activo = false;
    }
}
