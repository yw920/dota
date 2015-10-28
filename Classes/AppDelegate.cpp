#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameScene.h"
#include "LoadScene.h"
#include "OverScene.h"
#include "BaseSprite.h"
#include "TestScene.hpp"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
		glview->setFrameSize(600, 360);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	glview->setDesignResolutionSize(800, 480, kResolutionExactFit);
    // create a scene. it's an autorelease object
   // auto scene = HelloWorld::createScene();
	//auto scene = GameScene::createScene();
    
    FileUtils::getInstance()->addSearchPath("/Users/yw/Desktop/MyCppGame/Resources");
    
    auto scene = GameScene::createScene();
	//auto scene = OverScene::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
