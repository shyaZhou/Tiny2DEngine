#ifndef _ZSY_SCENE_H_
#define _ZSY_SCENE_H_
#include "zsyMarco.h"
#include "zsyNode.h"

NS_ZSY_BEGIN

class zsyRender;
class zsyScene : public zsyNode
{
protected:
    zsyScene(/* args */);
    ~zsyScene();

public:
    CREATE_FUNC(zsyScene);
    
public:

    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void update(float dt) override;
    virtual void render(zsyRender* render);
};

NS_ZSY_END

#endif