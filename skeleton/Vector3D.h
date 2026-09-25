#pragma once
#include <cassert>
#include <cmath>
#include <ostream>
#include "PxPhysicsAPI.h"

/*
 * A class implementing a 2-dimensional vector and corresponding
 * operations. All operations generate new Vector2D, they do not
 * modify the vectors on which they operate. The only methods that
 * modify the state are the different setters (and operator=).
 *
 */
class Vector3D
{
public:

    float _x; // first coordinate
    float _y; // second coordinate
    float _z; // third coordinate

    // constructores 
    Vector3D() noexcept;
    Vector3D(const Vector3D& v) noexcept;
    Vector3D(Vector3D&& v) noexcept;
    Vector3D(float x, float y, float z) noexcept;
    Vector3D(const physx::PxVec3& v);

    ~Vector3D();

	// Operaciones
    Vector3D normalize() const;
    float magnitude() const;
    float dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& v) const ;

    // Operadores 
    // copy assignment
    inline Vector3D& operator=(const Vector3D& v) noexcept
    {
        _x = v._x;
        _y = v._y;
        _z = v._z;
        return *this;
    }

    // vector subtraction
    inline Vector3D operator-(const Vector3D& v) const
    {
        return Vector3D(_x - v._x, _y - v._y, _z - v._z);
    }

    // vector addition
    inline Vector3D operator+(const Vector3D& v) const
    {
        return Vector3D(_x + v._x, _y + v._y, _z + v._z);
    }

    // multiplication by constant (scaling)
    inline Vector3D operator*(float d) const
    {
        return Vector3D(_x * d, _y * d, _z * d);
    }

    // division by constant (scaling)
    inline Vector3D operator/(float d) const
    {
        return Vector3D(_x / d, _y / d, _z / d);
    }

    // Operador de igualdad
    inline bool operator==(const Vector3D& v) const
    {
        return _x == v._x && _y == v._y && _z == v._z;
    }

    // Operador de desigualdad
    inline bool operator!=(const Vector3D& v) const
    {
        return !(*this == v);
    }

    // scalar multiplication
    inline float operator*(const Vector3D& d) const
    {
        return d._x * _x + d._y * _y + d._z * _z;
    }

    inline bool operator<(const Vector3D& other) const
    {
        return (_x < other._x) || (_x == other._x && _y < other._y) || (_x == other._x && _y == other._y && _z < other._z);
    }


    // v[0] is the first coordinate and v[1] is the second
    inline float& operator[](int i) noexcept
    {
        assert(i == 0 || i == 1 || i == 2);
        return i == 0 ? _x : i == 1 ? _y : _z;
    }

    // v[0] is the first coordinate and v[1] is the second
    inline const float& operator[](int i) const noexcept
    {
        assert(i == 0 || i == 1 || i == 2);
        return i == 0 ? _x : i == 1 ? _y : _z;
    }

    // counter clockwise rotation in a normal coordinate system, and
    // it is clockwise rotation if we work with a coordinate system
    // in which the vertical axe is flipped (it is like a mirror over
    // the horizontal axe) -- which the case when working with SDL.
    //
    Vector3D rotate(float degrees) const;

    // Computes the angle between 'this' and 'v'. The result is
    // between -180 and 180, and is such that the following holds:
    //
    //   this->rotate(angle).normalize() == v.normalize()
    //
    float angle(const Vector3D& v) const;

    /// <summary>
    /// @brief devuelve el angulo formado por el vector
    /// </summary>
    /// <returns>angulo devuelto en radianes</returns>
    float angle() const;

    Vector3D targetAngle(const Vector3D& target) const;


    // Conversión a PxVec3
    Vector3D::operator physx::PxVec3() const
    {
        return physx::PxVec3(_x, _y, _z);
    }

};

// needed for printing a value of type Vector3D with std::cout.
// The definition is in .cpp
std::ostream& operator<<(std::ostream& os, const Vector3D& v);
