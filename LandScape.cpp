#include "LandScape.hpp"
#include <unistd.h>
static std::string generateShape(int height)
{
    std::string res;
    res.push_back('W');
    for (int i = 1; i < height; i++)
        res.push_back('+');
    return (res);
}

LandScape::LandScape(int x, int bottom, int height, int velocity):
AObject(x, bottom - height + 1, 1000, 100, 100, 0), _velocity(-velocity),
_shape(1, height, generateShape(height))
{
}

LandScape::~LandScape()
{
}


const Shape &LandScape::getShape() const
{
    return (_shape);
}

void LandScape::actionMove(Game *, const Keyboard &)
{
    this->_x += this->_velocity;
}

void LandScape::actionShoot(Game *, const Keyboard &)
{
}

