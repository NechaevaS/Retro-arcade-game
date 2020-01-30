#ifndef BUBBLE_HPP
#define BUBBLE_HPP
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include <string>

class Game;

class Bubble: public AObject
{
    private:
        int _velocity;  
        static Shape _shape;
        Bubble(const Bubble &);
        Bubble &operator=(const Bubble &);
        
    public:
        Bubble(int x, int y, int velocity);
        ~Bubble();
        const Shape &getShape() const;
       void actionMove(Game *g, const Keyboard &k);
       void actionShoot(Game *g, const Keyboard &k);

};

#endif
