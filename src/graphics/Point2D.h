//
// Created by Andrew Clunis on 2023-11-24.
//

#ifndef UR_POINT2D_H
#define UR_POINT2D_H

#include <iostream>

#include "Vector2D.h"

namespace ur {
    class Point2D {
    public:
        double x, y;

        Point2D(double x = 0.0f, double y = 0.0f);

        // Overloading operators to support point arithmetic
        Point2D operator+(const Point2D& other) const;
        Point2D operator-(const Point2D& other) const;

        // Adding a vector to a point
        [[nodiscard]] Point2D operator+(const Vector2D& other) const;

        // Utility function for printing the point
        friend std::ostream& operator<<(std::ostream& os, const Point2D& p);
    };
}


#endif //UR_POINT2D_H
