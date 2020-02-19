#include "Game.hpp"
#include "Hero.hpp"
#include "Bubble.hpp"
#include "BubbleEnemy.hpp"
#include "Enemy.hpp"
#include <unistd.h>
#include <cstdlib>
#include <unistd.h>

Game::Game() : _score(0), _level(1)
{
    std::srand(time(NULL));
    /* determine the terminal type, including its size and 
    features, and sets up the curses environment 
    based on what the terminal can support*/
    initscr();

    /* disable line buffering and sets curses
     to take one character at a time*/
    cbreak();

    /* tell curses not to echo the input back to the screen*/
    noecho();
    clear();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    this->_gameWin = newwin(LINES - 10, COLS, 0, 0);
    this->_scoreWin = newwin(10, COLS, LINES - 10, 0);
    refresh();
    wborder(this->_scoreWin, 0, 0, 0, 0, 0, 0, 0, 0);
    wrefresh(this->_scoreWin);
    this->_objects = new ObjectVector;
    this->_hero = heroGenerator(this->_gameWin);
    this->_objects->push_back(this->_hero);
}

Game::~Game()
{
    for (unsigned int i = 0; i < this->_objects->getSize(); i++)
        delete (*this->_objects)[i];
    delete this->_objects;
    delwin(this->_gameWin);
    delwin(this->_scoreWin);
    endwin();
}

void Game::addObject(AObject *o)
{
    this->_objects->push_back(o);
}

void Game::doObjectsAction(int round)
{
    ObjectVector *objs = this->_objects;
    for (unsigned i = 0; i < objs->getSize(); i++)
    {
        (*objs)[i]->actionMove(this, this->_keyboard);
        if (dynamic_cast<Enemy*>((*objs)[i]) && round % 15 == 0)
            (*objs)[i]->actionShoot(this, this->_keyboard);
        if (dynamic_cast<Hero*>((*objs)[i]))
            (*objs)[i]->actionShoot(this, this->_keyboard);
    }
}

void Game::processObjectsCollision()
{
    ObjectVector *objs = this->_objects;
    for (unsigned j = 0; j < objs->getSize(); j++)
    {
        AObject *o1 = (*objs)[j];
        for (unsigned i = 0; i < objs->getSize(); i++)
        {
            AObject *o2 = (*objs)[i];
            if(!((dynamic_cast<Enemy*>(o2) && dynamic_cast<BubbleEnemy*>(o1)) || (dynamic_cast<Enemy*>(o1) && dynamic_cast<BubbleEnemy*>(o2))))
                o1->processCollision(o2);
        }
    }
}

void Game::drawAllObjects()
{
    wclear(this->_gameWin);
    wborder(this->_gameWin, 0, 0, 0, 0, 0, 0, 0, 0);

    ObjectVector *objs = this->_objects;
    for (unsigned i = 0; i < objs->getSize(); i++)
        (*objs)[i]->draw(this->_gameWin);
}

void Game::removeOutOfGameObjects()
{
    WINDOW *w = this->_gameWin;
    ObjectVector *newObjs = new ObjectVector;
    ObjectVector *objs = this->_objects;
    for (unsigned i = 0; i < objs->getSize(); i++)
    {
        AObject *o = (*objs)[i];
        if (o != this->_hero && (o->outOfGame(w) || o->killed()))
        {
            if (o->killed())
                this->_score += o->getValue();
            delete o;
        }
        else
            newObjs->push_back(o);
    }
    delete objs;
    this->_objects = newObjs;
}

WINDOW *Game::getGameWindow()
{
    return (this->_gameWin);
}

void Game::restart()
{
    int nLives = this->_hero->getLives();
    for (unsigned int i = 0; i < this->_objects->getSize(); i++)
        delete (*this->_objects)[i];
    delete this->_objects;
    this->_objects = new ObjectVector;
    this->_hero = heroGenerator(this->_gameWin, nLives);
    this->addObject(this->_hero);
}

