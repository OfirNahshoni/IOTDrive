/******************************************************************************
* File name: Rectangle.cpp
 * Owner: Ofir Nahshoni
 * Review:
 * Review status: NOT Ready
 ******************************************************************************/

#include <iostream>

#include "Rectangle.hpp"

using namespace ilrd;

Rectangle::Rectangle(size_t offset): Shape(offset) {}

Rectangle::~Rectangle() {}

void Rectangle::DrawShape()
{
    std::cout << "Rectangle";
}