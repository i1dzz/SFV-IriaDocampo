#pragma once

#include <cmath>
#include "ForceGenerator.h"
#include "Vector3D.h"

class ForceGeneratorExplosion : public ForceGenerator
{
public:
    ForceGeneratorExplosion(
        Vector3D centro,
        float radio,
        float K,
        float tau
    )
        : _centro(centro),
        _radio(radio),
        _K(K),
        _tau(tau),
        _tiempo(0.0f),
        _activa(false)
    {}

    // Iniciar o reiniciar la explosion
    void activar()
    {
        _tiempo = 0.0f;
        _activa = true;
    }

    void update(float dt)
    {
        if (_activa)
        {
            _tiempo += dt;

            // A partir de 4*tau la explosión desaparece
            if (_tiempo >= 4.0f * _tau)
                _activa = false;
        }
    }

    void updateForce(Particle* particle) override
    {
        if (!_activa || _tau <= 0.0f)
            return;

        // Vector desde el centro hasta la partícula
        Vector3D diferencia = particle->getPosition() - _centro;

        float distancia = diferencia.magnitude();

        // Fuera del radio no hay fuerza
        if (distancia >= _radio || distancia < 0.0001f)
            return;

        // Intensidad decreciente con el tiempo
        float intensidad =
            (_K / (distancia * distancia)) *
            exp(-_tiempo / _tau);

        // Fuerza radial hacia fuera
        Vector3D fuerza = diferencia * intensidad;

        particle->addForce(fuerza);
    }

private:
    Vector3D _centro;
    float _radio;
    float _K;
    float _tau;

    float _tiempo;
    bool _activa;
};