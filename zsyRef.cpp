#include "zsyRef.h"
#include "zsyMarco.h"

USING_NS_ZSY;

zsyRef::zsyRef() : _reference(1)
{
}

zsyRef::~zsyRef()
{
}

void zsyRef::retain() {
    ++_reference;
}

void zsyRef::release() {
    --_reference;
    if(_reference == 0) {
        delete this;
    }
}