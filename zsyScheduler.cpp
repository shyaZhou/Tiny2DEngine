#include "zsyScheduler.h"

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

    for(auto entry : _timerMap) {
        delete entry.second;
    }

    for(auto entry : _repeatMap) {
        delete entry.second;
    }
}

void zsyScheduler::schedulePerFrame(const std::function<void(float)> &callback, void *target, bool paused) {
    _UpdateEntry *entry = new _UpdateEntry{ target, callback, paused };
    _updateMap[target] = entry;
}

void zsyScheduler::schedule(const std::function<void(float)> &callback, float delay, unsigned int repeat, void *target, bool paused) {
    _TimerEntry *entry = new _TimerEntry{ target, callback, paused, repeat, delay };
    if(repeat == 0) {
        _timerMap[target] = entry;
    }else{
        _repeatMap[target] = entry;
    }
}


void zsyScheduler::unscheduleUpdate(void *target) {
    auto it = _updateMap.find(target);
    if(it != _updateMap.end()) {
        delete it->second;
        _updateMap.erase(it);
    }
}

void zsyScheduler::update(float dt) {
    for(auto entry : _updateMap) {
        if(!entry.second->paused) {
            entry.second->callback(dt);
        }
    }

    ZSYLOG("=======000 timerMap = %ld\n", _timerMap.size());
    for (auto entry : _timerMap) {
        if(!entry.second->paused) {
            entry.second->callback(dt);
        }
        delete entry.second;
    }

    _timerMap.clear();
    ZSYLOG("=======111 timerMap = %ld\n", _timerMap.size());

    // 迭代器失效，需要该方法
    // for(auto entry : _repeatMap)
    // std::unordered_map<void *, _TimerEntry *> repeatmap;
    // std::swap(_repeatMap, repeatmap);

    bool isFix = false;
    for (auto it = _repeatMap.begin(); it != _repeatMap.end();) {
        isFix = false;
        auto entry = *it;
        if(!entry.second->paused) {
            entry.second->time -= dt;
            if(entry.second->time <= 0.0f) {
                entry.second->callback(dt);
                if(entry.second->repeat != -1) {
                    entry.second->repeat--;
                    if(entry.second->repeat == 0){
                        auto p = it->second;
                        it = _repeatMap.erase(it);
                        delete p;
                        isFix = true;
                    }
                } 
            }
        }
        if(!isFix) ++it;
    }
}
