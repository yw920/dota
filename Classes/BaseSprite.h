#ifndef _BASESPRITE_
#define _BASESPRITE_

#include "cocos2d.h"
#include "Config.h"
#include "DragonBonesHeaders.h"
#include "Utils.h"
#include "DotaAnimParser/DBCCFactoryEx.h"
#include "DBCCRenderHeaders.h"
#include <vector>
#include <string>

using namespace cocos2d;
#define CREATE_FUNC_BASESPRITE(__TYPE__) \
static __TYPE__* create(const std::string& fcaFile,const std::string& animateName) \
{ \
__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
if (pRet && pRet->init(fcaFile,animateName)) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}


struct sp_property{
    float maxLife;
    float curLife;
    int range;
    float attackSpeed;
    int power;
    int defend;
    int magicCoolDownSpeed;
};


class BaseSprite : public DBCCArmatureNode
{
public:
    enum class State{
        sleep=1,
        walk,
        attack1,
        attack2,
        hurt,
        dead,
        magic
    };
    
    void setDead(){_isDead = true;}
    bool isDead(){return _isDead;}
     virtual void update(float dt,BaseSprite* target);
    
    DBCCArmatureNode* getArmatureNode(){return _armatureNode;}
    
	BaseSprite();
	~BaseSprite();
    
    virtual void attack(BaseSprite* target);
    virtual void magic(BaseSprite* target);
    
    virtual bool init(const std::string& pcaFile,const std::string& animateName);
    
//    inline static BaseSprite* create(const std::string& fcaFile,const std::string& animateName)
//    {
//        BaseSprite *pRet = new(std::nothrow) BaseSprite();
//        if (pRet && pRet->init(fcaFile,animateName))
//        {
//            pRet->autorelease();
//            return pRet;
//        }
//        else
//        {
//            delete pRet;
//            pRet = NULL;
//            return NULL;
//        }
//    }
    
    
    
    CREATE_FUNC_BASESPRITE(BaseSprite);
    
    virtual void playAnimation(const State& a,CallFunc* callBack=nullptr);
    
    sp_property& getProperty(){return _property;}
    
private:
    
    
    
    void setArmatureNode(const std::string& fcaFile, const std::string &armatureName);
    
     void delArmatureNode();
    
    CC_SYNTHESIZE(float,_curHurt, CurHurt);
	
protected:

   /**
    set the Animation
    **/
    
    DBCCArmatureNode* _armatureNode;
    std::vector<std::string>_animationList;
    
    sp_property _property;
    
    bool _isDead;
    
    float _elapseTime;
    
     //  to do per seconds
    
    
   
  
   
};

class EffSprite:public BaseSprite{
public:
    
    virtual bool init(const std::string& pcaFile,const std::string& animateName);
    CREATE_FUNC_BASESPRITE(EffSprite);
 virtual void playAnimation(const State& a,CallFunc* callBack=nullptr)override;
};

class TreeBoss:public BaseSprite{
public:
    virtual bool init(const std::string& pcaFile,const std::string& animateName)override;
    CREATE_FUNC_BASESPRITE(TreeBoss);
    virtual void playAnimation(const State& a,CallFunc* callBack=nullptr)override;
    virtual void attack(BaseSprite* target)override;
};

#endif