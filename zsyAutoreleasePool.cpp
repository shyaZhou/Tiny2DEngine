#include "zsyAutoreleasePool.h"
#include "zsyMarco.h"
#include "zsyRef.h"

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
    _objects.push_back(object);
}

// 引用计数-1->释放
void zsyAutoreleasePool::clear() {
    std::vector<zsyRef *> releasings;
    releasings.swap(_objects);
    for(auto obj : releasings) {
        obj->release();
    }
}