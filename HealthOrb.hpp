#ifndef HEALTHORB_HPP
#define HEALTHORB_HPP
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include <string>

class Game;

class HealthOrb: public AObject
{
    private:
        
        static Shape _shape;
        HealthOrb(const HealthOrb &);
        HealthOrb &operator=(const HealthOrb &);
    public:
        HealthOrb(int x, int y);
        ~HealthOrb();
        const Shape &getShape() const;
        void action(Game *, const Keyboard &);
        void processCollision(AObject *ob);
};

#endif
