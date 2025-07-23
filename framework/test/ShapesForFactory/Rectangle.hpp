// Rectangle.hpp

#ifndef ILRD_RD1645_RECTANGLE_HPP
#define ILRD_RD1645_RECTANGLE_HPP

#include "Shape.hpp"

using namespace ilrd;

class Rectangle : public Shape
{
public:
    Rectangle(size_t offset = 0);
    ~Rectangle();
    virtual void DrawShape();
}; // class Rectangle

#endif  // ILRD_RD1645_RECTANGLE_HPP