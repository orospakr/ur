//
// Created by Andrew Clunis on 2023-11-24.
//

#ifndef UR_VECTOR2D_H
#define UR_VECTOR2D_H

#include <iostream>

namespace ur {
    class Vector2D {
    public:
        double x, y;

        explicit Vector2D(double x = 0.0f, double y = 0.0f);

        Vector2D operator+(const Vector2D &other) const;

        Vector2D operator-(const Vector2D &other) const;

        Vector2D operator*(double scalar) const;

        Vector2D operator/(double scalar) const;

        [[nodiscard]] double length() const;

        [[nodiscard]] Vector2D normalize() const;

        friend std::ostream &operator<<(std::ostream &os, const Vector2D &v);

        double slope() const;
    };
}

#endif //UR_VECTOR2D_H
