#include "BaseSprite.h"


BaseSprite::BaseSprite()
:_isDead(false),
_elapseTime(0.0f)
{
	/*spConf->name = "";
	spConf->type= SPRITETYPE_1;
	spConf->attack = NULL;
	spConf->attackSpeed = NULL;
	spConf->power = NULL;*/
}

BaseSprite::~BaseSprite()
{
    

};

void BaseSprite::update(float dt,BaseSprite *target){
    _elapseTime += dt;
    
    
    if(_elapseTime>=_property.attackSpeed&&!isDead()){
        attack(target);
        _elapseTime = 0.0;
    }
}



bool BaseSprite::init(const std::string& fcaFile,const std::string& animateName)
{
    setArmatureNode(fcaFile,animateName);
    _armatureNode->setPosition(_director->getVisibleSize().width/2,_director->getVisibleSize().height/2);
    _property.attackSpeed = 2.0f;
    _property.range = 30;
    _property.maxLife = _property.curLife =  1000000;
    _property.power = 30;
    return true;
}

void BaseSprite::playAnimation(const BaseSprite::State &a,CallFunc* callBack)
{
        switch (a) {
        case BaseSprite::State::sleep:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[0]);
            
            break;
        case BaseSprite::State::attack1:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[6],-1.f,-1.f,1.f);
                
            break;
        case BaseSprite::State::attack2:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[7],-1.f,-1.f,1.f);
                          break;
        case BaseSprite::State::hurt:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[0]);
            break;
        case BaseSprite::State::dead:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[4],-1,-1,1);
            break;
        case BaseSprite::State::magic:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[5],-1.f,2.0f,1.f);
            break;
        case BaseSprite::State::walk:
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[1]);
               
            break;
            
        default:
            break;
    }
    
}

void BaseSprite::attack(BaseSprite *target)
{
    target->getProperty().curLife = target->getProperty().curLife - this->getProperty().power;
    
    target->setCurHurt(this->getProperty().power);
    _eventDispatcher->dispatchCustomEvent("hurt",(void*)target);
    if(CCRANDOM_0_1()<0.5f)
        playAnimation(BaseSprite::State::attack2);
    else
        playAnimation(BaseSprite::State::attack1);
    
}

void BaseSprite::magic(BaseSprite *target)
{
    target->getProperty().curLife = target->getProperty().curLife - this->getProperty().power*3;
    playAnimation(BaseSprite::State::magic);
}


void BaseSprite::setArmatureNode(const std::string& fcaFile, const std::string &armatureName)
{
    
        const Size& szWin = Director::getInstance()->getWinSize();
    
  //  delArmatureNode();
    
    bool isSucess = DBCCFactoryEx::getInstanceEx()->loadDotaFcaFile(fcaFile);
    assert(isSucess);
    _armatureNode = DBCCFactoryEx::getInstanceEx()->buildArmatureNode(armatureName);
    _armatureNode->setPosition(szWin.width/2, szWin.height/2);
    addChild(_armatureNode);
    
    _animationList = _armatureNode->getAnimation()->getAnimationList();
    
 
}

void BaseSprite::delArmatureNode()
{
    if (nullptr == _armatureNode)
        return;
    
    _armatureNode->removeFromParent();
    _armatureNode = nullptr;
    
//    if (_isHero)
//    {
//        DBCCFactoryEx::getInstanceEx()->removeTextureAtlas(_heroList[_curHero]);
//        DBCCFactoryEx::getInstanceEx()->removeDragonBonesData(_heroList[_curHero]);
//    }
//    else
//    {
//        DBCCFactoryEx::getInstanceEx()->removeTextureAtlas(_effectList[_curEffect]);
//        DBCCFactoryEx::getInstanceEx()->removeDragonBonesData(_effectList[_curEffect]);
//    }
    cocos2d::Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

bool EffSprite::init(const std::string &fcaFile, const std::string &animateName){
    if(BaseSprite::init(fcaFile, animateName))
        return true;
    return false;
}

void EffSprite::playAnimation(const BaseSprite::State &a,CallFunc* callBack)
{
    switch (a) {
        case BaseSprite::State::magic:{
            _armatureNode->getAnimation()->gotoAndPlay(_animationList[0],-1.0f,2.0f);
            auto move = MoveBy::create(2.0f,Vec2(Director::getInstance()->getWinSize().width-this->getContentSize().width/2,0));
             auto actionFade = FadeOut::create(1.0f);
            this->runAction(Sequence::create(move,actionFade,callBack,nullptr));
            break;
        }
        default:
            break;
    }
}

bool TreeBoss::init(const std::string &pcaFile, const std::string &animateName)
{
    if(!BaseSprite::init(pcaFile, animateName))
        return false;
    _property.curLife = _property.maxLife = 200;
    _property.power = 20;
    _property.attackSpeed = 2.8f;
    return true;
}

void TreeBoss::attack(BaseSprite *target)
{
    target->getProperty().curLife = target->getProperty().curLife - this->getProperty().power;
    
    target->setCurHurt(this->getProperty().power);
    _eventDispatcher->dispatchCustomEvent("hurt",(void*)target);

    if(CCRANDOM_0_1()<0.5f)
        playAnimation(BaseSprite::State::attack2);
    else
        playAnimation(BaseSprite::State::attack1);
    
}

void TreeBoss::playAnimation(const BaseSprite::State &a,CallFunc* callBack)
{
    switch (a) {
    case BaseSprite::State::sleep:
        _armatureNode->getAnimation()->gotoAndPlay(_animationList[0]);
        break;

    case BaseSprite::State::attack1:{
        _armatureNode->getAnimation()->gotoAndPlay(_animationList[1]);
        break;
    }
        
    case BaseSprite::State::attack2:
        _armatureNode->getAnimation()->gotoAndPlay(_animationList[3]);
        break;
        
    case BaseSprite::State::magic:
        _armatureNode->getAnimation()->gotoAndPlay(_animationList[2]);
        break;

    default:
        break;
    }
    
}

