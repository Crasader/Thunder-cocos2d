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


//�л����ƶ�״̬
void BaseFSM::changeToMove(float radDirection, float dt){
	if (baseRole->getState() != ROLE_MOVE && baseRole->getState() != ROLE_DEAD) {
		baseRole->setState(ROLE_MOVE);
	}

	//λ�ƹ�ʽ V0*t+0.5*t*t
	float distance = baseRole->property->getVelocity()*dt + 0.5*pow(dt, 2)*baseRole->property->getAcceleration();
	float dx = distance*cos(radDirection);
	float dy = distance*sin(radDirection);


	auto position = baseRole->getPosition() + Vec2(dx, dy);
	auto screen = Director::getInstance()->getVisibleSize();
	//����Ļ�������
	if (position.x <= screen.width &&position.x>=0 && position.y <= screen.height &&position.y>=0) {
		baseRole->setPosition(Vec2(position));
	}
}

//�л���Ĭ�Ϸ���״̬
void BaseFSM::changeToDefault(){
	if (baseRole->getState() != ROLE_DEFAULT && baseRole->getState() != ROLE_DEAD) {
		baseRole->setState(ROLE_DEFAULT);
		//Ĭ�϶���֡
		baseRole->stopAllActions();
		baseRole->getArmature()->getAnimation()->play("default");
	}
}

void BaseFSM::changeToAttack(){
}



//��ը����
void BaseFSM::changeToDead(){
}


