#include "Vector3D.h"

//CONSTRTUCTORES
Vector3D::Vector3D() noexcept : _x(0.0f), _y(0.0f), _z(0.0f)
{}

Vector3D::Vector3D(const Vector3D& v) noexcept : _x(v._x), _y(v._y), _z(v._z)
{}

Vector3D::Vector3D(Vector3D&& v) noexcept : _x(v._x), _y(v._y), _z(v._z)
{}

Vector3D::Vector3D(float x, float y, float z) noexcept : _x(x), _y(y), _z(z)
{}

Vector3D::~Vector3D()
{}

// Constructor de conversión desde PxVec3
Vector3D::Vector3D(const physx::PxVec3& v)
    : _x(v.x), _y(v.y), _z(v.z)
{}

// Operaciones
Vector3D Vector3D::normalize() const
{
    float mag = magnitude();

    if (mag == 0.0f)
        return Vector3D(0.0f, 0.0f, 0.0f);

    return Vector3D(_x / mag, _y / mag, _z / mag);
}

float Vector3D::magnitude() const
{
    return sqrtf(powf(_x, 2) + powf(_y, 2) + powf(_z, 2));
}

float Vector3D::dot(const Vector3D& other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}
Vector3D Vector3D::cross(const Vector3D& v) const
{
    return Vector3D(
        _y * v._z - _z * v._y,
        _z * v._x - _x * v._z,
        _x * v._y - _y * v._x
    );
}
