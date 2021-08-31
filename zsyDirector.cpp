#include "zsyDirector.h"
#include <thread>

USING_NS_ZSY;

zsyDirector *zsyDirector::_instance = nullptr;
zsyDirector *zsyDirector::instance() {
    // 游戏启动不可能通过多线程启动，因此Director启动用考虑多线程情况
    if(_instance == nullptr) {
        _instance = new zsyDirector();
        // 两部构造法，第一步做内存申请，第二步申请图形
        _instance->init();
    }
    return _instance;
}

zsyDirector::zsyDirector(/* args */)
    :_runningScene(nullptr)
    ,_nextScene(nullptr)
    ,_render(nullptr)
    ,_scheduler(nullptr)
    ,_fps(1)
    ,_deltaTime(0)
    ,_lastUpdate{0, 0}
    ,_paused(false)
    ,_releasePool(nullptr)
{
}

zsyDirector::~zsyDirector()
{
    ZSY_SAFE_DELETE(_render);
    ZSY_SAFE_DELETE(_scheduler);
    ZSY_SAFE_DELETE(_releasePool);
}

bool zsyDirector::init() {
    // 图形
    _render = new zsyRender();
    // 调度器
    _scheduler = new zsyScheduler();
    // Autorelease
    _releasePool = new zsyAutoreleasePool();
    return true;
}
void zsyDirector::mainLoop(){
    while(true) {
        if(calculateDeltaTime()) { // 帧率控制
            //绘制场景
            drawScene();
        }else {
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }
}
void zsyDirector::drawScene(){
    if(_paused) return;

    // 切换场景放在回调事件里
    setNextScene();

    // 处理回调scheduler /帧事件
    _scheduler->update(_deltaTime);

    //绘制scene
    if(_runningScene) {
        _runningScene->render(_render);
    }

    // 释放
    _releasePool->clear();
}
bool zsyDirector::calculateDeltaTime(){
    timeval now;
    if(gettimeofday(&now, nullptr) != 0) {
        return false;
    }
    float elapsed = now.tv_sec - _lastUpdate.tv_sec + (now.tv_usec - _lastUpdate.tv_usec) / 1000000.0f;
    if(elapsed >= 1 / _fps) {
        // 时间间隔需要向上传递
        _lastUpdate = now;
        _deltaTime = elapsed;
        return true;
    }
    return false;
}

void zsyDirector::setNextScene(){
    if(_nextScene) {
        if(_runningScene) {
            _runningScene->onExit();
        }
        _runningScene = _nextScene;
        _nextScene = nullptr;
        _runningScene->onEnter();
    }
}

void zsyDirector::start() {
    _paused = false;
    _deltaTime = 0;
    gettimeofday(&_lastUpdate, nullptr);
    this->mainLoop();
}

void zsyDirector::pause() {
    if(_paused) return;
    _paused = true;
    _deltaTime = 0;
    // // 暂停的时候场景中的物体也应该暂停
    // _scheduler->pause

}

void zsyDirector::resume() {
    _paused = false;
    // pause scheduler
}
void zsyDirector::restart() {
    
}

// 切换场景
void zsyDirector::runScene(zsyScene *scene) {
    _scenes.push_back(scene);
    _nextScene = scene;
    this->start();
}
void zsyDirector::pushScene(zsyScene *scene) {
    _scenes.push_back(scene);
    _nextScene = scene;
}
void zsyDirector::popScene(zsyScene *scene) {
    if(_scenes.size() > 1) {
        _scenes.pop_back();
        _nextScene = _scenes.back();
    } else {

    }
}
void zsyDirector::replaceScene(zsyScene *scene) {
    if(_scenes.size() > 0) 
        _scenes.pop_back();
    _scenes.push_back(scene);
    _nextScene = scene;
}