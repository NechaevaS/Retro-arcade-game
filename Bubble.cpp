#include "Bubble.hpp"
#include <unistd.h>

Shape Bubble::_shape(1, 1, "o");

Bubble::Bubble(int x, int y, int velocity):
AObject(x, y, 1, 1, 10, 0), _velocity(velocity)
{
}

Bubble::~Bubble()
{
}

const Shape &Bubble::getShape() const
{
    return (_shape);
}

void Bubble::actionMove(Game *, const Keyboard &)
{
    this->_x += this->_velocity;
}

void Bubble::actionShoot(Game *, const Keyboard &)
{
}
