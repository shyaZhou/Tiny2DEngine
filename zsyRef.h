#ifndef _ZSY_REF_H_
#define _ZSY_REF_H_
#include "zsyMarco.h"

NS_ZSY_BEGIN

class zsyRef
{
private:
    // Node继承Ref
    unsigned int _reference;

// 不允许外部创建释放
protected:
    zsyRef(/* args */);
    virtual ~zsyRef();

public:

    // 引用，使用此方法后内存由Ref维护
    void retain();
    // 释放
    void release();
    zsyRef *autorelease();
};

NS_ZSY_END

#endif