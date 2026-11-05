#pragma once
#include<cmath>
#include "ForceGeneratorWind.h"

class ForceGeneratorVortex : public ForceGeneratorWind
{
public:

    ForceGeneratorVortex(
        Vector3D centro,
        float radio,
        float K,
        float k1,
        float k2 = 0.0f
    )
        : ForceGeneratorWind(Vector3D(0, 0, 0), k1, k2),
        _centro(centro),
        _radio(radio),
        _K(K)
    {}

protected:

    Vector3D getWindVelocity(Particle* particle) const override
    {
        Vector3D posicion = particle->getPosition();

        // Vector desde el centro hasta la particula
        Vector3D diferencia = posicion - _centro;

        // Distancia al centro en el plano XZ
        float distancia = sqrt(
            diferencia._x * diferencia._x +
            diferencia._z * diferencia._z
        );

        // Fuera del radio de influencia no hay viento
        if (distancia > _radio)
            return Vector3D(0, 0, 0);

        // Velocidad tangencial del torbellino
        return Vector3D(
            -_K * diferencia._z,
            0.0f,
            _K * diferencia._x
        );
    }

private:

    Vector3D _centro;
    float _radio;
    float _K;
};