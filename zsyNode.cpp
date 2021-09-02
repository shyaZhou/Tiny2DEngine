#include "zsyNode.h"
#include <algorithm>
#include "zsyMarco.h"
#include "zsyDirector.h"

NS_ZSY_BEGIN

zsyNode::zsyNode() 
    : _name("")
    , _tag(0)
    , _visible(true)
    , _localZOrder(0)
    , _x(0)
    , _y(0)
    , _reorderChildDirty(false)
    , _pause(false)
{
    ZSYLOG("构造Node --- address = %p \n", this);
}
zsyNode::~zsyNode(){
    // for(auto child : _children)
    //     child->release();
    ZSYLOG("析构Node --- address = %p ; name = %s \n", this, _name.c_str());
}

zsyNode *zsyNode::getChildByName(const std::string &name) const{
    for(const auto &child : _children) {
        if(child->_name.compare(name) == 0) 
            return child;
    }
    return nullptr;
}

zsyNode *zsyNode::getChildByTag(int tag) const {
    for(const auto &child : _children) {
        if(child->_tag == tag) return child;
    }
    return nullptr;
}

void zsyNode::addChild(zsyNode *child, int localZOrder, int tag){
    // 引用计数+1
    // child->retain();
    
    child->_parent = this;
    _children.push_back(child);
    child->_tag = tag;
    child->_localZOrder = localZOrder;
    _reorderChildDirty = true;
}

void zsyNode::removeChild(zsyNode* child){
    if(_children.empty()) return;
    auto iter = std::find(std::begin(_children), std::end(_children), child);
    if(iter != _children.end()){
        _children.erase(iter);
    }
}
void zsyNode::removeChildByName(const std::string& name){
    for(auto it = std::begin(_children); it != std::end(_children); ++it) {
        if((*it)->_name.compare(name) == 0) {
            _children.erase(it);
            break;
        }
    }
}
void zsyNode::removeChildByTag(int tag){
    for(auto it = std::begin(_children); it != std::end(_children); ++it) {
        if((*it)->_tag == tag) {
            _children.erase(it);
            break;
        }
    }
}
void zsyNode::sortAllChildren(){
    if(_reorderChildDirty) {
        sortNodes(_children);
        _reorderChildDirty = false;
    }
}

void zsyNode::visit(zsyRender *render) {
    int i = 0;
    if(!_children.empty()) {
        sortAllChildren();
        // left draw
        for(; i < _children.size(); i++) {
            auto node = _children.at(i);
            // 渲染左子树
            if(node && node->_localZOrder < 0) {
                node->visit(render);
            } else {
                break;
            }
        }
        // self draw
        this->draw(render);

        // right draw
        for(auto it = _children.begin() + i; it != _children.end(); ++it) {
            (*it)->visit(render);
        } 
    }else{
        this->draw(render);
    }
}

// 渲染方法
void zsyNode::draw(zsyRender *render) {
    if(_visible) {
        render->draw(this);
        ZSYLOG("zsyNode --- draw ! name = %s, children = %ld\n", _name.c_str(), _children.size());
    }
}

// 注册到调度中
void zsyNode::scheduleUpdate(){
    zsyDirector::instance()->getScheduler()->scheduleUpdate(this, _pause);
}
void zsyNode::unscheduleUpdate(){
    zsyDirector::instance()->getScheduler()->unscheduleUpdate(this);
}
void zsyNode::resume(){
    _pause = false;

    for(auto child : _children){
        child->resume();
    }
}
void zsyNode::pause(){
    _pause = true;

    for(auto child: _children){
        child->pause();
    }
}
void zsyNode::onEnter(){
    for(auto child: _children){
        child->onEnter();
    }
}
void zsyNode::onExit(){
    for(auto child: _children){
        child->onExit();
    }
}

// 是否update直接走scheduler，无需在此回调
void zsyNode::update(float dt) {

}

void zsyNode::scheduleOnce(std::function<void(float)> callback){
    zsyDirector::instance()->getScheduler()->scheduleOnce(this, [callback](float dt){
        ZSYLOG("==============SCHEDULE ONCE!==================\n");
        callback(dt);
    });
}
void zsyNode::schedule(std::function<void(float)> callback, int repeat, float delay){
    zsyDirector::instance()->getScheduler()->schedule(this, [callback](float dt){
        callback(dt);
        ZSYLOG("==============SCHEDULE REPEAT!==================\n");
    }, 1.0f, repeat, false);
    // -1表示无限循环下去
}

NS_ZSY_END