#include "pt/MapObj/BenefitItemCake.h"

BenefitItemCake::BenefitItemCake(const char* pName): LiveActor(pName) {
    mIsCollected = false;
}

void BenefitItemCake::init(const JMapInfoIter& rIter) {
    MR::processInitFunction(this, rIter, false);
    MR::calcGravity(this);
    
//    initNerve(&NrvBenefitItemObj::HostTypeNrvWait::sInstance);

    initHitSensor(1);
    MR::addHitSensor(this, "BenefitItemCake", 0x4A, 4, 55.0f, TVec3f(0.0f, 70.0f, 0.0f));

//    mFlashingCtrl = new FlashingCtrl(this, 1);

    makeActorAppeared();

    // Can't use ActorInfo for this one...
    MR::useStageSwitchSyncAppear(this, rIter);
}

void BenefitItemCake::control() {
    if (mIsCollected) {
        mVelocity = TVec3f(0, 0, 0);
    }
}

void BenefitItemCake::appearAndMove() {
//    appearMove(mTranslation, TVec3f(0.0f, 0.0f, 0.0f), 0x7FFFFFFF, 0);
//    setCannotTime(300);
    MR::validateHitSensors(this);
}

bool BenefitItemCake::receiveMessage(u32 msg, HitSensor* pSender, HitSensor* pReciver) {
    if (MR::isMsgItemGet(msg) && !mIsCollected)
        collect();
        return false;
}

void BenefitItemCake::collect() {
    mIsCollected = true;
    MR::startSystemSE("SE_SY_5UP", -1, -1);
    MR::getGameSceneLayoutHolder()->requestOneUp(99);
    GameDataFunction::addPlayerLeft(99);
    MR::invalidateHitSensors(this);
    MR::invalidateShadowAll(this);
    MR::emitEffect(this, "CakeGet");
    MR::hideModel(this);
}