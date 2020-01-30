#ifndef AOBJECT_HPP
#define AOBJECT_HPP
#include <ncurses.h>
#include "AObject.hpp"
#include "Shape.hpp"
#include "Keyboard.hpp"
#include <string>

class Game;

class AObject
{
    protected:
        int _x;
        int _y;
        int _hp;
        int _maxHp;
        int _lives;
        int _damage;
        int _val;
        char _colour;
        AObject(const AObject &);
        AObject &operator=(const AObject &);
    public:
        AObject(int x, int y, int maxhp, int lives, int damage, int val, char colour);
        virtual ~AObject();
        virtual bool outOfGame(WINDOW *) const;
        virtual bool killed() const;
        virtual void draw(WINDOW *);
        virtual void actionMove(Game *, const Keyboard &) = 0;
        virtual void actionShoot(Game *, const Keyboard &) = 0;
        virtual bool isCollision(AObject *) const;
        virtual const Shape &getShape() const = 0;
        void processCollision(AObject *);
        void takeDamage(int dam);
        int getValue() const;
        int getLives() const;
        int getHP() const;
};

#endif
