#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>

class Shape
{
    private:
        int _sizeX;
        int _sizeY;
        std::string _shape;
        Shape(const Shape&);
        Shape &operator=(const Shape&);
    public:
        Shape(int sizeX, int sizeY, const std::string &shape);
        ~Shape();
        int getSizeX() const;
        int getSizeY() const;
        char getElement(int x, int y) const;
};

#endif