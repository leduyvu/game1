#include "Singler.h"

using namespace cocos2d;

Singler* Singler::instance = NULL;

Singler::Singler(int t,int s) {
    point = t;
    step = s;
}
int Singler::getPoint()
{
    return this->point;
}
void Singler::setPoint(int t)
{
    this->point = t;
    this->~Singler();
}
int Singler::getStep()
{
    return this->step;
    
}
void Singler::setStep(int i)
{
    this->step=i;
    this->~Singler();
}
Singler* Singler::sharedObject() {
    if (instance==NULL) {
        instance = new Singler(100,1);
    }
    return instance;
}