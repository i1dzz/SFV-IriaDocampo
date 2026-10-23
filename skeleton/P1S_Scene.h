
#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

class P1S_Scene : public Scene
{
public:
    explicit P1S_Scene(std::string name)
        : Scene(std::move(name))
    {}

    void init() override
    {
       
    }

    void update(double dt) override
    {
        // actualizar todos los proyectiles
        for (Particle* p : proyectiles)
        {
            if (p != nullptr)
                p->integrate(dt);
        }

       
    }

    void keyPress(unsigned char key,
        const physx::PxTransform& camera) override
    {
        std::cout << "Key pressed: " << key << std::endl;

        if (key == '1')
        {
            
            disparar(camera, 100.0f, 0.008f, 800.0f,
                1.0f);
        }
        else if (key == '2')
        {
            disparar(camera, 55.0f, 0.05f, 100.0f,
                1.0f);
        }
        else if (key == '3')
        {
            disparar(camera, 65.0f, 0.05f, 100.0f,
                -1.0f);
        }
        else if (key == 'r' || key == 'R')
        {
            // eliminar todos los proyectiles
            for (Particle* p : proyectiles)
                p->release(); 

            proyectiles.clear();
        }
    }

    void cleanup() override
    {
        for (Particle* p : proyectiles)
            p->release();

        proyectiles.clear();
    }

private:

    std::vector<Particle*> proyectiles;

    std::string display_text;

    
    void disparar(const physx::PxTransform& camera,
        float velSim, float masaReal, float velReal, float signo)
    {
        physx::PxVec3 dirCam = camera.q.rotate(physx::PxVec3(0.0f, 0.0f, -1.0f));

        dirCam.normalize();

        Vector3D direccion(dirCam);
        Vector3D iniVel = direccion * velSim;

        // mSim = mReal * (vReal / vSim)^2
        float masaSim = masaReal * (velReal / velSim) * (velReal / velSim);

        // ajustar la gravedad para mantener una trayectoria
        const float g = 9.81f;

        float gSim = signo * g * (velSim / velReal) * (velSim / velReal);

        Vector3D aceleracion(0.0f, -gSim, 0.0f);

        // hay que evitar que la esfera aparezca dentro de la camara
        Vector3D iniPos(camera.p.x + direccion._x * 2.0f, camera.p.y + direccion._y * 2.0f, camera.p.z + direccion._z * 2.0f
        );

        Particle* p = new Particle(iniPos, iniVel, aceleracion, 1.0f);

        p->setMass(masaSim);

        proyectiles.push_back(p);

        std::cout << "Proyectil creado. masa simulada: "
            << masaSim << std::endl;
    }
};

