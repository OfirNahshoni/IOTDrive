/**
* @file: TestFactory.cpp
* @author: Ofir Nahshoni
* @brief: This is a test file for Factory Design Pattern.
*/

#include "Line.hpp"
#include "Square.hpp"
#include "Circle.hpp"
#include "Factory.hpp"
#include "Rectangle.hpp"
#include "Handleton.hpp"

using namespace ilrd;

enum ShapesEnum
{
    LINE = 0,
    SQUARE = 1,
    CIRCLE = 2,
    RECTANGLE = 3,
    NUM_OF_SHAPES
};

std::shared_ptr<Shape> CreateLine(size_t offset)
{
    return std::make_unique<Line>(offset);
}

std::shared_ptr<Square> CreateSquare(size_t offset)
{
    return std::make_unique<Square>(offset);
}

std::shared_ptr<Circle> CreateCircle(size_t offset)
{
    return std::make_unique<Circle>(offset);
}

std::shared_ptr<Rectangle> CreateRectangle(size_t offset)
{
    return std::make_unique<Rectangle>(offset);
}

void TestsForShapesFactory();

int main()
{
    TestsForShapesFactory();

    return 0;
}

void TestsForShapesFactory()
{
    Factory<ShapesEnum, Shape, size_t>* factory = 
                    Handleton::GetInstance<Factory<ShapesEnum, Shape, size_t>>();

    factory->Register(LINE, CreateLine);
    factory->Register(SQUARE, CreateSquare);
    factory->Register(CIRCLE, CreateCircle);
    factory->Register(RECTANGLE, CreateRectangle);

    std::shared_ptr<Shape> shape = factory->Create(LINE, 0);
    shape->Draw();
    shape = factory->Create(SQUARE, 1);
    shape->Draw();
    shape = factory->Create(CIRCLE, 2);
    shape->Draw();
    shape = factory->Create(RECTANGLE, 3);
    shape->Draw();
}