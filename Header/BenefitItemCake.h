#pragma once

#include "syati.h"
#include "revolution.h"
//#include "Game/LiveActor/FlashingCtrl.h"
    
    class BenefitItemCake : public LiveActor {
    public:
        BenefitItemCake(const char* pName);
        virtual void init(const JMapInfoIter& rIter);
        virtual void control();
        virtual bool receiveMessage(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    
        void collect();
        void appearAndMove();

        bool mIsCollected;
    };