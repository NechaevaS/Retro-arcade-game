#include "Shape.hpp"
#include <fstream>
#include <cstdlib>

Shape::Shape(int sizeX, int sizeY, const std::string &shape):
_sizeX(sizeX), _sizeY(sizeY), _shape(shape)
{
    if (sizeX * sizeY != (int)shape.size())
    {
        std::ofstream err("errors", std::ofstream::app);
        err << "shape does not conform x and y\n";
        exit(1);
    }
}

Shape::~Shape()
{
}

int Shape::getSizeX() const
{
    return (this->_sizeX);
}

int Shape::getSizeY() const
{
    return (this->_sizeY);
}

char Shape::getElement(int x, int y) const
{
    if (x < 0 || x >= this->_sizeX)
    {
        std::ofstream err("errors", std::ofstream::app);
        err << "x is out of size\n";
        exit(1);
    }
    if(y < 0 || y >= this->_sizeY)
    {
        std::ofstream err("errors", std::ofstream::app);
        err << "y is out of size\n";
        exit(1);
    }
    return (this->_shape[y * this->_sizeX + x]);
}