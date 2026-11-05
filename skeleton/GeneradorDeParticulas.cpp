#include "GeneradorDeParticulas.h"
GeneradorDeParticulas::GeneradorDeParticulas(Vector3 vel, Vector3 dir, Vector3 pos) : _vel(vel), _dir(dir), _pos(pos)
{
	_vida = 65.0f; 
    _minBounds = Vector3(-100.0f, -100.0f, -100.0f);
    _maxBounds = Vector3(100.0f, 100.0f, 100.0f);
	
}

void GeneradorDeParticulas::cleanup()
{
    for (auto p : particulas)
    {
        if (p.first) {

            p.first->release();
            p.first = nullptr;
        }
       // delete p.first.d;
    }

    particulas.clear();
}


void 

GeneradorDeParticulas::update(double dt)
{

    Vector3D media = _dir * _vel.magnitude(); // calculo de la velocidad aleatoria

    Vector3D velocidad( media._x + distX(gen), media._y + distY(gen), media._z + distZ(gen));


    Particle* p = new Particle(_pos, velocidad, Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 20.0f,  0.75f);

    particulas.push_back({ p, 0.0f });

    // 2. Actualizar y eliminar partículas
    auto it = particulas.begin();

    while (it != particulas.end())
    {
        Particle* p = it->first;
        it->second += static_cast<float>(dt);

        p->integrate(dt);

        Vector3D pos = p->getPosition();

        bool morir = it->second >= _vida;

        bool fuera = pos._x < _minBounds._x || pos._x > _maxBounds._x ||
                     pos._y < _minBounds._y || pos._y > _maxBounds._y ||
                     pos._z < _minBounds._z || pos._z > _maxBounds._z;
            
        if (morir || fuera)
        {
            p->release();
            p = nullptr;

            it = particulas.erase(it);
        }
        else
        {
            ++it;
        }
    }
}