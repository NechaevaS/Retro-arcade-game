#ifndef GAME_HPP
#define GAME_HPP

#include "ObjectVector.hpp"
#include "LandScape.hpp"
#include "Keyboard.hpp"
#include "Enemy.hpp"
#include "Hero.hpp"
#include <curses.h>
#include <stdlib.h>
#include <string>

class Game
{
    private:
        Keyboard _keyboard;
        WINDOW *_gameWin;
        WINDOW *_scoreWin;
        ObjectVector *_objects;
        int _score;
        int _level;
        Hero *_hero;
        const static int _landH = 10;
        Game(const Game &);
        Game &operator=(const Game &);

    public:
        Game();
        ~Game();
        void addObject(AObject *);
        void doObjectsAction(int round);
        void processObjectsCollision();
        void drawAllObjects();
        void removeOutOfGameObjects();
        void run();
        void gameOver();
        WINDOW *getGameWindow();

        static LandScape *landGenerator(WINDOW *w);
        static Hero *heroGenerator(WINDOW *w, int nLives = 3);
        Enemy *enemyGenerator(WINDOW *w);
        void    displayScore(WINDOW *w, Hero *hero);
        void restart();
        int     getLevel();
        int     getScore();
};

#endif