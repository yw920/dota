//
//  TestScene.hpp
//  MyCppGame
//
//  Created by yw on 15/10/27.
//
//

#ifndef TestScene_hpp_1
#define TestScene_hpp_1

#include "cocos2d.h"

USING_NS_CC;

class TestScene1:public Layer
{
public:
    
    TestScene1();
    ~TestScene1();
    
    static Scene* createScene();
    
    
    virtual bool init();
 
    CREATE_FUNC(TestScene1);
    
private:
    void update(float dt);
};

#endif /* TestScene_hpp */
