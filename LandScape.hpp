#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include <string>

class Game;

class LandScape: public AObject
{
    private:
        int _velocity;  
        Shape _shape;
        LandScape(const LandScape &);
        LandScape &operator=(const LandScape &);
    public:
        LandScape(int x, int bottom, int height, int velocity);
        ~LandScape();
        const Shape &getShape() const;
        void actionMove(Game *, const Keyboard &);
        void actionShoot(Game *, const Keyboard &);
};

#endif
