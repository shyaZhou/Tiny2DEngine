#ifndef _ZSY_RENDER_H_
#define _ZSY_RENDER_H_
#include "zsyMarco.h"

NS_ZSY_BEGIN

class zsyNode;
class zsyRender
{
private:
    /* data */
public:
    zsyRender(/* args */);
    ~zsyRender();

    void draw(zsyNode *node);
};

NS_ZSY_END

#endif