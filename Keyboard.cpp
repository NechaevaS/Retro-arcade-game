#include "Keyboard.hpp"
#include "ncurses.h"

Keyboard::Keyboard(){}

Keyboard::~Keyboard() {}

bool Keyboard::isKeyPresed(int code) const
{
    int ch = getch();
    if (ch != code)
    {
        ungetch(ch);
        return (false);
    }
    return(true);
}