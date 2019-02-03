#include "ControlLayer.h"
#include "../layer/Operatelayer.h"
#include "../layer/MapLayer.h"
#include "../game/BaseFSM.h"
#include"cocostudio/CocoStudio.h"
using namespace cocostudio;

bool ControlLayer::init(){
	if (!Layer::init()) {
		return false;
	}
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//±³¾°²ã ¹ö¶¯
	auto mapLayer = MapLayer::createWithFile("bgImage/background4.png");
	this->addChild(mapLayer);

	//TODO ÔØÈëÅäÖÃÎÄ¼þ
	auto playerPlaneProperty = PropertyManager::create();
	playerPlaneProperty->setDataName("export/player-plane/player-plane.ExportJson");
	playerPlaneProperty->setArmatureName("player-plane");
	playerPlaneProperty->setShootingInterval(1.0f);
	playerPlaneProperty->setType(PLAER_PLANE);
	playerPlaneProperty->setVelocity(500);
	playerPlaneProperty->setAcceleration(0);
	playerPlaneProperty->setHP(100);
	playerPlaneProperty->setDefaultPosition(Vec2(origin.x+visibleSize.width*0.5,origin.y+visibleSize.height*0.5));
	//player
	playerPlane = PlayerPlane::createWithProperty(playerPlaneProperty);
	this->addChild(playerPlane,1);
	//FSM×´Ì¬»ú
	auto playerFSM = BaseFSM::createFSM(playerPlane);
	playerFSM->retain();
	playerPlane->setBaseFSM(playerFSM);

	//rockerÒ¡¸Ë
	//Ò¡¸ËÏÞÖÆÇøÓò ×ó°ëÆÁÄ»
	auto limitZone = Rect(origin.x, origin.y, visibleSize.width*0.5, visibleSize.height);
	rocker = Rocker::createRocker("rocker/rocker.png", "rocker/rockerBG.png", Vec2(200, 200), limitZone);
	rocker->startRocker(true);
	this->addChild(rocker);

	//¼¼ÄÜ²ã
	Operatelayer* operateLayer = Operatelayer::create();
	this->addChild(operateLayer);

	//ÑªÌõ
	bloodBar = BloodBar::createWithFile("ui/BloodBar.csb", Vec2(130, 680),playerPlane->property->getHP());
	if (bloodBar) {
		this->addChild(bloodBar, 2);
	}

	this->scheduleUpdate();
	return true;
}


//player ×´Ì¬»ú
void ControlLayer::update(float dt){
	playerPlane->getBaseFSM()->switchMoveState(rocker->rockerDirection,rocker->radDirection,dt);
	//bloodBar->setPercent(0.1);
}
