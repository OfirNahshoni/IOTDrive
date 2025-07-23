// Line.hpp

#ifndef ILRD_RD1645_LINE_HPP
#define ILRD_RD1645_LINE_HPP

#include "Shape.hpp"

using namespace ilrd;

class Line : public Shape
{
public:
    Line(size_t offset = 0);
    ~Line();
    virtual void DrawShape();
}; // class Line

#endif  // ILRD_RD1645_LINE_HPP