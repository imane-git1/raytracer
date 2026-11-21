#pragma once

class Colour
{
public:
    Colour(double r, double g, double b);

    [[nodiscard]] double r() const;
    [[nodiscard]] double g() const;
    [[nodiscard]] double b() const;

private:
    double _r;
    double _g;
    double _b;
};

[[nodiscard]] Colour operator*(double factor, const Colour &colour);
