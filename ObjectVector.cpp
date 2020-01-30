#include "ObjectVector.hpp"

ObjectVector::ObjectVector()
{
    this->_data = new AObject *[_inc];
    this->_maxSize = _inc;
    this->_size = 0;
}

ObjectVector::~ObjectVector()
{
    delete [] this->_data;
}

unsigned int ObjectVector::getSize()
{
    return(this->_size);
}

void ObjectVector::push_back(AObject *o)
{
    if (this->_size == this->_maxSize)
    {
        unsigned int newSize = this->_maxSize + _inc;
        AObject **tmp = new AObject *[newSize];
        for (unsigned int i = 0; i < this->_size; i++)
            tmp[i] = this->_data[i];
        this->_maxSize = newSize;
        delete []this->_data;
        this->_data = tmp;
    }
    this->_data[this->_size++] = o;
}

AObject *ObjectVector::operator[](unsigned int i)
{
    return (this->_data[i]);
}