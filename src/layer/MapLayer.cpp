#include "MapLayer.h"
#include <exception>

MapLayer * MapLayer::createWithFile(const char * fileName){
	MapLayer* mapLayer = new MapLayer();
	if (mapLayer && mapLayer->init(fileName)) {
		mapLayer->autorelease();
		return mapLayer;
	}
	else {
		CC_SAFE_DELETE(mapLayer);
	}
	return nullptr;
}

bool MapLayer::init(const char * fileName){
	try {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		//Ĭ���Ӵ���
		rollingRect.width = visibleSize.width;
		rollingRect.height = 100;

		//����1
		bg1 = Sprite::create(fileName);
		bg1->setAnchorPoint(Vec2::ZERO);
		bg1->setPosition(origin);
		float scaleX = rollingRect.width / bg1->getContentSize().width;
		bg1->setScaleX(scaleX);
		this->addChild(bg1);

		//����2  �Ϸ�
		bg2 = Sprite::create(fileName);
		bg2->setAnchorPoint(Vec2::ZERO);
		bg2->setPosition(origin.x, origin.y + bg1->getContentSize().height);
		bg2->setScaleX(scaleX);
		this->addChild(bg2);

		//�ٽ��
		this->peakPositionY = -bg1->getContentSize().height;
		//Ĭ���ٶ�
		this->speed = 100.0f;
		//Ĭ�ϼ��ٶ�
		this->acceleration = 0.0f;

		startRolling();
		return true;
	}
	catch(std::exception& e){
		log("%s", e.what());
		return false;
	}
}

//����  �����ٶ�
void MapLayer::update(float dt){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float distanceY = dt*speed + 0.5*acceleration*pow(dt, 2);
	bg1->setPositionY(bg1->getPositionY() - distanceY);
	bg2->setPositionY(bg2->getPositionY() - distanceY);

	if (bg1->getPositionY() < peakPositionY) {
		bg1->setPositionY(0);
		bg2->setPositionY(-peakPositionY);
	}
}



//��ʼ����
void MapLayer::startRolling(){
	this->scheduleUpdate();
}


//ֹͣ����
void MapLayer::stopRolling(){
	this->unscheduleUpdate();
}
