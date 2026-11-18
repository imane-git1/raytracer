#include "geometry/sphere.h"
#include <cmath>

Sphere::Sphere(const Vector &centre, double radius, const Colour &colour)
    : _centre(centre), _radius(radius), _colour(colour)
{
}

const Vector &Sphere::centre() const
{
    return _centre;
}

double Sphere::radius() const
{
    return _radius;
}

const Colour &Sphere::colour() const
{
    return _colour;
}

bool Sphere::isHitBy(const Ray &ray) const
{
    // Solve a*t^2 + b*t + c = 0 for the point O + t*D on the sphere.
    Vector l = ray.origin() - _centre;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * ray.direction().dot(l);
    double c = l.dot(l) - _radius * _radius;

    double delta = b * b - 4.0 * a * c;
    if (delta < 0.0)
    {
        return false;
    }

    double t1 = (-b - sqrt(delta)) / (2.0 * a);
    double t2 = (-b + sqrt(delta)) / (2.0 * a);

    if (t1 >= 0.0 || t2 >= 0.0)
    {
        return true;
    }

    return false;
}