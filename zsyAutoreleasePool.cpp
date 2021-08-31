#include "zsyAutoreleasePool.h"
#include "zsyMarco.h"

USING_NS_ZSY;

zsyAutoreleasePool::zsyAutoreleasePool(/* args */)
{
    _objects.reserve(100);
}

zsyAutoreleasePool::~zsyAutoreleasePool()
{
    clear();
}

// 维护需要管理的对象
void zsyAutoreleasePool::addObject(zsyRef *object) {
    
}

// 引用计数-1->释放
void zsyAutoreleasePool::clear() {

}