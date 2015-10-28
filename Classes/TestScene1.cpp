#include "TestScene1.h"


USING_NS_CC;

TestScene1::TestScene1(){}

TestScene1::~TestScene1(){}


Scene* TestScene1::createScene()
{
    auto scene = Scene::create();
    auto layer = TestScene1::create();
    scene->addChild(layer);
    
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
//    _eventDispatcher->addCustomEventListener("my",[](EventCustom* e)->void{
//        CCLOG("%s",e->getUserData());
//    });
//    schedule(schedule_selector(TestScene::update),1.0f);
   
    return true;
}

void TestScene1::update(float dt){
    
}

