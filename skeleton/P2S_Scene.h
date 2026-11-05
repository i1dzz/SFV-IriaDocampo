#pragma once

#include<vector>
#include "Scene.h"
#include "Particle.h"
#include "GeneradorDeParticulas.h"
#include "ForceGeneratorGravity.h"
#include "ForceGeneratorWind.h"
#include "ForceGeneratorVortex.h"
#include "ForceGeneratorExplosion.h"
#include "SistemaDeParticulas.h"
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
        // Crear sistema de particulas
        sistema = new SistemaDeParticulas();

        // Modelo de particula para el primer generador
        modelo = new Particle(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            1.0f, 1.0f, 0.5f,
            Vector4(0.0f, 0.0f, 0.7f, 0.5f));

        // Gen1
        fuente = new GeneradorDeParticulas(
            Vector3D(0.0f, 80.0f, 0.0f),
            Vector3D(0.0f, 1.0f, 0.0f),
            Vector3D(-50.0f, -30.0f, 0.0f),
            5.0f, 1.0f, modelo  );

        gravedadNormal = new ForceGeneratorGravity( Vector3D(0.0f, -10.0f, 0.0f) );

        viento = new ForceGeneratorWind(Vector3D(5.0f, 0.0f, 0.0f), 2.0f);

        fuerzasFuente.push_back(viento);
        fuerzasFuente.push_back(gravedadNormal);

        //Gen2
        modeloTorbellino = new Particle(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            1.0f, 1.0f, 0.5f,
            Vector4(0.7f, 0.7f, 0.7f, 0.5f));

        torbellinoGen = new GeneradorDeParticulas(
            Vector3D(0.0f, 80.0f, 0.0f),
            Vector3D(0.0f, 1.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            5.0f, 2.0f,
            modeloTorbellino);

        torbellino = new ForceGeneratorVortex(
            Vector3D(0, 0, 0), 100.0f, 5.0f, 2.0f );

        fuerzasTorbellino.push_back(torbellino);

        //Gen3
        modeloExplosion = new Particle(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            1.0f, 1.0f, 0.5f,
            Vector4(1.0f, 0.7f, 0.0f, 0.5f));

        explosionGen = new GeneradorDeParticulas(
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, 0.0f, 0.0f),
            Vector3D(0.0f, -30.0f, -50.0f),
            1.0f, 2.0f,
            modeloExplosion
        );

        explosion = new ForceGeneratorExplosion(Vector3D(0.0f, -30.0f, -50.0f), 200.0f, 50000.0f, 1.0f );

        fuerzasExplosion.push_back(gravedadNormal);
        fuerzasExplosion.push_back(explosion);


        //Registrar en el sistema : fuerzas y generadores
        sistema->addForceGenerator(viento);
        sistema->addForceGenerator(gravedadNormal);
        sistema->addForceGenerator(torbellino);
        sistema->addForceGenerator(explosion);

        sistema->addParticleGenerator(fuente, fuerzasFuente);
        sistema->addParticleGenerator(torbellinoGen, fuerzasTorbellino);
        sistema->addParticleGenerator(explosionGen, fuerzasExplosion);
    }

    void update(double dt) override
    {
        if (sistema != nullptr)
            sistema->update(dt);
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
        // Destruir sistema
        delete sistema;
        sistema = nullptr;

        delete modelo;
        modelo = nullptr;

        delete modeloTorbellino;
        modeloTorbellino = nullptr;

        delete modeloExplosion;
        modeloExplosion = nullptr;

        // Estos ya han sido liberados por el sistema
        fuente = nullptr;
        torbellinoGen = nullptr;
        explosionGen = nullptr;

        gravedadNormal = nullptr;
        viento = nullptr;
        torbellino = nullptr;
        explosion = nullptr;

        fuerzasFuente.clear();
        fuerzasTorbellino.clear();
        fuerzasExplosion.clear();
    }

private:
    std::string display_text;

    Particle* modelo = nullptr;
    Particle* modeloTorbellino = nullptr;
    Particle* modeloExplosion = nullptr;
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

    SistemaDeParticulas* sistema = nullptr;
    
};

