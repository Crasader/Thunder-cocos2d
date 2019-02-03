#include "Player_Plane.h"

PlayerPlane * PlayerPlane::createWithProperty(PropertyManager * _property){
	PlayerPlane* playerPlane = new PlayerPlane();
	if (playerPlane && playerPlane->init(_property)) {
		playerPlane->autorelease();
		return playerPlane;
	}
	else {
		CC_SAFE_DELETE(playerPlane);
	}
	return nullptr;
}

bool PlayerPlane::init(PropertyManager * _property){
	this->property = _property;
	this->property->retain();
	
	//Ĭ�Ϸ��ж���
	ArmatureDataManager::getInstance()->addArmatureFileInfo(property->getDataName());
	armature = Armature::create(property->getArmatureName());
	armature->getAnimation()->play("default");
	this->addChild(armature);

	//����Ĭ��λ��
	this->setPosition(property->getDefaultPosition());


	//��ʱ�Զ����
	this->schedule(schedule_selector(PlayerPlane::shooting), property->getShootingInterval());
	return true;
}


void PlayerPlane::shooting(float dt){
	log("shooting");
}

