#include "MyScene.h"
#include "zsySprite.h"

USING_NS_ZSY;

MyScene::MyScene(/* args */)
{
}

MyScene::~MyScene()
{
}

bool MyScene::init(){
    // 未释放内存
    // auto sprite = new zsySprite();
    auto sprite = zsySprite::create();
    // sprite->autorelease();
    sprite->setName("my --- sprite");
    this->addChild(sprite, 1);


    auto node = zsyNode::create();
    // 使用create
    // auto node = new zsyNode();
    // node->init();
    // node->autorelease();

    node->setName("my ---- node");
    this->addChild(node, -1);
    return true;
}

void MyScene::onEnter(){
    zsyNode::onEnter();
    
    // 添加任务
    this->scheduleUpdate();
}
void MyScene::onExit(){

    zsyNode::onExit();
    // 清理任务
    this->unscheduleUpdate();
}
void MyScene::update(float dt){
    ZSYLOG("===========MyScene - update %f \n", dt);
}
void MyScene::render(zsyRender* render){
    this->visit(render);
    // 如果有相机，此处逻辑会不一样，应该渲染相机
}