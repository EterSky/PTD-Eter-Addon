#include "pt/Map/MorphSwitchCtrl.h"

MorphSwitchCtrl::MorphSwitchCtrl(const char* pName) : NameObj(pName) {
	mMorph = -1;
	mDeactivate = false;
}

void MorphSwitchCtrl::init(JMapInfoIter const& rIter) {
	MR::connectToSceneMapObjMovement(this);
	
	MR::getJMapInfoArg0NoInit(rIter, &mMorph); // Bitfield of morphs
	MR::getJMapInfoArg1NoInit(rIter, &mDeactivate); // Deactivate when no longer checked

	MR::registerDemoSimpleCastAll(this);

	mStageSwitchCtrl = MR::createStageSwitchCtrl(this, rIter);
}

void MorphSwitchCtrl::movement() {
	s32 check = 0;

	if (mMorph == -1) {
		check = MR::isPlayerElementModeNormal();
	}
	else if (mMorph == 0) {
		check = MR::isPlayerElementModeBee();
	}
	else if (mMorph == 1) {
		check = MR::isPlayerElementModeTeresa();
	}
	else if (mMorph == 2) {
		check = MR::isPlayerElementModeCloud();
	}
	/*else if (mMorph == 3) {
		check = MR::isPlayerElementModeDrill();
	}
	else if (mMorph == 4) {
		check = MR::isPlayerElementModeFoo();
	}*/
	else if (mMorph == 5) {
		check = MR::isPlayerElementModeFire();
	}
	else if (mMorph == 6) {
		check = MR::isPlayerElementModeIce();
	}
	else if (mMorph == 7) {
		check = MR::isPlayerElementModeInvincible();
	}
	else if (mMorph == 8) {
		check = MR::isPlayerElementModeRock();
	}
	else if (mMorph == 9) {
		check = MR::isPlayerElementModeHopper();
	}
	else if (mMorph == 10) {
		check = MR::isPlayerElementModeYoshi();
	}
	/*else if (mMorph == 11) {
		check = MR::isPlayerElementModeYoshiBalloon();
	}*/
	else if (mMorph == 12) {
		check = MR::isPlayerElementModeYoshiLight();
	}
	/*else if (mMorph == 13) {
		check = MR::isPlayerElementModeYoshiDash();
	}*/

	// Set switch when condition is met
	if (check) {
		mStageSwitchCtrl->onSwitchA();
	}
	if (!check && mDeactivate) {
		mStageSwitchCtrl->offSwitchA();
	}
}