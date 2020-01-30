#ifndef BUBBLEENEMY_HPP
#define BUBBLEENEMY_HPP
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include <string>

class Game;

class BubbleEnemy: public AObject
{
    private:
        int _velocity;  
        static Shape _shape;
        BubbleEnemy(const BubbleEnemy &);
        BubbleEnemy &operator=(const BubbleEnemy &);
        
    public:
        BubbleEnemy(int x, int y, int velocity);
        ~BubbleEnemy();
        const Shape &getShape() const;
       void actionMove(Game *g, const Keyboard &k);
       void actionShoot(Game *g, const Keyboard &k);

};

#endif