void Game::gameOver()
{
    wclear(this->_gameWin);
    for (;;)
    {
         if (_level == 4 && _hero->getLives() > 0)
            mvwprintw(this->_gameWin, getmaxy(this->_gameWin) / 2, getmaxx(this->_gameWin) / 2 - 10, "GAME OVER YOU WIN!!!");
        else
            mvwprintw(this->_gameWin, getmaxy(this->_gameWin) / 2 , getmaxx(this->_gameWin) / 2 - 10, "GAME OVER YOU LOOSE :(");
        wborder(this->_gameWin, 0, 0, 0, 0, 0, 0, 0, 0);
        wrefresh(this->_gameWin);
        if (this->_keyboard.isKeyPresed('q'))
            return;
        while (getch() != ERR);
        usleep(100000);
    }
}

void Game::run()
{
    int nLives = this->_hero->getLives();
    int round = 0;
    for (;; round++)
    {
        if (this->_keyboard.isKeyPresed('q'))
            break;

        this->addObject(landGenerator(this->_gameWin));

        if (round % 15 == 0)
            this->addObject(enemyGenerator(this->_gameWin));

        this->doObjectsAction(round);
        this->processObjectsCollision();
        this->displayScore(this->_scoreWin, this->_hero);
        if (this->_hero->getLives() <= 0)
        {
            gameOver();
            break;
        }
        if (this->getScore() && !(this->getScore() % 10))
        {
            if (_level + _score == 11)
                this->_level = 2;
            if (_level + _score == 22)
                this->_level = 3;
            if (_level + _score == 33)
            {
                this->_level = 4;
                gameOver();
                break;
            }
        }
        if (this->_hero->getLives() != nLives)
        {
            this->restart();
            nLives = this->_hero->getLives();
        }
        this->removeOutOfGameObjects();
        this->drawAllObjects();
//        this->displayScore(this->_scoreWin, this->_hero);
        wrefresh(this->_gameWin);

        while (getch() != ERR)
            ;
        if (_level == 1)
            usleep(100000);
        else if (_level == 2)
            usleep(50000);
        else
            usleep(20000);
    }
}

Enemy *Game::enemyGenerator(WINDOW *w)
{
    int x = getmaxx(w) - 3;
    int y = 1 + rand() % (getmaxy(w) - _landH - 2);
    return (new Enemy(x, y, 1));
}

LandScape *Game::landGenerator(WINDOW *w)
{

    int x = getmaxx(w) - 1;
    int bottom = getmaxy(w) - 2;
    int range = _landH - 1;
    int heigh = std::rand() % range + 1;
    return (new LandScape(x, bottom, heigh, 1));
}

Hero *Game::heroGenerator(WINDOW *w, int nLives)
{

    int x = getbegx(w) + 5;
    int y = (getmaxy(w) - 2) / 2;

    return (new Hero(x, y, nLives));
}

int Game::getLevel()
{
    return this->_level;
}

int Game::getScore()
{
    return this->_score;
}

void Game::displayScore(WINDOW *w, Hero *hero)
{
    mvwprintw(stdscr, getbegy(w) + 1, getbegx(w) + 2, "Name: %s", "Nemo");
    mvwprintw(stdscr, getbegy(w) + 2, getbegx(w) + 2, "Level: %d", this->getLevel());
    mvwprintw(stdscr, getbegy(w) + 3, getbegx(w) + 2, "Lives: %d", hero->getLives());
    mvwprintw(stdscr, getbegy(w) + 5, getbegx(w) + 2, "Score: %d", this->getScore());


    mvwprintw(stdscr, getbegy(w) + 1, getmaxx(w) / 3, "%s", "RULES: ");
    mvwprintw(stdscr, getbegy(w) + 2, getmaxx(w) / 3, "%s", "1. Your Hero can move (arrows)and shoot!(space)");
    mvwprintw(stdscr, getbegy(w) + 3, getmaxx(w) / 3, "%s", "2. For improving the level you should kill 10 enemies.");
    mvwprintw(stdscr, getbegy(w) + 4, getmaxx(w) / 3, "%s", "3. Collision with grass will take your life.");
    mvwprintw(stdscr, getbegy(w) + 5, getmaxx(w) / 3, "%s", "4. Collision with ememy will take half of your life.");
    mvwprintw(stdscr, getbegy(w) + 6, getmaxx(w) / 3, "%s", "5. Your goal is to kill 30 enemies");
    mvwprintw(stdscr, getbegy(w) + 7, getmaxx(w) / 3, "%s", "ENJOY!!!");
}
