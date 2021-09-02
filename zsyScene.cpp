#include "zsyScene.h"
#include "MyScene.h"
#include "zsyDirector.h"

USING_NS_ZSY;

zsyScene::zsyScene(/* args */)
{
}

zsyScene::~zsyScene()
{
}

void zsyScene::onEnter(){
    zsyNode::onEnter();
    
    // 添加任务
    this->scheduleUpdate();
}

void zsyScene::onExit(){
    zsyNode::onExit();
    // 清理任务
    this->unscheduleUpdate();
}

void zsyScene::update(float dt){
    ZSYLOG("===========zsyScene - update %f \n", dt);

    auto myScene = new MyScene();
    if(myScene->init()){
        myScene->setName("MyScene");
        zsyDirector::instance()->pushScene(myScene);
    }
}
void zsyScene::render(zsyRender* render){
    this->visit(render);
    // 如果有相机，此处逻辑会不一样，应该渲染相机
}