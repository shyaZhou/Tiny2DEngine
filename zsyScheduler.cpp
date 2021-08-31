#include "zsyScheduler.h"
#include "zsyMarco.h"

USING_NS_ZSY;

zsyScheduler::zsyScheduler(/* args */)
{
}

zsyScheduler::~zsyScheduler()
{
    // 在哪创建就在哪释放
    for(auto entry : _updateMap) {
        delete entry.second;
    }
}

void zsyScheduler::schedulePerFrame(const std::function<void(float)> &callback, void *target, bool paused) {
    _UpdateEntry *entry = new _UpdateEntry{ target, callback, paused };
    _updateMap[target] = entry;
}

void zsyScheduler::unscheduleUpdate(void *target) {
    auto it = _updateMap.find(target);
    if(it != _updateMap.end()) {
        delete it->second;
        _updateMap.erase(it);
    }
}

void zsyScheduler::scheduleOnce(const std::function<void(float)> &callback, void *target, bool paused) {
    _UpdateOnceEntry *entry = new _UpdateOnceEntry{ target, callback, paused };
    _updateOnceMap[target] = entry;
}

void zsyScheduler::update(float dt) {
    for(auto entry : _updateMap) {
        if(!entry.second->paused) {
            entry.second->callback(dt);
        }
    }
}

void zsyScheduler::doOnce(void *target, float dt) {
    auto it = _updateOnceMap.find(target);
    if(it != _updateOnceMap.end()) {
        if(!it->second->paused) {
            it->second->callback(dt);
        }
        delete it->second;
        _updateOnceMap.erase(it);
    }
}