//
//  singler.h
//  demo4
//
//  Created by macbook_006 on 13/06/11.
//
//

#ifndef __SINGLER_H__
#define __SINGLER_H__
#include "cocos2d.h"
class Singler {
private:
    int point;
    int step;
    Singler(int t,int step);
    static Singler* instance;
    
public:
    static Singler* sharedObject();
    int getPoint();
    void setPoint(int t);
    int getStep();
    void setStep(int i);
};

#endif