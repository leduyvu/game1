
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer {
public:
    ~HelloWorld();
    HelloWorld();
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    // void initPhysics();
    // adds a new sprite at a given coordinate
    // void addNewSpriteAtPosition(cocos2d::CCPoint p);
    void remove(cocos2d::CCNode * node);
    void runLine(CCPoint location);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    //virtual void ccTouches(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    void setValue(CCLabelTTF *lb, int i);
    bool impact(CCSprite *sp, CCSprite *ft);
    void boomDown(CCSprite *boom);
    void fire(CCSprite *boom);
    void checkLocation(CCPoint location, CCPoint locationEnd);
    void menu();
    int getStep();
    
private:
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    cocos2d::CCSprite *people;
    cocos2d::CCSprite *footer;
    cocos2d::CCSprite *gun;
    cocos2d::CCSprite *duck;
    CCSprite *dan;
    int i = 0;
    CCArray *array,*arrayBoom,*plane;
    bool check = false;
    long point=100;
    int hearth =100;
    CCLabelTTF *points;
    CCLabelTTF *hearths;
    int step;
};

#endif // __HELLO_WORLD_H__
