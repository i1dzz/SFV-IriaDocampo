#include "Particle.h"


Particle::Particle(Vector3D pos, Vector3D vel, Vector3D ac, float dam = 1.0f)
{
	this->vel = vel;
	this->acel = ac;
	this->damping = dam;

	this->pose = physx::PxTransform(pos._x, pos._y, pos._z);
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.5f));
	this->renderItem = new RenderItem(shape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	shape->release();

	_proyectile = true;
}


Particle::Particle(Vector3D pos, Vector3D vel, Vector3D ac,float masa, float damping): 
	vel(vel),acel(ac), damping(damping), masa(masa), _proyectile(true), renderItem(nullptr), pose(physx::PxTransform(physx::PxVec3(pos._x, pos._y, pos._z)))
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.5f));

	renderItem = new RenderItem(shape, &pose,Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	shape->release();

	if (_proyectile) acel = Vector3D(0.0f, 0.81f, 0.0f);
}


Particle::Particle(Vector3D pos, Vector3D vel, Vector3D ac, float dam, float m, float size) : masa(m), _size(size)
{
	this->vel = vel;
	this->acel = ac;
	this->damping = dam;
	this->pose = physx::PxTransform(pos._x, pos._y, pos._z);
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(_size));
	this->renderItem = new RenderItem(shape, &pose, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	shape->release();

	_proyectile = true;

	masa = m; 

}

Particle::~Particle()
{
	release();
}
void 
Particle::integrate(double dt)
{
	// 2da ley de Newton
	Vector3D aceleracion = fuerzaAcumulada * masa;

	// Actualizar velocidad
	vel = vel + aceleracion * static_cast<float>(dt);

	// Actualizar posicion
	Vector3D pos(pose.p.x, pose.p.y, pose.p.z);

	pos = pos + vel * static_cast<float>(dt);

	pose.p = physx::PxVec3(pos._x, pos._y, pos._z);

	// Reiniciar el acumulador
	fuerzaAcumulada = Vector3D(0.0f, 0.0f, 0.0f);

	if (renderItem!= nullptr)
		renderItem->transform = &pose;
}


void Particle::release()
{
	if (renderItem != nullptr)
	{
		renderItem->release();
		renderItem = nullptr;
	}
}


void 
Particle::addForce(const Vector3D& fuerza)
{
	fuerzaAcumulada = fuerzaAcumulada + fuerza;
}


Particle* 
Particle::clone() const
{
	return new Particle(getPosition(),vel,acel, damping,masa,_size);
}