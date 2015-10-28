#include "GameScene.h"
#include "json/document.h"
#include "BaseSprite.h"
#include "OverScene.h"


#define moveAction 1
USING_NS_CC;

GameScene::GameScene()
:isAttackBegin(false),
magicEffect(nullptr),
isMagic(false),
attackDuration(0.0f)

{
}
GameScene::~GameScene()
{
}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
	{
        
		return false;
	}
    
    initBg();
    
    initUI();
    
    initHeros();
    
    addTouchListener();
   
	
    scheduleUpdate();
    
	return true;
}

void GameScene::initBg(){
    auto bg = Sprite::create("bbg_blood_elf_door.jpg");
    bg->setPosition(_director->getVisibleSize()/2);
    addChild(bg,0);
    
}

void GameScene::effectCallback(){
    eff->setVisible(false);
    isMagic = false;
}

void GameScene::addTouchListener()
{
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* t,Event* e)->bool{
        auto menuCoo = menu->convertToNodeSpace(t->getLocation());
        Rect oldAABB =  buttonCoco->getBoundingBox();
        Vec2 oldVec = oldAABB.origin;
        Vec2 newVec = oldVec-buttonCoco->getContentSize()/2;
        Rect newAABB(newVec.x,newVec.y,oldAABB.size.width,oldAABB.size.height);
        
        if(mpProgressTimer->getPercentage()==100.0f&&newAABB.containsPoint(menuCoo)){
            isMagic = true;
            coco->playAnimation(BaseSprite::State::magic);
            if(!eff){
             eff = EffSprite::create("pfca/effect/eff_point_Coco_ult.fca", "effect/eff_point_Coco_ult");
            this->addChild(eff);
            }
            eff->setVisible(true);
            eff->setPosition(0-_director->getWinSize().width/2,0);
            eff->playAnimation(BaseSprite::State::magic,CallFunc::create(CC_CALLBACK_0(GameScene::effectCallback, this)));
            
            mpProgressTimer->setPercentage(0.f);
            
        }
        
        return true;
    };
    
    auto hurtLisener = EventListenerCustom::create("hurt", [this](EventCustom* e)->void{
      
        auto hurtObject = (BaseSprite*)e->getUserData();
        Label* l = nullptr;
       ProgressTimer* hp = nullptr;
        if(hurtObject==boss){
            l = l1;
            hp = effectHpProgressTimer[0];
            
        }else{
            l  = l2;
            hp = effectHpProgressTimer[1];
        }
        if(dynamic_cast<TreeBoss*>(hurtObject)){
            l->setPosition(hurtObject->getPosition()+Vec2(_director->getWinSize().width/2,_director->getWinSize().height/2+200));
            hp->setPosition(hurtObject->getPosition()+Vec2(_director->getWinSize().width/2,_director->getWinSize().height/2+180));
            
        }
        else{
              l->setPosition(hurtObject->getPosition()+Vec2(_director->getWinSize().width/2,_director->getWinSize().height/2+100));
            hp->setPosition(hurtObject->getPosition()+Vec2(_director->getWinSize().width/2,_director->getWinSize().height/2+130));
        }
       
        hp->setPercentage((hurtObject->getProperty().curLife/hurtObject->getProperty().maxLife)*100);

        
        
        l->setString("-"+Value((int)hurtObject->getCurHurt()).asString());
        if(!l->getParent()){
           
            this->addChild(l,3);
        }
        if(!hp->getParent()){
            this->addChild(hp,3);
        }
        hp->setVisible(true);
        if(!l->isVisible()){
            l->setVisible(true);
            l->setOpacity(255);
        }
        auto move = MoveBy::create(0.5f, Vec2(0,20));
        auto fade = FadeOut::create(0.5f);
        
        l->runAction(Sequence::create(move, fade,CallFunc::create(std::bind(&GameScene::lableCallback, this,l)),nullptr));
        
        hp->runAction(Sequence::create(DelayTime::create(1.0f),CallFuncN::create([](Node* n){
            n->setVisible(false);
        }), NULL));
    });
    
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,buttonCoco);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(hurtLisener,this);
    
    
}

void GameScene::lableCallback(Label* l)
{
    l->setVisible(false);
}

void GameScene::heroDeadSchedule(float dt)
{
    auto fadeOut = FadeOut::create(2.0f);
    auto fadeOutCallback = CallFunc::create(std::bind(&GameScene::heroDeadCallback, this,coco));
    coco->runAction(Sequence::create(fadeOut,fadeOutCallback,nullptr));
}

void GameScene::heroDeadCallback(BaseSprite *deadSprite)
{
    deadSprite->setVisible(false);
    _eventDispatcher->removeAllEventListeners();
    
    //_eventDispatcher->
}

