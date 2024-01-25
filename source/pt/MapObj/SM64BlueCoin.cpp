#include "pt/MapObj/SM64BlueCoin.h"
#include "Game/MapObj/CoinHolder.h"

SM64BlueCoin::SM64BlueCoin(const char* pName): Coin(pName) {
    mIsCollected = false;
    mIsInAirBubble = false; // Obj_arg0
    mUseConnection = false; // Obj_arg1

    MR::createCoinRotater();
    MR::createCoinHolder();
    MR::addToCoinHolder(this, this);
}

void SM64BlueCoin::init(const JMapInfoIter& rIter) {
    MR::processInitFunction(this, rIter, false);
    MR::calcGravity(this);

    MR::getJMapInfoArg0NoInit(rIter, &mIsInAirBubble); // Use AirBubble?
    MR::getJMapInfoArg1NoInit(rIter, &mUseConnection); // Use MapObjConnection?
    
    initNerve(&NrvCoin::CoinNrvFix::sInstance, 0);

    initHitSensor(1);
    MR::addHitSensor(this, "SM64BlueCoin", 0x4A, 4, 55.0f, TVec3f(0.0f, 70.0f, 0.0f));

    mFlashingCtrl = new FlashingCtrl(this, 1);

    mConnector = new MapObjConnector(this);
    mConnector->attach(mTranslation);

    MR::initShadowVolumeSphere(this, 50.0f);
    MR::setShadowDropPositionPtr(this, 0, &mShadowDropPos);
    MR::setShadowDropLength(this, 0, 1000.0f);

    MR::connectToSceneItem(this);

    makeActorAppeared();

    // Can't use ActorInfo for this one...
    MR::useStageSwitchSyncAppear(this, rIter);
}

void SM64BlueCoin::initAfterPlacement() {
    if (!mUseConnection)
        MR::offBind(this);

    if (MR::isValidSwitchB(this)) {
        MR::hideModel(this);
        MR::invalidateHitSensors(this);
    }

    initAirBubble();
}

void SM64BlueCoin::control() {
    if (mIsCollected) {
        mVelocity = TVec3f(0, 0, 0);
    }
}

void SM64BlueCoin::calcAndSetBaseMtx() {
    if (mUseConnection) {
        mConnector->connect();
        mConnector->attachToUnder();
    }

    Coin::calcAndSetBaseMtx();
}

void SM64BlueCoin::initAirBubble() {
    if (mIsInAirBubble) {
        mAirBubble = MR::createPartsModelNoSilhouettedMapObj(this, "空気アワ", "AirBubble", 0);
        mAirBubble->initFixedPosition(TVec3f(0.0f, 70.0f, 0.0f), TVec3f(0.0f, 0.0f, 0.0f), 0);
        MR::startAction(mAirBubble, "Move");
        MR::setSensorRadius(this, "SM64BlueCoin", 100.0f);
    }
}

void SM64BlueCoin::appearAndMove() {
    appearMove(mTranslation, TVec3f(0.0f, 0.0f, 0.0f), 0x7FFFFFFF, 0);
    setCannotTime(300);
    MR::validateHitSensors(this);
}

bool SM64BlueCoin::receiveMessage(u32 msg, HitSensor* pSender, HitSensor* pReciver) {
    if (MR::isMsgItemGet(msg) && !mIsCollected)
        collect();
        return false;
}

void SM64BlueCoin::collect() {
    if (MR::isValidSwitchA(this)) {
        MR::onSwitchA(this);
    }

    mIsCollected = true;
    if (mIsInAirBubble && !mUseConnection) {
        MR::emitEffect(mAirBubble, "RecoveryBubbleBreak");
        MR::incPlayerOxygen(8);
        mAirBubble->kill();
    }
    MR::startSystemSE("SE_SY_PURPLE_COIN", -1, -1);
    MR::isIntervalStep(this, 10);
    GameSequenceFunction::getPlayResultInStageHolder()->addCoinNum(5);
    MR::invalidateHitSensors(this);
    MR::invalidateShadowAll(this);
    MR::emitEffect(this, "SM64BlueCoinGet");
    MR::incPlayerLife(2);
    MR::hideModel(this);
}