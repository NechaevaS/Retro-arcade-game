#ifndef HERO_HPP
#define HERO_HPP
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include <string>

class Game;

class Hero: public AObject
{
    private:
        
        static Shape _shape;
        Hero(const Hero &);
        Hero &operator=(const Hero &);
    public:
        Hero(int x, int y, int nLives = 3);
        ~Hero();
        const Shape &getShape() const;
       void actionMove(Game *g, const Keyboard &k);
       void actionShoot(Game *g, const Keyboard &k);      
};

#endif
