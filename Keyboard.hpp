#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

class Keyboard
{
    private:
        Keyboard(const Keyboard&);
        Keyboard &operator=(const Keyboard&);
    public:
        Keyboard();
        ~Keyboard();
        bool isKeyPresed(int code) const;
};

#endif