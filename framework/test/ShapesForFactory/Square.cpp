/******************************************************************************
* File name: Square.cpp
 * Owner: Ofir Nahshoni
 * Review:
 * Review status: NOT Ready
 ******************************************************************************/

#include <iostream>

#include "Square.hpp"

using namespace ilrd;

Square::Square(size_t offset): Shape(offset) {}

Square::~Square() {}

void Square::DrawShape()
{
    std::cout << "Square";
}