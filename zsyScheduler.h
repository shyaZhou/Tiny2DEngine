#ifndef _ZSY_SCHDULER_H_
#define _ZSY_SCHDULER_H_
#include "zsyMarco.h"
#include <unordered_map>
#include <functional>

NS_ZSY_BEGIN

struct _UpdateEntry{
    // 回调对象
    void *target;
    // 可调用对象
    std::function<void(float)> callback;
    bool paused;
};

struct _UpdateOnceEntry{
    void *target;
    std::function<void(float)> callback;
    bool paused;
};

class zsyScheduler
{
private:
    std::unordered_map<void *, _UpdateEntry *> _updateMap;
    std::unordered_map<void *, _UpdateOnceEntry *> _updateOnceMap;
public:
    zsyScheduler(/* args */);
    ~zsyScheduler();

    // 保存任何类对象，只要T类型有update方法且update方法为void*(float)，保存在_UpdateEntry中
    template<typename T>
    void scheduleUpdate(T *target, bool paused) {
        // 闭包
        this->schedulePerFrame([target](float dt){
            target->update(dt);
        }, target, paused);
    }

    template<typename T>
    void scheduleUpdateOnce(T *target, bool paused) {
        // 闭包
        this->schedulePerFrame([target](float dt){
            target->update(dt);
        }, target, paused);
    }
    void unscheduleUpdate(void *target);
    void doOnce(void *target, float dt);
    void schedulePerFrame(const std::function<void(float)> &callback, void *target, bool paused);
    void scheduleOnce(const std::function<void(float)> &callback, void *target, bool paused);
    void update(float dt);
};

NS_ZSY_END


#endif