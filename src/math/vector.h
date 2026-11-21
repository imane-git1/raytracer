#pragma once

class Vector
{
public:
    Vector(double x, double y, double z);

    [[nodiscard]] double x() const;
    [[nodiscard]] double y() const;
    [[nodiscard]] double z() const;

    [[nodiscard]] Vector operator+(const Vector &other) const;
    [[nodiscard]] Vector operator-(const Vector &other) const;

    [[nodiscard]] double dot(const Vector &other) const;
    [[nodiscard]] double length() const;
    [[nodiscard]] Vector normalised() const;

private:
    double _x;
    double _y;
    double _z;
};

[[nodiscard]] Vector operator*(double t, const Vector &v);