#pragma once

#include <string>
#include "PxPhysicsAPI.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:

	Particle(Vector3D pos, Vector3D vel, Vector3D ac, float dam);
	Particle(Vector3D pos, Vector3D vel, Vector3D ac, float masa, float damping); 

	Particle(Vector3D pos, Vector3D vel, Vector3D ac, float dam, float m, float size);

	~Particle();

	void integrate(double dt);
	void release();
	Particle* clone() const; 

	// Getters
	Vector3D getPosition() const { return Vector3D(pose.p.x, pose.p.y, pose.p.z); }
	const Vector3D& getVelocity() const { return vel; }
	const float& getMass() const{	return masa;}

	// Setters
	void setPosition(const Vector3D& position)
	{
		pose.p = physx::PxVec3(position._x, position._y, position._z);
		if (renderItem) { renderItem->transform = &pose; }
	}	
	void setVelocity(const Vector3D& velocity) { vel = velocity;}
	void setAcceleration(const Vector3D& acceleration) {acel = acceleration;}
	void setDamping(float damping) { this->damping = damping; }
	void setMass(float m) { masa = m; }

	bool isProyectile() {return _proyectile;}
	void addForce(const Vector3D& fuerza);

private:
	Vector3D vel;
	Vector3D acel;
	float _size; 

	RenderItem* renderItem = nullptr;
	physx::PxTransform pose;

	// proyectil
	float masa = 10.0f;
	float damping = 1.0f;
	bool _proyectile = false;

	Vector3D fuerzaAcumulada = Vector3D(0.0f, 0.0f, 0.0f);


};

