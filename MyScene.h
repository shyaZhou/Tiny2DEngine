#ifndef _MY_SCENE_H_
#define _MY_SCENE_H_
#include "zsyMarco.h"
#include "zsyNode.h"
#include "zsyScene.h"

NS_ZSY_BEGIN

class zsyRender;
class MyScene : public zsyScene
{
private:
    /* data */
public:
    MyScene(/* args */);
    ~MyScene();
public:

    virtual bool init();
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float dt) override;
    virtual void render(zsyRender* render);
};

NS_ZSY_END

#endif