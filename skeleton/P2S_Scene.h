#pragma once
#include "Scene.h"
#include "Particle.h"
#include "GeneradorDeParticulas.h"

class P2S_Scene :
    public Scene
{

public: 

    explicit P2S_Scene(std::string name)
        : Scene(std::move(name))
    {}

    void init() override
    {
        fuente = new GeneradorDeParticulas(
            Vector3D(0.0f, 50.0f, 0.0f),  // velocidad media
            Vector3D(0.0f, 1.0f, 0.0f),   // apuntan hacia arriba
            Vector3D(0.0f, 0.0f, 0.0f)   
        );
    }

    void update(double dt) override
    {
        // actualizar todos los proyectiles
        for (Particle* p : proyectiles)
        {
            if (p != nullptr)
                p->integrate(dt);
        }

        if(fuente != nullptr) fuente->update(dt);
    }

    void keyPress(unsigned char key,
        const physx::PxTransform& camera) override
    {
        std::cout << "Key pressed: " << key << std::endl;

       
    }

    void cleanup() override
    {
        for (Particle* p : proyectiles)
            p->release();
        if (fuente != nullptr)
        {
            fuente->cleanup();
            delete fuente;
            fuente = nullptr;
        }
        proyectiles.clear();
    }

private:

    std::vector<Particle*> proyectiles;

    std::string display_text;

    GeneradorDeParticulas* fuente = nullptr;
};

