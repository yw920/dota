#include "TestScene.hpp"
#include "Config.h"
#include "json/document.h"
#include "BaseSprite.h"

USING_NS_CC;



Scene* TestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    
   
   auto lis =EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [this](Touch* t,Event* e)->bool{
        CCLOG("%f,%f",t->getLocation().x,t->getLocation().y);
        Vec2 newV =this->convertToNodeSpace(t->getLocation());
          CCLOG("%f,%f",newV.x,newV.y
                );
        
        return true;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
    
    
    
    
    _eventDispatcher->addCustomEventListener("hurting", [](EventCustom* e){
        CCLOG("%s",(char*)e->getUserData());
    });
    schedule(schedule_selector(TestScene::update),1.0f);
    
    auto coco = BaseSprite::create(std::string("pfca/Coco.fca"), std::string("Coco"));
   // coco->setRotation(180.0f);
//coco->playAnimation(BaseSprite::State::walk);
    coco->setPosition(0,0);
    addChild(coco,1);
    
    auto move =MoveBy::create(2, Vec2(-200,0));
        
    coco->runAction(move);
    
    auto l = Label::createWithTTF("-123", "fonts/Marker Felt.ttf",30);
    l->setPosition(_director->getWinSize()/2);
    l->setColor(Color3B::ORANGE);
    addChild(l);
    
    return true;
}

void TestScene::update(float dt)
{
     char data[30]="fuck";
    _eventDispatcher->dispatchCustomEvent("hurting",&data);

}


