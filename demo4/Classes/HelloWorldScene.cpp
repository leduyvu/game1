
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define PTM_RATIO 32
USING_NS_CC;
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
    people = CCSprite::create("canh.jpeg");
    footer = CCSprite::create("maybay.jpeg");
    gun = CCSprite::create("sung.jpg");
    duck = CCSprite::create("icon.jpeg");
    //dan = CCSprite::create("Projectile.png");
    footer->setPosition(ccp(s.width/2 + 200, s.height/2+50));
    people->setPosition(ccp(s.width/2, s.height/2));
    gun->setPosition(ccp(s.width/2, 10));
    //dan->setPosition(ccp(s.width/2, 10));
    duck->setPosition(ccp(s.width/2, s.height/2+100));
    
    addChild(duck,4);
    CCLayerColor *lay = CCLayerColor::create();
    lay->setColor(ccc3(0,0,0));
    
    addChild(lay,2);
    addChild(footer,4);
    addChild(gun,4);
    //addChild(dan,3);
    
    

    CCLabelTTF *label = CCLabelTTF::create("Tap screen", "Marker Felt", 32);
    addChild(label, 0);
    label->setColor(ccc3(0,0,255));
    label->setPosition(ccp( s.width/2, s.height-50));
    //run();
    this->scheduleUpdate();
}
void HelloWorld::update(float dt)
{
    if (i == 250)
    {
        CCSprite *boom = CCSprite::create("bom.jpg");
        boom->setPosition(footer->getPosition());
        addChild(boom,4);
        boomDown(boom);
        fire(boom);
       i=0;
    }
    
    while (i<250)
    {
        CCPoint local = footer->getPosition();
        if(local.x <10)
         footer->setPosition(ccp(footer->getPosition().x + 10 * dt ,footer->getPosition().y)) ;
        else if (local.x<400)
            footer->setPosition(ccp(footer->getPosition().x - 10 * dt ,footer->getPosition().y)) ;
        else
            footer->setPosition(ccp(footer->getPosition().x - 10 * dt ,footer->getPosition().y)) ;
        duck->setPosition(ccp(duck->getPosition().x + 10 * dt ,duck->getPosition().y)) ;
        //break;
        i++;
        break;
    }
    CCObject *i;
   // array->addObject(footer);
    CCARRAY_FOREACH(array, i)
    {
        CCSprite *sp = (CCSprite*)i;
        impact(sp);
    }
    //run();

}
void HelloWorld::run()
{
    CCMoveTo *move1 = CCMoveTo::create(5, ccp(0, 400));
    CCMoveTo *move2 = CCMoveTo::create(5, ccp(300, 300));
    if (duck->getPosition().x == 0)
        duck->runAction(move1);
    else if (duck->getPosition().x == 300)
        duck->runAction(move2);
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
    //layer->setColor(ccc3(255,255,255));
    scene->addChild(layer);
    layer->release();
   // gun->setPosition(ccp(200,200));

    return scene;
}


void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
    CCSetIterator it;
    CCTouch* touch;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        touch = (CCTouch*)(*it);
        
        if(!touch)
            break;
        
        CCPoint location = touch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        runLine(location);
        
    }
}

void HelloWorld::remove(cocos2d::CCNode *node)
{
    CCSprite * sp = (CCSprite*)node;
    array->removeObject(node);
    this->removeChild(sp);
    
}
void HelloWorld::impact(CCSprite *sp)
{
    //float x = ccpDistance(ccp(200,200),ccp(100,100));
    
    float x = ccpDistanceSQ(sp->getPosition(),footer->getPosition());
    if (x<300)
    {
        remove(sp);
        CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("SmallSun.plist");
        emitter1->setStartColor(ccc4f(0,0.3,0.5,1));
        emitter1->setBlendAdditive(false);
        emitter1->setDuration(1);
        emitter1->setPosition(footer->getPosition());
        this->addChild(emitter1);
        //CCSize s = CCDirector::sharedDirector()->getWinSize();
        footer->setPosition(ccp((arc4random()%10)+300,200));
        
    }
}
void HelloWorld::boomDown(CCSprite *boom){
    CCMoveTo *move = CCMoveTo::create(2, ccp(boom->getPosition().x,0));
    boom->runAction(move);
                                      
}
void  HelloWorld::fire(CCSprite *boom)
{
    if(boom->getPosition().y==0)
    {
        CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("SmallSun.plist");
        emitter1->setStartColor(ccc4f(0,0.3,0.5,1));
        emitter1->setBlendAdditive(false);
        emitter1->setDuration(1);
        emitter1->setPosition(boom->getPosition());
        this->addChild(emitter1);
        remove(boom);
    }
    
}
void HelloWorld::runLine(CCPoint location){
    CCSprite *dan1 = CCSprite::create("Projectile.png");
    array = new CCArray();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    dan1->setPosition(ccp(s.width/2, 10));
    int x0 = location.x;
    int y0 = location.y;
    int x1 = (int)s.width/2;
    int y1 = 10 ;
    int y_max = s.height;
    int x =(x0 - x1) * (y_max - y0)/(y0-y1) +x0 ;
    addChild(dan1,4);
    CCMoveTo *move = CCMoveTo::create(1, ccp(x,y_max));
    array->addObject(dan1);
    CCCallFuncN * remove1 = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::remove));
    CCSequence *sq = CCSequence::createWithTwoActions(move,remove1);
    //dan1->runAction(sq);
    //CCSequence *sq2 = CCSequence::createWithTwoActions(sq , remove1);
    dan1->runAction(sq);
    //this->addChild(dan1,4);

}