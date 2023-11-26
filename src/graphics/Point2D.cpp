//
// Created by Andrew Clunis on 2023-11-24.
//

#include "Point2D.h"
#include <iostream>

namespace ur {
Point2D::Point2D(double x, double y) : x(x), y(y) {}

Point2D Point2D::operator+(const Point2D &other) const {
    return {x + other.x, y + other.y};
}

Point2D Point2D::operator-(const Point2D &other) const {
    return {x - other.x, y - other.y};
}

std::ostream &operator<<(std::ostream &os, const Point2D &p) {
    os << "Point2D(" << p.x << ", " << p.y << ")";
    return os;
}

Point2D Point2D::operator+(const Vector2D &other) const {
    return {x + other.x, y + other.y};
}
} // namespace ur
