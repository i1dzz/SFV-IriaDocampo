
#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "Particle.h"
#include "Proyectil.h"

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
        for (Proyectil* p : proyectiles)
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
            for (Proyectil* p : proyectiles)
                p->release(); 

            proyectiles.clear();
        }
    }

    void cleanup() override
    {
        for (Proyectil* p : proyectiles)
            p->release();

        proyectiles.clear();
    }

private:

    std::vector<Proyectil*> proyectiles;

    std::string display_text;

    
    void disparar(
        const physx::PxTransform& camera,
        float velSim,
        float masaReal,
        float velReal,
        float signo
    )
    {
        Proyectil* p = new Proyectil(
            camera,
            velSim,
            masaReal,
            velReal,
            signo
        );

        proyectiles.push_back(p);

        std::cout << "Proyectil creado. masa simulada: "
            << p->getMass() << std::endl;
    }
};

