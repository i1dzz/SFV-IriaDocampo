#pragma once

#include<vector>
#include "Scene.h"
#include "Particle.h"
#include "GeneradorDeParticulas.h"
#include "ForceGeneratorGravity.h"
#include "ForceGeneratorWInd.h"
#include "ForceGenerator.h"

class P2S_Scene :
    public Scene
{

public: 

    explicit P2S_Scene(std::string name)
        : Scene(std::move(name))
    {}

    void init() override
    {
        modelo = new Particle(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 0.5f
        );

        fuente = new GeneradorDeParticulas(
            Vector3D(0.0f, 80.0f, 0.0f),
            Vector3D(0.0f, 1.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),  5.0f, 1.0f, modelo  );

        gravedadNormal = new ForceGeneratorGravity(
            Vector3D(0.0f, -10.0f, 0.0f)
        );

       viento = new ForceGeneratorWind(
            Vector3D(10.0f, 0.0f, 0.0f),
            2.0f
        );

        fuerzasFuente.push_back(viento);

        fuerzasFuente.push_back(gravedadNormal);
    }

    void update(double dt) override
    {
        if (fuente != nullptr) 
            fuente->update(dt, fuerzasFuente);
    }

    void keyPress(unsigned char key,
        const physx::PxTransform& camera) override
    {
        std::cout << "Key pressed: " << key << std::endl;

       
    }

    void cleanup() override
    {
        if (fuente != nullptr)
        {
            fuente->cleanup();
            delete fuente;
            fuente = nullptr;
        }

        if (modelo != nullptr)
        {
            delete modelo;
            modelo = nullptr;
        }
        delete gravedadNormal;
        gravedadNormal = nullptr;
        delete viento;
        viento = nullptr;

    }

private:
    std::string display_text;

    Particle* modelo = nullptr;
    GeneradorDeParticulas* fuente = nullptr;

    ForceGeneratorGravity* gravedadNormal = nullptr;
    ForceGeneratorWind* viento = nullptr; 
    std::vector<ForceGenerator*> fuerzasFuente;

    
};

