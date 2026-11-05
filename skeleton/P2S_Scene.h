#pragma once

#include<vector>
#include "Scene.h"
#include "Particle.h"
#include "GeneradorDeParticulas.h"
#include "ForceGeneratorGravity.h"
#include "ForceGeneratorWind.h"
#include "ForceGeneratorVortex.h"
#include "ForceGeneratorExplosion.h"
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
        //Modelo de particula para los generadores
        modelo = new Particle(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 0.5f  , Vector4(0.0f, 0.0f, 0.7f, 0.5f));

        //Gen1: Fuente con gravedad y viento
        fuente = new GeneradorDeParticulas(
            Vector3D(0.0f, 80.0f, 0.0f),
            Vector3D(0.0f, 1.0f, 0.0f),
            Vector3D(-50.0f, -30.0f, 0.0f),  5.0f, 1.0f, modelo  );

        gravedadNormal = new ForceGeneratorGravity(Vector3D(0.0f, -10.0f, 0.0f));
        viento = new ForceGeneratorWind(Vector3D(5.0f, 0.0f, 0.0f), 2.0f );

        fuerzasFuente.push_back(viento);
        fuerzasFuente.push_back(gravedadNormal);

        //Gen2: torbellino
       // modelo->setColor(Vector4(0.7f, 0.7f, 0.7f, 0.8f)); 
        torbellinoGen = new GeneradorDeParticulas(
            Vector3D(0.0f, 80.0f, 0.0f),
            Vector3D(0.0f, 1.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f), 5.0f, 2.0f, 
            
            new Particle(
                Vector3D(0.0f, 0.0f, 0.0f),
                Vector3D(0.0f, 0.0f, 0.0f),
                Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 0.5f, Vector4(0.7f, 0.7f, 0.7f, 0.5f)));
        torbellino =
            new ForceGeneratorVortex(
                Vector3D(0, 0, 0), // Centro
                100.0f,            // Radio de influencia
                5.0f,              // Intensidad k
                2.0f               // Rozamiento
            );

        fuerzasTorbellino.push_back(torbellino); 


        //Gen3: explosion
        //modelo->setColor(Vector4(1.0f, 0.5f, 0.0f, 0.8f));
        explosionGen = new GeneradorDeParticulas(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, -30.0f, -50.0f), 1.0f, 2.0f, 
            
            new Particle(
                Vector3D(0.0f, 0.0f, 0.0f),
                Vector3D(0.0f, 0.0f, 0.0f),
                Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 0.5f, Vector4(1.0f, 0.7f, 0.0f, 0.5f)));

        explosion = new ForceGeneratorExplosion(
            Vector3D(0.0f, -30.0f, -50.0f), // Centro
            200.0f,                      // Radio
            50000.0f,                    // Intensidad k
            1.0f
        );

        fuerzasExplosion.push_back(gravedadNormal);
        fuerzasExplosion.push_back(explosion);
    }

    void update(double dt) override
    {
        if (fuente != nullptr) 
            fuente->update(dt, fuerzasFuente);

        if (torbellinoGen != nullptr)
            torbellinoGen->update(dt, fuerzasTorbellino);

        if (explosionGen != nullptr)
            explosionGen->update(dt, fuerzasExplosion);
    }

    void keyPress(unsigned char key,
        const physx::PxTransform& camera) override
    {
        std::cout << "Key pressed: " << key << std::endl;

        if (key == 'e' || key == 'E')
        {
            if (explosion != nullptr)
                explosion->activar();
        }
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
        if (gravedadNormal != nullptr) {
            delete gravedadNormal;
            gravedadNormal = nullptr;
        }

        if (viento != nullptr) {
            delete viento;
            viento = nullptr;
        }

        if (torbellino != nullptr) {
            delete torbellino;
            torbellino = nullptr;
        }

        if (explosion != nullptr) {
            delete explosion;
            explosion = nullptr;
        }

    }

private:
    std::string display_text;

    Particle* modelo = nullptr;
    GeneradorDeParticulas* fuente = nullptr;
    GeneradorDeParticulas* torbellinoGen = nullptr;
    GeneradorDeParticulas* explosionGen = nullptr;

    ForceGeneratorGravity* gravedadNormal = nullptr;
    ForceGeneratorWind* viento = nullptr; 
    ForceGeneratorVortex* torbellino = nullptr; 
    ForceGeneratorExplosion* explosion = nullptr; 
    std::vector<ForceGenerator*> fuerzasFuente;
    std::vector<ForceGenerator*> fuerzasTorbellino;
    std::vector<ForceGenerator*> fuerzasExplosion;

    
};

