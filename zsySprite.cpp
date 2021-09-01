#include "zsySprite.h"
#include "zsyMarco.h"
#include "zsyRender.h"

USING_NS_ZSY;

zsySprite::zsySprite(/* args */)
{
    ZSYLOG("构造Sprite --- address = %p ; \n", this);
}

zsySprite::~zsySprite()
{
    ZSYLOG("析构Sprite --- address = %p ; name = %s\n", this, _name.c_str());
}

void zsySprite::draw(zsyRender *render) {
    if(_visible)
        render->draw(this);
    ZSYLOG("zsySprite --- draw ! name = %s, children = %ld\n", _name.c_str(), _children.size());
}
