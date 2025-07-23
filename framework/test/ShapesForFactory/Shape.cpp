/******************************************************************************
* File name: Shape.cpp
 * Owner: Ofir Nahshoni
 * Review:
 * Review status: APPROVED
 ******************************************************************************/

#include <iostream>

#include "Shape.hpp"

using namespace ilrd;

Shape::Shape(size_t offset): m_offset(offset) {}

Shape::~Shape() {}

void Shape::Draw()
{
    for (size_t i = 0; i < m_offset; ++i)
    {
        std::cout << " ";
    }

    DrawShape();
    std::cout << std::endl;
}

void Shape::Move(size_t offset)
{
    m_offset = offset;
}