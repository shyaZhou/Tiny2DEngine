#include <iostream>
#include "zsyMarco.h"
#include "zsyNode.h"
#include "zsyScene.h"
#include "zsyDirector.h"

USING_NS_ZSY;

int main() {
    zsyScene *scene = new zsyScene();
    scene->setName("zsyScene");

    for (int i = 2; i >= -2; i--) {
        auto p = new zsyNode();
        p->setName("Node - " + std::to_string(i));
        scene->addChild(p, i, i);
    }

    zsyDirector::instance()->runScene(scene);

    delete scene;
    return 0;
}