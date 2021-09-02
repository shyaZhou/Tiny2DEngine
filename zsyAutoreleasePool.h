#ifndef _ZSY_AUTORELEASE_H_
#define _ZSY_AUTORELEASE_H_
#include "zsyMarco.h"
#include <vector>

NS_ZSY_BEGIN

class zsyRef;

// 内存管理
class zsyAutoreleasePool
{
private:
    std::vector<zsyRef *> _objects;
public:
    zsyAutoreleasePool(/* args */);
    ~zsyAutoreleasePool();

    void addObject(zsyRef *object);

    // director中每帧进行清理
    void clear();
};

NS_ZSY_END

#endif 
