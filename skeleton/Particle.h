#pragma once

#include <string>
#include "PxPhysicsAPI.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
class Particle
{
public:

	Particle(Vector3D pos, Vector3D vel)
	{
		this->vel = vel;
		this->pose = physx::PxTransform(pos._x, pos._y, pos._z);
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.5f));
		this->renderItem = new RenderItem(shape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	Particle(Vector3D pos, Vector3D vel, Vector3D ac)
	{
		this->vel = vel;
		this->acel = ac;
		this->pose = physx::PxTransform(pos._x, pos._y, pos._z);
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.5f));
		this->renderItem = new RenderItem(shape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}


	Particle(Vector3D pos, Vector3D vel, Vector3D ac, float dam)
	{
		this->vel = vel;
		this->acel = ac;
		this->damping = dam; 
		this->pose = physx::PxTransform(pos._x, pos._y, pos._z);
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.5f));
		this->renderItem = new RenderItem(shape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		_proyectile = true; 
		
	}

	Particle(Vector3D pos, Vector3D vel, Vector3D ac,
		float masa, float damping)
		: vel(vel),
		acel(ac),
		damping(damping),
		masa(masa),
		_proyectile(true),
		renderItem(nullptr),
		pose(physx::PxTransform(
			physx::PxVec3(pos._x, pos._y, pos._z)))
	{
		physx::PxShape* shape =
			CreateShape(physx::PxSphereGeometry(1.5f));

		renderItem = new RenderItem(
			shape, &pose,
			Vector4(1.0f, 0.0f, 0.0f, 1.0f));

		if (_proyectile) acel = Vector3D(0.0f, 0.81f, 0.0f);
	}

	~Particle();

	void integrate(double dt)
			{
		// Actualiza la posición
		// Euler: posicion = posicion + velocidad * dt
		Vector3D pos(pose.p.x, pose.p.y, pose.p.z);
		pos = pos + vel * static_cast<float>(dt);
		pose.p = physx::PxVec3(pos._x, pos._y, pos._z);

		// Actualiza la velocidad 
		vel = vel + acel * static_cast<float>(dt);

		//Damping
		vel = vel * static_cast<float>(damping);
	
		// Actualiza la posición del renderItem si existe
		if (renderItem) {
			renderItem->transform = &pose;
		}

	}

	void release()
	{
		if (renderItem) {
			renderItem->release(); // Deregistra y destruye el item
			renderItem = nullptr;
		}
	}


	// Getters
	Vector3D getPosition() const
	{
		return Vector3D(pose.p.x, pose.p.y, pose.p.z);
	}
	const Vector3D& getVelocity() const
	{
		return vel;
	}
	const float& getMass() const
	{
		return masa;
	}
	// Setters
	void setPosition(const Vector3D& position)
		{
		pose.p = physx::PxVec3(position._x, position._y, position._z);
		if (renderItem) {
			renderItem->transform = &pose;
		}
	}	
	void setVelocity(const Vector3D& velocity) { vel = velocity;}
	void setAcceleration(const Vector3D& acceleration) {acel = acceleration;}
	void setDamping(float damping) { this->damping = damping; }
	void setMass(float m) { masa = m; }

	bool isProyectile()
	{
		return _proyectile;
	}

private:
	Vector3D vel;
	Vector3D acel;


	RenderItem* renderItem;
	physx::PxTransform pose;

	// proyectil
	float masa = 10.0f;
	float damping = 1.0f;
	bool _proyectile = false;


};

