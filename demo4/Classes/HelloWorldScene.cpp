
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "sstream"
//#include <string.h>

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
    arrayBoom = new CCArray();
    array = new CCArray();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    // init physics

    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("blocks.png", 100);
    m_pSpriteTexture = parent->getTexture();
    addChild(parent, 0, kTagParentNode);
    //Create CCNode :
    CCSprite *nen = CCSprite::create("nen2.jpeg");
    people = CCSprite::create("canh.jpeg");
    footer = CCSprite::create("maybay.jpeg");
    gun = CCSprite::create("sung.jpg");
    duck = CCSprite::create("icon.jpeg");
    ostringstream ss;
    ss << hearth;
    ostringstream ss1;
    ss1 << point;
    points = CCLabelTTF::create(ss1.str().c_str(), "ico",16);
    hearths= CCLabelTTF::create(ss.str().c_str(), "ico",16);
    CCLabelTTF *label = CCLabelTTF::create("Framgia Game", "Marker Felt", 30);
    CCLabelTTF *pt = CCLabelTTF::create("point", "Time New Roman",16);
    CCLabelTTF *hth = CCLabelTTF::create("heart", "Time New Roman", 16);
    //set Location
    footer->setPosition(ccp(s.width/2 + 200, s.height/2+50));
    people->setPosition(ccp(s.width/2, s.height/2));
    gun->setPosition(ccp(s.width/2, 10));
    points->setPosition(ccp(70,s.height -50));
    hearths->setPosition(ccp(70,s.height -30));
    duck->setPosition(ccp(s.width/2, s.height/2+100));
    nen->setPosition(ccp(s.width/2, s.height/2));
    pt->setPosition(ccp(30, s.height-50));
    hth->setPosition(ccp(30, s.height-30));
    // add into Scene
    addChild(duck,4);
    addChild(footer,4);
    addChild(gun,4);
    addChild(points,5);
    addChild(hearths,5);
    addChild(pt,5);
    addChild(hth,5);
    addChild(label, 0);
    label->setColor(ccc3(0,0,255));
    label->setPosition(ccp( s.width/2, s.height-30));
    this->scheduleUpdate();
}
void HelloWorld::update(float dt)
{
    CCObject *t;
    CCObject *j;
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    //check game-over?
    if (hearth<=0 || point<0)
    {
        CCLabelTTF *gameover = CCLabelTTF::create("GAME OVER", "Time New Roman", 46);
        gameover->setPosition(ccp(s.width/2,s.height/2));
        addChild(gameover,7);
        return ;
    }
    //check and handler impact
    CCARRAY_FOREACH(array, t)
    {
        CCSprite *sp = (CCSprite*)t;
        if(impact(sp,footer))
        {   point = point +20;
            setValue(points,point);
            int x = (arc4random()%10)*100;
            if (x <s.width && x > 0)
                footer->setPosition(ccp(x,200));
            else
              footer->setPosition(ccp(350,200));
            //break;
        }
        
    }
    CCARRAY_FOREACH(arrayBoom, j)
    {   
        CCSprite *sp1 = (CCSprite*)j;
        CCARRAY_FOREACH(array, t)
        {
            CCSprite *sp = (CCSprite*)t;
            if (sp1 != NULL && sp != NULL) {
                //printf("%f  %f",sp->getPosition().x,sp->getPosition().y);
                if(impact(sp, sp1))
                {
                    point = point + 5;
                    setValue(points, point);
                    //impact(sp, sp1);
                    this->removeChild(sp1);
                    arrayBoom->removeObject(sp1);
                    point = point + 5;
                    //delete sp1;
                    //delete sp1;
                    return;
                }
            }
            
        }
        if (sp1 != NULL)
            fire(sp1); //handler boom 
        
    }
    //create boom
    if (i == 50)
    {
        CCSprite *boom = CCSprite::create("bom.jpg");
        boom->setPosition(footer->getPosition());
        addChild(boom,4);
        boomDown(boom);
        arrayBoom->addObject(boom);
        i=0;
    }
    // footer running
    while (i<50)
    {
        CCPoint local = footer->getPosition();
        if (local.x < 50)

            check=true;
        if (local.x >450)
           check=false;
        if(check)
        {
            footer->setPosition(ccp(footer->getPosition().x + 10 * dt * 5 ,footer->getPosition().y)) ;
        }
        else if (local.x<400)
            footer->setPosition(ccp(footer->getPosition().x - 10 * dt * 5,footer->getPosition().y)) ;
        else
            footer->setPosition(ccp(footer->getPosition().x - 10 * dt * 5,footer->getPosition().y)) ;
        duck->setPosition(ccp(duck->getPosition().x + 10 * dt * 5,duck->getPosition().y)) ;
        //check = false;
        //break;
        i++;
        break;
    }
}
//set String for CClabel with a integer
void HelloWorld::setValue(CCLabelTTF *lb, int i)
{
    ostringstream ss;
    ss << i;
    lb->setString(ss.str().c_str());
    
}
//destroy function
HelloWorld::~HelloWorld()
{
    delete world;
    world = NULL;
    removeAllChildren();
}
// Create scene
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

