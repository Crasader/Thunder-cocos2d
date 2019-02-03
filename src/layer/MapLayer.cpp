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

		//默认视窗口
		rollingRect.width = visibleSize.width;
		rollingRect.height = 100;

		//背景1
		bg1 = Sprite::create(fileName);
		bg1->setAnchorPoint(Vec2::ZERO);
		bg1->setPosition(origin);
		float scaleX = rollingRect.width / bg1->getContentSize().width;
		bg1->setScaleX(scaleX);
		this->addChild(bg1);

		//背景2  上方
		bg2 = Sprite::create(fileName);
		bg2->setAnchorPoint(Vec2::ZERO);
		bg2->setPosition(origin.x, origin.y + bg1->getContentSize().height);
		bg2->setScaleX(scaleX);
		this->addChild(bg2);

		//临界点
		this->peakPositionY = -bg1->getContentSize().height;
		//默认速度
		this->speed = 100.0f;
		//默认加速度
		this->acceleration = 0.0f;

		startRolling();
		return true;
	}
	catch(std::exception& e){
		log("%s", e.what());
		return false;
	}
}

//滚动  根据速度
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



//开始滚动
void MapLayer::startRolling(){
	this->scheduleUpdate();
}


//停止滚动
void MapLayer::stopRolling(){
	this->unscheduleUpdate();
}
