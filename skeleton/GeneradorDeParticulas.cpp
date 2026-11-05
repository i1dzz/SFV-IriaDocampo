#include "GeneradorDeParticulas.h"
GeneradorDeParticulas::GeneradorDeParticulas(Vector3 vel, Vector3 dir, Vector3 pos) : _vel(vel), _dir(dir), _pos(pos)
{
	_vida = 65.0f; 
    _minBounds = Vector3(-100.0f, -100.0f, -100.0f);
    _maxBounds = Vector3(100.0f, 100.0f, 100.0f);
	
}

GeneradorDeParticulas::GeneradorDeParticulas( Vector3D vel, Vector3D dir, Vector3D pos, float vida, float dispersion, Particle* pM) : _vel(vel),  _dir(dir),  _pos(pos),  _vida(vida),  _dispersion(dispersion), pModel(pM)
{
    _minBounds = Vector3(-100.0f, -100.0f, -100.0f);
    _maxBounds = Vector3(100.0f, 100.0f, 100.0f);

}

void GeneradorDeParticulas::cleanup()
{
    for (auto& p : particulas)
    {
        if (p.first != nullptr) {

            delete p.first;
            p.first = nullptr;
        }
    }

    particulas.clear();
}

GeneradorDeParticulas::~GeneradorDeParticulas()
{
    cleanup();
}

void GeneradorDeParticulas::update(  double dt, const std::vector<ForceGenerator*>& fuerzas)
{

   // Direccion y velocidad media
    Vector3D media = _dir * _vel.magnitude();

    // Variacion de velocidad mediante distribucion normal
    Vector3D velocidad(
        media._x + distX(gen) * _dispersion,
        media._y + distY(gen) * _dispersion,
        media._z + distZ(gen) * _dispersion );

    // Variacion de posicion mediante distribucion uniforme
    Vector3D posicion(
        _pos.x + distUniforme(gen),
        _pos.y + distUniforme(gen),
        _pos.z + distUniforme(gen)
    );

    if (pModel != nullptr)
    {
        Particle* nueva = pModel->clone();

        nueva->setPosition(posicion);
        nueva->setVelocity(velocidad);

        particulas.push_back({ nueva, 0.0f });
    }

    //Actualizar particulas iterando
    auto it = particulas.begin();

    while (it != particulas.end())
    {
        Particle* p = it->first;

        it->second += static_cast<float>(dt);

        // Aplicar todos los generadores de fuerzas
        for (ForceGenerator* fuerza : fuerzas)
        {
            fuerza->updateForce(p);
        }

        p->integrate(dt);

        if (it->second >= _vida)
        {
            p->release();
            delete p;
            p = nullptr;

            it = particulas.erase(it);
        }
        else
        {
            ++it;
        }
    }
}