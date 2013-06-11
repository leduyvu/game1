//
//  Menu.cpp
//  demo4
//
//  Created by macbook_006 on 13/06/11.
//
//

#include "Menu.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Singler.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32
USING_NS_CC;
enum {
    kTagParentNode = 1,
};

Menu::Menu()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    //Create CCNode :
    CCSprite *nen = CCSprite::create("e.png");
    nen->setPosition(ccp(s.width/2,s.height /2));
    addChild(nen,1);
    CCLabelTTF *play = CCLabelTTF::create("Play Step 1", "Time New Roman", 30);
    play->setColor(ccc3(255, 0, 0));
    //play->setPosition(ccp(s.width/2, s.height/2 + 70));
    CCLabelTTF *exit = CCLabelTTF::create("Exit", "Time New Roman", 30);
    exit->setColor(ccc3(255, 0, 0));
    //exit->setPosition(ccp(s.width/2, s.height/2));
    //CCMenuItemSprite;
    //CCMenuItem
    //CCMenuItemLabel::c
    CCMenuItemLabel *mplay = CCMenuItemLabel::create(play, this, menu_selector(Menu::play));
    mplay->setPosition(ccp(0, 80));
    
    CCLabelTTF *next = CCLabelTTF::create("Next Step", "Time New Roman", 30);
    exit->setColor(ccc3(255, 0, 0));
    CCMenuItemLabel *mexit = CCMenuItemLabel::create(exit, this, menu_selector(Menu::quit));
    mexit->setPosition(ccp(0,0));
    
    CCMenuItemLabel *mnext = CCMenuItemLabel::create(next, this, menu_selector(Menu::next));
    mnext->setPosition(ccp(0, 40));
    mnext->setColor(ccc3(255, 0, 0));
    
    //if()
    CCMenu *m = CCMenu::create(mplay,mexit,mnext,NULL);
    //CCMenu::cre
    m->setPosition(ccp(s.width/2, s.height/2));
    this->addChild(m,4);
    

}

Menu::~Menu()
{
    this->removeAllChildren();
}
// Create scene
CCScene* Menu::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    // add layer as a child to scene
    CCLayer* layer = new Menu();
    //layer->setColor(ccc3(255,255,255));
    scene->addChild(layer);
    layer->release();
    // gun->setPosition(ccp(200,200));
    return scene;
}
void Menu::play()
{
    Singler::sharedObject()->setStep(1);
    Singler::sharedObject()->setPoint(100);
    CCScene *newScene=HelloWorld::scene();
    //Singler *c = Singler::sharedObject();
    //c->setPoint(200);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,newScene));
    
}
void Menu::quit()
{
    Singler::sharedObject()->setStep(1);
    Singler::sharedObject()->setPoint(100);
    //Singler::sharedObject()->~Singler();
    CCDirector::sharedDirector()->end();
    
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif

}
void Menu::next()
{
    //Singler::sharedObject()->setPoint(100);
    CCScene *newScene=HelloWorld::scene();
    int k = Singler::sharedObject()->getStep() + 1;
    printf("dfsfdfd: %d",k);
    Singler::sharedObject()->setStep(k);
    printf("qqwqwqwqw: %d", Singler::sharedObject()->getStep());
    //Singler *c = Singler::sharedObject();
    //c->setPoint(200);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,newScene));
    
}