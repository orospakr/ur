//
// Created by Andrew Clunis on 2023-11-24.
//

#include "Vector2D.h"

#include <iostream>
#include <cmath>

namespace ur {
    Vector2D::Vector2D(double x, double y) : x(x), y(y) {}

    Vector2D Vector2D::operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }

    Vector2D Vector2D::operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }

    Vector2D Vector2D::operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }

    Vector2D Vector2D::operator/(double scalar) const {
        return Vector2D(x / scalar, y / scalar);
    }

    double Vector2D::length() const {
        return std::sqrt(x * x + y * y);
    }

    Vector2D Vector2D::normalize() const {
        double len = length();
        if (len != 0) {
            return *this / len;
        }
        return *this;
    }

    std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
        os << "Vector2D(" << v.x << ", " << v.y << ")";
        return os;
    }

    /**
     * @brief Returns the slope of the vector.
     */
    double Vector2D::slope() const {
        return y / x;
    }
}