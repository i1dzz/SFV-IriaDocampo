#include "Proyectil.h"

Proyectil::Proyectil(
    const physx::PxTransform& camera,
    float velSim,
    float masaReal,
    float velReal,
    float signo
)
    : Particle(
        Vector3D(
            camera.p.x + camera.q.rotate(
                physx::PxVec3(0.0f, 0.0f, -1.0f)
            ).x * 2.0f,
            camera.p.y + camera.q.rotate(
                physx::PxVec3(0.0f, 0.0f, -1.0f)
            ).y * 2.0f,
            camera.p.z + camera.q.rotate(
                physx::PxVec3(0.0f, 0.0f, -1.0f)
            ).z * 2.0f
        ),

        Vector3D(
            camera.q.rotate( physx::PxVec3(0.0f, 0.0f, -1.0f)
            ).getNormalized()
        )* velSim,

        Vector3D(
            0.0f,   -signo * 9.81f * (velSim / velReal) * (velSim / velReal),
            0.0f
        ),

        1.0f
    )
{
    // Calcular la masa simulada
    float masaSim = masaReal *
        (velReal / velSim) * (velReal / velSim);

    setMass(masaSim);
}