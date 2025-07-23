// Square.hpp

#ifndef ILRD_RD1645_SQUARE_HPP
#define ILRD_RD1645_SQUARE_HPP

#include "Shape.hpp"

using namespace ilrd;

class Square : public Shape
{
public:
    Square(size_t offset = 0);
    ~Square();
    virtual void DrawShape();
}; // class Square

#endif  // ILRD_RD1645_SQUARE_HPP