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

struct _TimerEntry{
    void *target;
    std::function<void(float)> callback;
    bool paused;
    unsigned int repeat;
    float time;
};

class zsyScheduler
{
private:
    std::unordered_map<void *, _UpdateEntry *> _updateMap;
    std::unordered_map<void *, _TimerEntry *> _repeatMap; // 重复N次
    std::unordered_map<void *, _TimerEntry *> _timerMap; // 重复1次
public:
    zsyScheduler(/* args */);
    ~zsyScheduler();

    template<typename T>
    void scheduleOnce(T *target, std::function<void(float)> callback, bool paused = false) {
        this->schedule(callback, 0.0f, 0, target, paused);
    }

    template<typename T>
    void schedule(T *target, std::function<void(float)> callback, float delay, unsigned int repeat, bool paused = false) {
        this->schedule(callback, delay, repeat, target, paused);
    }

    void schedule(const std::function<void(float)> &callback, float delay, unsigned int repeat, void *target, bool paused);

    // 保存任何类对象，只要T类型有update方法且update方法为void*(float)，保存在_UpdateEntry中
    template<typename T>
    void scheduleUpdate(T *target, bool paused) {
        // 闭包
        this->schedulePerFrame([target](float dt){
            target->update(dt);
        }, target, paused);
    }

    void unscheduleUpdate(void *target);
    void schedulePerFrame(const std::function<void(float)> &callback, void *target, bool paused);
    void update(float dt);
};

NS_ZSY_END


#endif