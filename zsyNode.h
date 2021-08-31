#ifndef _ZSY_NODE_H_
#define _ZSY_NODE_H_

#include "zsyMarco.h"
#include <string>
#include <vector>
#include <algorithm>
#include "zsyRef.h"
#include "zsyVector.h"
#include <functional>

NS_ZSY_BEGIN

class zsyRender;
class zsyNode
{
    friend class zsyRender;

public:
    zsyNode(/* args */);
    ~zsyNode();
    virtual bool init(){ return true; }

public:
    // CREATE_FUNC(zsyNode);

public:
    // 通过名字获取子节点
    virtual zsyNode* getChildByName(const std::string& name) const;
    
    // 通过模版获取子节点
    template<typename T>
    T getChildByName(const std::string& name) const { 
        return static_cast<T>(getChildByName(name)); 
    }

    virtual zsyNode * getChildByTag(int tag) const;

    template<typename T>
    T getChildByTag(int tag) const { return static_cast<T>(getChildByTag(tag)); }

    virtual void addChild(zsyNode* child, int localZOrder = 0, int tag = 0);
    virtual void removeChild(zsyNode* child);
    virtual void removeChildByName(const std::string& name);
    virtual void removeChildByTag(int tag);

    void sortAllChildren();

    // 启动调度update
    void scheduleUpdate();
    void unscheduleUpdate();
    void resume();
    void pause();

    virtual void onEnter();
    virtual void onExit();

    // virtual void scheduleOnce(std::function<void(float)> callback);
    // virtual void schedule(std::function<void(float)> callback, int repeat, float delay);

    // 进入节点，会去渲染自己的节点和子节点
    virtual void visit(zsyRender* render);
    virtual void draw(zsyRender* render);
    virtual void update(float dt);

    template<typename _T> inline
    static void sortNodes(std::vector<_T*>& nodes)
    {
        static_assert(std::is_base_of<zsyNode, _T>::value, "Node::sortNodes: Only accept derived of Node!");

        std::sort(std::begin(nodes), std::end(nodes), [](_T* n1, _T* n2) {
            return n1->_localZOrder < n2->_localZOrder;
        });
    }

public:
    virtual inline void setName(const std::string& name) { _name = name; }
    virtual inline const std::string getName() const { return _name; }
    virtual inline void setTag(int tag) { _tag = tag; }
    virtual inline int getTag() const { return _tag; }
    virtual inline void setVisible(bool visible) { _visible = visible; }
    virtual inline bool isVisible() const { return _visible; }
    virtual inline void setLocalZOrder(int tag) { _tag = tag; }
    virtual inline int getLocalZOrder() const { return _tag; }

protected:
    std::string _name;
    int _tag;
    bool _visible;
    // 判断在哪棵子树，<0左子树，>0右子树
    int _localZOrder;
    // 屏幕中坐标
    float _x, _y;
    // 是否是脏数据
    bool _reorderChildDirty;
    bool _pause;

    std::vector<zsyNode*> _children;
    zsyNode* _parent;

};

NS_ZSY_END

#endif