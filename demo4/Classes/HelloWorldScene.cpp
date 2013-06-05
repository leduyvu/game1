
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32

enum {
    kTagParentNode = 1,
};

HelloWorld::HelloWorld()
{
    setTouchEnabled( true );
    setAccelerometerEnabled( true );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    // init physics

    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("blocks.png", 100);
    m_pSpriteTexture = parent->getTexture();

    addChild(parent, 0, kTagParentNode);
    //CCSprite* pSprite = CCSprite::create("CloseNormal.png");
    people = CCSprite::create("aoe.jpg");
    footer = CCSprite::create("maybay.jpeg");
    gun = CCSprite::create("sung.jpg");
    duck = CCSprite::create("icon.jpeg");
    footer->setPosition(ccp(s.width/2 + 200, s.height/2+50));
    people->setPosition(ccp(s.width/2, s.height/2));
    gun->setPosition(ccp(s.width/2, 10));
    duck->setPosition(ccp(s.width/2, s.height/2+100));
    
    addChild(people,2);
    addChild(footer,4);
    addChild(gun,4);
    addChild(duck,4);

    CCLabelTTF *label = CCLabelTTF::create("Tap screen", "Marker Felt", 32);
    addChild(label, 0);
    label->setColor(ccc3(0,0,255));
    label->setPosition(ccp( s.width/2, s.height-50));
    
    this->scheduleUpdate();
}
void HelloWorld::update(float dt)
{
    if (i == 250)
    {
        CCSprite *boom = CCSprite::create("bom.jpg");
        boom->setPosition(footer->getPosition());
        addChild(boom,4);
       i=0;
    }
    while (i<250)
    {
        footer->setPosition(ccp(footer->getPosition().x - 10 * dt ,footer->getPosition().y)) ;
        duck->setPosition(ccp(duck->getPosition().x + 10 * dt ,duck->getPosition().y)) ;
        //break;
        i++;
        break;
    }
    

}
HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
    //cpSpaceFree( m_pSpace );
    //delete m_debugDraw;
}


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
