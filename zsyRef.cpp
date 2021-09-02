#include "zsyRef.h"
#include "zsyDirector.h"

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

// --, ==0 ? 释放
void zsyRef::release() {
    --_reference;
    if(_reference == 0) {
        delete this;
    }
}

// 把当前对象插入autoreleasePool
zsyRef *zsyRef::autorelease() {
    // 放入director中是因为director每帧会做clear
    zsyDirector::instance()->getAutoreleasePool()->addObject(this);
    return this;
}