// handler event
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

void HelloWorld::checkLocation(CCPoint location, CCPoint locationEnd)
{
    float x = ccpDistanceSQ(location,gun->getPosition());
    if (x<=30)
    {
        CCMoveTo *move = CCMoveTo::create(2, locationEnd);
        gun->runAction(move);
        delete move;
    }
    
}
// remove a Node
void HelloWorld::remove(cocos2d::CCNode *node)
{
    CCSprite * sp = (CCSprite*)node;
    array->removeObject(node);
    this->removeChild(sp);
    
}
//check and handler impact
bool HelloWorld::impact(CCSprite *sp, CCSprite *ft)
{
    float x;
    try {
        x = ccpDistanceSQ(sp->getPosition(),ft->getPosition());
    } catch (exception c) {
        x= 300;
    }
    //if impact
    if (x<300)
    {
        //this->remove(ft);
        CCPoint pos = ft->getPosition();
        //footer->setPosition(ccp((arc4random()%10)*100,200));
        CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("SmallSun.plist");
        emitter1->setStartColor(ccc4f(0,0.3,0.5,1));
        emitter1->setBlendAdditive(false);
        emitter1->setDuration(1);
        emitter1->setPosition(pos);
        this->addChild(emitter1);
        this->removeChild(sp);
        this->array->removeObject(sp);
        return true;
    }
    else return false;
}
//boom
void HelloWorld::boomDown(CCSprite *boom){
    CCMoveTo *move = CCMoveTo::create(5, ccp(boom->getPosition().x,0));
    boom->runAction(move);
}
//boom fire when y < 20
void  HelloWorld::fire(CCSprite *boom)
{
    if(boom->getPosition().y<=20)
    {
        this->removeChild(boom);
        CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("SmallSun.plist");
        emitter1->setStartColor(ccc4f(0,0.3,0.5,1));
        emitter1->setBlendAdditive(false);
        emitter1->setDuration(1);
        emitter1->setPosition(boom->getPosition());
        this->addChild(emitter1);
        arrayBoom->removeObject(boom);
        hearth = hearth - 20;
        setValue(hearths, hearth);
        point = point -10 ;
        setValue(points, point);
    }
    
}
//gun -shooting
void HelloWorld::runLine(CCPoint location){
    CCSprite *dan1 = CCSprite::create("Projectile.png");
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    dan1->setPosition(ccp(s.width/2, 10));
    long x0 = location.x;
    long y0 = location.y;
    long x1 = (int)s.width/2;
    long y1 = 10 ;
    long y_max = s.height;
    long x =(x0 - x1) * (y_max - y0)/(y0-y1) +x0 ;
    addChild(dan1,4);
    CCMoveTo *move = CCMoveTo::create(1, ccp(x,y_max));
    array->addObject(dan1);
    CCCallFuncN * remove1 = CCCallFuncN::create(this, callfuncN_selector(HelloWorld::remove));
    CCSequence *sq = CCSequence::createWithTwoActions(move,remove1);
    dan1->runAction(sq);

}