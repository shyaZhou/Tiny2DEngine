#ifndef _ZSY_DIRECTOR_H_
#define _ZSY_DIRECTOR_H_
#include "zsyMarco.h"
#include "zsyRender.h"
#include <vector>
#include <sys/time.h>
#include "zsyScene.h"
#include "zsyScheduler.h"
#include "zsyAutoreleasePool.h"


NS_ZSY_BEGIN

// 游戏中所有场景的内存维护由Director进行
class zsyDirector
{
private:
    // 切换场景放在帧处理中回调
    // 备忘录模式，场景切换过程都能保存下来
    // 场景
    Vector<zsyScene *> _scenes;
    zsyScene *_runningScene;
    zsyScene *_nextScene;

    // 图形绘制
    // 由导演进行维护, 由director创建时选择图形库
    zsyRender *_render;

    // 调度器
    // 委托模式
    zsyScheduler *_scheduler;

    // AutoreleasePool
    zsyAutoreleasePool *_releasePool;
    
    // fps
    float _fps;
    float _deltaTime;
    // 时间戳，控制帧率
    timeval _lastUpdate;

    bool _paused;

    static zsyDirector *_instance;

public:
    // 场景状态控制
    void start();
    void pause();
    void resume();
    void restart();

    // 切换场景
    void runScene(zsyScene *scene);
    void popScene(zsyScene *scene); 
    void replaceScene(zsyScene *scene);
    void pushScene(zsyScene *scene);

    void mainLoop();
    void drawScene();
    bool calculateDeltaTime();
    void setNextScene();

public:
    static zsyDirector *instance();
    zsyDirector(/* args */);
    ~zsyDirector();
    bool init();

    // 返回给director进行调用
    inline zsyScheduler *getScheduler() {return _scheduler;}
    inline zsyAutoreleasePool *getAutoreleasePool(){ return _releasePool; }
};

NS_ZSY_END

#endif