#ifndef OBJECTVECTOR_HPP
#define OBJECTVECTOR_HPP

#include "AObject.hpp"

class ObjectVector
{
    private:
        AObject **_data;
        unsigned int _size;
        unsigned int _maxSize;
        static const unsigned int _inc = 2;

    public:
        ObjectVector();
        ~ObjectVector();
        unsigned int getSize();
        void push_back(AObject *);
        AObject *operator[](unsigned int i);

};
#endif