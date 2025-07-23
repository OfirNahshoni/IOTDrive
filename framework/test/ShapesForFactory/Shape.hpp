// Shape.hpp

#ifndef ILRD_RD1645_SHAPES_HPP
#define ILRD_RD1645_SHAPES_HPP

#include <cstddef> //size_t

namespace ilrd
{

    class Shape
    {
    public:
        explicit Shape(size_t offset = 0);
        virtual ~Shape() = 0;
        void Draw();
        void Move(size_t offset);

    protected:
        virtual void DrawShape() = 0;

    private:
        size_t m_offset;
    }; //class Shape
} //namespace ilrd
#endif //ILRD_RD1645_SHAPES_HPP