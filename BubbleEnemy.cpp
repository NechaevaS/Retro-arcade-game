#include "BubbleEnemy.hpp"
#include <unistd.h>

Shape BubbleEnemy::_shape(1, 1, "o");

BubbleEnemy::BubbleEnemy(int x, int y, int velocity):
AObject(x, y, 1, 1, 10, 0), _velocity(-velocity)
{
}

BubbleEnemy::~BubbleEnemy()
{
}

const Shape &BubbleEnemy::getShape() const
{
    return (_shape);
}

void BubbleEnemy::actionMove(Game *, const Keyboard &)
{
    this->_x += this->_velocity;
}

void BubbleEnemy::actionShoot(Game *, const Keyboard &)
{
}
