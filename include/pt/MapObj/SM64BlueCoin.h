#pragma once

#include "syati.h"
#include "revolution.h"
#include "Game/MapObj/Coin.h"
#include "Game/LiveActor/FlashingCtrl.h"
    
    class SM64BlueCoin : public Coin {
    public:
        SM64BlueCoin(const char* pName);
        virtual void init(const JMapInfoIter& rIter);
        virtual void initAfterPlacement();
        virtual void control();
        virtual void calcAndSetBaseMtx();
        virtual bool receiveMessage(u32 msg, HitSensor* pSender, HitSensor* pReceiver);
    
        void collect();
        void appearAndMove();
        void initAirBubble();
    
        bool mIsInAirBubble; // Obj_arg0
        bool mUseConnection; // Obj_arg1
        bool mIsCollected;
    };