#include "BaseFSM.h"

BaseFSM * BaseFSM::createFSM(PlayerPlane * baseRole){
	BaseFSM *baseFSM = new BaseFSM();
	if (baseFSM&& baseFSM->init(baseRole)) {
		baseFSM->autorelease();
	}
	else {
		CC_SAFE_DELETE(baseFSM);
	}
	return baseFSM;
}

bool BaseFSM::init(PlayerPlane * baseRole){
	this->baseRole = baseRole;
	log("%f", this->baseRole->getPosition().x);
	return true;
}


void BaseFSM::switchMoveState(tagDirection direction, float radDirection,float dt){
	switch (direction)
	{
	case rocker_stay:
		changeToDefault();
		break;
	default:
		changeToMove(radDirection, dt);
		break;
	}
}


//切换到移动状态
void BaseFSM::changeToMove(float radDirection, float dt){
	if (baseRole->getState() != ROLE_MOVE && baseRole->getState() != ROLE_DEAD) {
		baseRole->setState(ROLE_MOVE);
	}

	//位移公式 V0*t+0.5*t*t
	float distance = baseRole->property->getVelocity()*dt + 0.5*pow(dt, 2)*baseRole->property->getAcceleration();
	float dx = distance*cos(radDirection);
	float dy = distance*sin(radDirection);


	auto position = baseRole->getPosition() + Vec2(dx, dy);
	auto screen = Director::getInstance()->getVisibleSize();
	//在屏幕内则更新
	if (position.x <= screen.width &&position.x>=0 && position.y <= screen.height &&position.y>=0) {
		baseRole->setPosition(Vec2(position));
	}
}

//切换到默认飞行状态
void BaseFSM::changeToDefault(){
	if (baseRole->getState() != ROLE_DEFAULT && baseRole->getState() != ROLE_DEAD) {
		baseRole->setState(ROLE_DEFAULT);
		//默认动画帧
		baseRole->stopAllActions();
		baseRole->getArmature()->getAnimation()->play("default");
	}
}

void BaseFSM::changeToAttack(){
}



//爆炸动画
void BaseFSM::changeToDead(){
}