void GameScene::update(float dt)
{
       
    if(boss->getPositionX()-_director->getWinSize().width/4-coco->getPositionX()<coco->getProperty().range&&!isAttackBegin){
        coco->stopActionByTag(moveAction);
        isAttackBegin = true;
        coco->attack(boss);
        boss->attack(coco);
    }
    
    if(coco->getProperty().curLife<=0&&!coco->isDead()){
        coco->setDead();
        coco->playAnimation(BaseSprite::State::dead);
        scheduleOnce(schedule_selector(GameScene::heroDeadSchedule),1.0f);
    }
    
    
    if(boss->getProperty().curLife<=0&&!boss->isDead()){
        boss->setDead();
        boss->playAnimation(BaseSprite::State::dead);
        boss->runAction(Sequence::create(DelayTime::create(1.0f),CallFunc::create([this](){
            Scene* overScene = OverScene::createScene();
            _director->replaceScene(TransitionCrossFade::create(2.0f,overScene));
            
            
        
        }), NULL));
    }
    
    
    if(isAttackBegin&&!isMagic){
        coco->update(dt, boss);
        boss->update(dt, coco);
        
    }
    if(isMagic){attackDuration = 2.5f;}
    mpProgressTimer->setPercentage(mpProgressTimer->getPercentage()+0.5f);
    hpProgressTimer->setPercentage((coco->getProperty().curLife/coco->getProperty().maxLife)*100);
   
}

void GameScene::beginAttack()
{
    
}

void GameScene::initMap()
{
    
	
}

void GameScene::initUI()
{
   panel = Sprite::create("panel/panel.png");
    panel->setPosition(_director->getVisibleSize().width/2,panel->getContentSize().height/2);
    
    
    buttonCoco = Sprite::create("UI/DOTA-HERO/Coco.jpg");
    auto itemHero = MenuItemSprite::create(buttonCoco,buttonCoco);
    
    hpProgressTimer = ProgressTimer::create(Sprite::create("hp_green.png"));
    hpProgressTimer->setType(ProgressTimer::Type::BAR);
    hpProgressTimer->setMidpoint(Vec2(0,100));
    hpProgressTimer->setBarChangeRate(Vec2(1,0));
    hpProgressTimer->setPercentage(100);
    
    
    
    mpProgressTimer = ProgressTimer::create(Sprite::create("hp_yellow.png"));
    mpProgressTimer->setType(ProgressTimer::Type::BAR);
    mpProgressTimer->setPercentage(0);
    mpProgressTimer->setMidpoint(Vec2(0,100));
    mpProgressTimer->setBarChangeRate(Vec2(1,0));
    
    for(int i=0;i<2;++i) {
        effectHpProgressTimer[i] = ProgressTimer::create(Sprite::create("hp_green.png"));
        effectHpProgressTimer[i]->setType(ProgressTimer::Type::BAR);
        effectHpProgressTimer[i]->setPercentage(100);
        effectHpProgressTimer[i]->setMidpoint(Vec2(0,100));
        effectHpProgressTimer[i]->setBarChangeRate(Vec2(1,0));
        CC_SAFE_RETAIN(effectHpProgressTimer[i]);

    }
    
    effectHpProgressTimer[0]->setScaleX(1.5f);
    
    
    auto itemHp = MenuItemSprite::create(hpProgressTimer, hpProgressTimer);
    itemHp->setScale(1.3f);
    auto itemMp = MenuItemSprite::create(mpProgressTimer, mpProgressTimer);
    itemMp->setScale(1.3f);
    
    
   menu = Menu::create(itemHero,itemHp,itemMp,nullptr);
    menu->alignItemsVertically();
    
    panel->addChild(menu,1);
    menu->setPosition(menu->getParent()->getContentSize()/2);

    addChild(panel);
    
   l1 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
     l2 = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
    l1->setColor(Color3B::RED);
    l2->setColor(Color3B::RED);
    CC_SAFE_RETAIN(l1);
    CC_SAFE_RETAIN(l2);

    
}

void GameScene::initHeros(){
    /*
     coco init
     */
    
    coco = BaseSprite::create(std::string("pfca/Coco.fca"), std::string("Coco"));
    coco->playAnimation(BaseSprite::State::walk);
           coco->setPosition(0-_director->getVisibleSize().width/2,0);
    addChild(coco,1);
    auto move =MoveTo::create(8,Vec2(_director->getVisibleSize().width,coco->getPositionY()));
   
    move->setTag(moveAction);
    
    coco->runAction(move);
    
    /*
     boss init
     */
    boss =TreeBoss::create("pfca/AncientTreant.fca", "AncientTreant");
    boss->playAnimation(BaseSprite::State::sleep);
    
    boss->setPosition(_director->getWinSize().width/2.0f-boss->getContentSize().width-80,0.0f);
    addChild(boss,1);
    
   
    
}




