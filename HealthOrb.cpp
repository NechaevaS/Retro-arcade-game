#include "HealthOrb.hpp"
#include "Game.hpp"
#include "Bubble.hpp"
#include <unistd.h>

Shape HealthOrb::_shape(12, 5,
                std::string("    ....    ") +
                std::string(" ::  ||  :: ") +
                std::string(":: ==  == ::") +
                std::string(" ::  ||  ::" ) +
                std::string("    ....    "));

HealthOrb::HealthOrb(int x, int y) : AObject(x, y, 30, 3, -30, 0)
{
}

HealthOrb::~HealthOrb()
{
}

const Shape &HealthOrb::getShape() const
{
    return (_shape);
}

void HealthOrb::action(Game *g, const Keyboard &k)
{
    // WINDOW *w = g->getGameWindow();
    // int right = getmaxx(w) - 1 - _shape.getSizeX();
    // int bottom = getmaxy(w) - 1 - _shape.getSizeY();
    // if (k.isKeyPresed('w') && this->_y > 1)
    //     this->_y -= 1;
    // if (k.isKeyPresed('s')&& this->_y < bottom)
    //     this->_y += 1;
    // if (k.isKeyPresed('a')&& this->_x > 1)
    //     this->_x -= 1;
    // if (k.isKeyPresed('d')&& this->_x < right)
    //     this->_x += 1;

    // if (k.isKeyPresed(' '))
    // {
    //     int x = this->_x + _shape.getSizeX();
    //     int y = this->_y +_shape.getSizeY()/2;
    //     Bubble *b = new Bubble(x, y, 1);
    //     g->addObject(b);
    // }
}

void HealthOrb::processCollision(AObject *ob)
{
    if (this == ob || !this->isCollision(ob))
        return;
    this->_hp -= ob->_damage;
    if (this->_hp <= ob->_maxHp)
    {
        this->_hp = this->_maxHp;
    }
}
