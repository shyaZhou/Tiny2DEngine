#ifndef _ZSY_SPRITE_H_
#define _ZSY_SPRITE_H_
#include "zsyNode.h"

NS_ZSY_BEGIN

class zsySprite : public zsyNode
{
private:
    /* data */
public:
    zsySprite(/* args */);
    ~zsySprite();

    virtual void draw(zsyRender *render) override;
};

NS_ZSY_END


#endif