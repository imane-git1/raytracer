#pragma once

class Vector {
public:
    Vector() = default;
    Vector(float x, float y, float z);

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;

    float x() const;
    float y() const;
    float z() const;

private:
    float _x = 0.0f;
    float _y = 0.0f;
    float _z = 0.0f;
};
