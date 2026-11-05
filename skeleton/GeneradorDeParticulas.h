#pragma once
#include "Particle.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>
#include <iostream>
#include "ForceGenerator.h"

#include <random>
class GeneradorDeParticulas{
public: 

	// el generador dispara particulas a una velocidad constante en una misma direccion y su direcion apenas varia
	GeneradorDeParticulas(Vector3 vel, Vector3 dir, Vector3 pos);
	GeneradorDeParticulas(Vector3D vel, Vector3D dir, Vector3D pos,	float vida,	float dispersion, Particle* pM);
	~GeneradorDeParticulas();
	void cleanup();
	void update(double dt, const std::vector<ForceGenerator*>& fuerzas);



private:
	std::random_device rd;
	std::mt19937 gen{ rd() };

	std::normal_distribution<float> distX{ 0.0f, 5.0f };
	std::normal_distribution<float> distY{ 0.0f, 5.0f };
	std::normal_distribution<float> distZ{ 0.0f, 5.0f };
	Vector3D _minBounds;
	Vector3D _maxBounds;

	Vector3 _vel; // valocidad media
	Vector3 _dir; // direccion principal
	Vector3 _pos; // posicion del emisor

	// vector de particulas con sus tiempos de vida 
	std::vector<std::pair<Particle*, float>> particulas; 
	float _vida; // tiempo de vida de las particulas; 
	float _dispersion = 0.5f;

	Particle* pModel = nullptr; 

};

