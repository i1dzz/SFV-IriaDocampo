#pragma once
#pragma once

#include "ForceGenerator.h"
#include "Vector3D.h"

class ForceGeneratorWind : public ForceGenerator
{
public:

    ForceGeneratorWind(Vector3D velocidadViento, float k1, float k2 = 0.0f)
        : _velocidadViento(velocidadViento), _k1(k1), _k2(k2)
    {}

    void updateForce(Particle* particle) override
    {
        // Diferencia entre velocidad del viento y velocidad de la particula
        Vector3D diferencia = _velocidadViento - particle->getVelocity();

        // Componente lineal
        Vector3D fuerza = diferencia * _k1;

        // Componente cuadratica
        fuerza = fuerza + diferencia * (diferencia.magnitude() * _k2);

        particle->addForce(fuerza);
    }

private:

    Vector3D _velocidadViento;
    float _k1;
    float _k2;
};