#include "Hero.hpp"
#include "Game.hpp"
#include "Bubble.hpp"
#include <unistd.h>

Shape Hero::_shape(9, 3,
                std::string("\\  @@@>  ") +
                std::string(">>@@@@@>>") +
                std::string("/  @@@>  "));

Hero::Hero(int x, int y, int nlives) : AObject(x, y, 100, nlives, 100, 0)
{
    this->_hp = _maxHp;
}

Hero::~Hero()
{
}

const Shape &Hero::getShape() const
{
    return (_shape);
}

void Hero::actionShoot(Game *g, const Keyboard &k)
{
    if (k.isKeyPresed(' '))
    {
        int x = this->_x + _shape.getSizeX() - 1;
        int y = this->_y +_shape.getSizeY()/2;
        Bubble *b = new Bubble(x, y, 1);
        g->addObject(b);
    }

}
void Hero::actionMove(Game *g, const Keyboard &k)
{
    WINDOW *w = g->getGameWindow();
    int right = getmaxx(w) - 1 - _shape.getSizeX();
    int bottom = getmaxy(w) - 1 - _shape.getSizeY();
    if ((k.isKeyPresed('w') || k.isKeyPresed(KEY_UP)) && this->_y > 1)
        this->_y -= 1;
    if ((k.isKeyPresed('s') || k.isKeyPresed(KEY_DOWN)) && this->_y < bottom)
        this->_y += 1;
    if ((k.isKeyPresed('a') || k.isKeyPresed(KEY_LEFT)) && this->_x > 1)
        this->_x -= 1;
    if ((k.isKeyPresed('d') || k.isKeyPresed(KEY_RIGHT)) && this->_x < right)
        this->_x += 1;

    
}


