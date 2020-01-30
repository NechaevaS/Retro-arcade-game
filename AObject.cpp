#include "AObject.hpp"
#include <unistd.h>

AObject::AObject(int x, int y, int maxHp, int lives, int damage, int val):
_x(x), _y(y), _hp(maxHp), _maxHp(maxHp), _lives(lives), _damage(damage), _val(val)
{
}

AObject::~AObject()
{
}

bool AObject::outOfGame(WINDOW *w) const
{
    const Shape &shape(this->getShape());
    int wr = getmaxx(w)-2;
    int wl = 2;
    int left = this->_x;
    int right = left + shape.getSizeX();
    if (right < wl || left > wr)
        return (true);
    return (false);
   
}

bool AObject::killed() const
{
     return (this->_lives == 0);
}


void AObject::takeDamage(int)
{
}

int AObject::getValue() const
{
    return (this->_val);
}

int AObject::getLives() const
{
    return this->_lives;
}

int AObject::getHP() const
{
    return this->_hp;
}

static bool intersect(int a0, int a1, int b0, int b1)
{
    if (b0 >= a0 && b0 <= a1)
        return (true);
    if (b1 >= a0 && b1 <= a1)
        return (true);
    if (a0 >= b0 && a0 <= b1)
        return (true);
    if (a1 >= b0 && a1 <= b1)
        return (true);
    return (false);
}

bool AObject::isCollision(AObject *o) const
{
    const Shape &s1 = this->getShape();
    const Shape &s2 = o->getShape();
    int o1xL = this->_x;
    int o1yU = this->_y;
    int o1xR = o1xL + s1.getSizeX() - 1;
    int o1yD = o1yU + s1.getSizeY() - 1;
    int o2xL = o->_x;
    int o2yU = o->_y;
    int o2xR = o2xL + s2.getSizeX() - 1;
    int o2yD = o2yU + s2.getSizeY() - 1;
    if (intersect(o1xL, o1xR, o2xL, o2xR) && intersect(o1yU, o1yD, o2yU, o2yD))
        return (true);
    return (false);

}

void AObject::processCollision(AObject *ob)
{
    if (this == ob || !this->isCollision(ob))
        return;
    this->_hp -= ob->_damage;
    if (this->_hp <= 0)
    {
        this->_lives -= 1;
        this->_hp = this->_maxHp;
    }
}

void AObject::draw(WINDOW *w)
{
    const Shape &shape(this->getShape());

    for (int y = 0; y < shape.getSizeY(); y++)
    {
        for (int x = 0; x < shape.getSizeX(); x++)
        {
            mvwaddch(w, y + this->_y, x + this->_x, shape.getElement(x, y));
        }
    }
    
}

