#ifndef _ZSY_MARCO_H_
#define _ZSY_MARCO_H_

#include<cassert>
#include<cstring>
#include<stdio.h>
#define ZSYASSERT(cond, msg) do {                              \
        if (!(cond)) {                                          \
            if (strlen(msg)) \
                printf("Assert failed: %s", msg);             \
        assert(cond);                                      \
        } \
    } while (0)

#define ZSYLOG(fmt,...) do { printf(fmt, ##__VA_ARGS__); } while(0)
#define NS_ZSY_BEGIN                 namespace zsy{
#define NS_ZSY_END                   }
#define USING_NS_ZSY                 using namespace zsy

#define ZSY_SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define ZSY_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define ZSY_SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define ZSY_SAFE_RELEASE(p)          do { if(p) { (p)->release(); } } while(0)
#define ZSY_SAFE_RELEASE_NULL(p)     do { if(p) { (p)->release(); (p) = nullptr; } } while(0)
#define ZSY_SAFE_RETAIN(p)           do { if(p) { (p)->retain(); } } while(0)
#define ZSY_BREAK_IF(cond)           if(cond) break

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

#endif