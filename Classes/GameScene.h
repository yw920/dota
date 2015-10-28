#ifndef _GAMESCENE_
#define _GAMESCENE_

#include "cocos2d.h"



using namespace cocos2d;

class BaseSprite;

class GameScene : public Layer
{
public:
  
	GameScene();
	~GameScene();
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	
private:
    
    void update(float dt);
    void addTouchListener();
    void initUI();
    void initBg();
    void initHeros();
    void beginAttack();
    
   void effectCallback();
    void lableCallback(Label* l);
    
    void heroDeadCallback(BaseSprite* deadSprite);
    
    void heroDeadSchedule(float dt);
    
    void initMap();
    
    Sprite* magicEffect;
    Sprite* buttonCoco;
    Sprite* panel;
    Menu* menu;
    Label* l1;
    Label* l2;
    
  
    
    ProgressTimer* hpProgressTimer;
    ProgressTimer* mpProgressTimer;
    
    ProgressTimer* effectHpProgressTimer[2];
    
    BaseSprite* coco;
    BaseSprite* eff;
    BaseSprite* boss;
   
    bool isAttackBegin;
    bool isMagic;
    
    float attackDuration;
};

#endif