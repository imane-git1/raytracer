#include "vector.h"

Vector::Vector(float x, float y, float z) : _x(x), _y(y), _z(z) {}

Vector Vector::operator+(const Vector& other) const {
    return Vector{_x + other._x, _y + other._y, _z + other._z};
}

Vector Vector::operator-(const Vector& other) const {
    return Vector{_x - other._x, _y - other._y, _z - other._z};
}

float Vector::x() const {
    return _x;
}

float Vector::y() const {
    return _y;
}

float Vector::z() const {
    return _z;
}
