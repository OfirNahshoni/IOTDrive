/******************************************************************************
* File name: Line.cpp
 * Owner: Ofir Nahshoni
 * Review:
 * Review status: NOT Ready
 ******************************************************************************/

#include <iostream>

#include "Line.hpp"

using namespace ilrd;

Line::Line(size_t offset): Shape(offset) {}

Line::~Line() {}

void Line::DrawShape()
{
    std::cout << "Line";
}