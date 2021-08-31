#include "zsyRender.h"
#include "zsyMarco.h"
#include "zsyNode.h" 

USING_NS_ZSY;

zsyRender::zsyRender(/* args */)
{
}

zsyRender::~zsyRender()
{
}

// 介入图形库
void zsyRender::draw(zsyNode *node) {
    ZSYLOG("render node x = %f, y = %f \n", node->_x, node->_y);
}