// Circle.hpp

#ifndef ILRD_RD1645_CIRCLE_HPP
#define ILRD_RD1645_CIRCLE_HPP

#include "Shape.hpp"

using namespace ilrd;

class Circle : public Shape
{
public:
    Circle(size_t offset = 0);
    ~Circle();
    virtual void DrawShape();
}; // class Circle

#endif  // ILRD_RD1645_CIRCLE_HPP