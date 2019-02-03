#include "AboutScene.h"
#include "SimpleAudioEngine.h"
#include "../utilis/RollTextLayer.h"
using namespace CocosDenshion;


bool AboutScene::init(){
	if (!Scene::init()) {
		return false;
	}

	//���  ������Ļ
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto position = Vec2(visibleSize.width/4, visibleSize.height/6);
	auto rollTextLayer = RollTextLayer::createWithJsonFile("config/about.json", position, visibleSize*3/4);
	if (rollTextLayer) {
		this->addChild(rollTextLayer);
	}
	else {
		CC_SAFE_DELETE(rollTextLayer);
	}


	//����
	auto returnItem = MenuItemImage::create("menu-item/Back-up.png", "menu-item/Back-down.png", CC_CALLBACK_1(AboutScene::returnCallBack, this));
	returnItem->setAnchorPoint(Vec2(0.0f, 1.0f));
	auto origin = Director::getInstance()->getVisibleOrigin();
	returnItem->setPosition(origin.x,origin.y+visibleSize.height);

	Menu* menu = Menu::create(returnItem, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu);

	return true;
}



//���ز˵�����
void AboutScene::returnCallBack(Ref * pSender) {
	//������Ч
	SimpleAudioEngine::getInstance()->playEffect("sound-effect/clickItem.wav");
	Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
}