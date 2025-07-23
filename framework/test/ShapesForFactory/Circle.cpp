/******************************************************************************
* File name: Circle.cpp
 * Owner: Ofir Nahshoni
 * Review:
 * Review status: NOT Ready
 ******************************************************************************/

#include <iostream>

#include "Circle.hpp"

using namespace ilrd;

Circle::Circle(size_t offset): Shape(offset) {}

Circle::~Circle() {}

void Circle::DrawShape()
{
    std::cout << "Circle";
}