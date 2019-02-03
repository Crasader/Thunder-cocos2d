#include "SettingScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool SettingScene::init(){
	if (!Scene::init()) {
		return false;
	}

	//��������ѡ��
	//toggle �������ֿ���
	auto musicOnItem = MenuItemImage::create("menu-item/on.png", "menu-item/on.png");

	auto musicOffItem = MenuItemImage::create("menu-item/off.png", "menu-item/off.png");

	auto musicToggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::musicToggleCallBack, this),
		musicOnItem, musicOffItem, NULL);
	//ȷ��
	auto okItem = MenuItemImage::create("menu-item/ok-down.png", "menu-item/ok-up.png", CC_CALLBACK_1(SettingScene::returnCallBack, this));


	Menu* menu = Menu::create(musicToggleItem, okItem,NULL);
	menu->alignItemsVertically();
	this->addChild(menu);


	//����
	auto returnItem = MenuItemImage::create("menu-item/Back-up.png", "menu-item/Back-down.png", CC_CALLBACK_1(SettingScene::returnCallBack, this));
	returnItem->setAnchorPoint(Vec2(0.0f, 1.0f));
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	returnItem->setPosition(origin.x, origin.y + visibleSize.height);

	Menu* menu2 = Menu::create(returnItem, NULL);
	menu2->setPosition(Vec2::ZERO);

	this->addChild(menu2);


	//�������ж�
	if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
		musicToggleItem->setSelectedIndex(0);
	}
	else {
		musicToggleItem->setSelectedIndex(1);
	}

	return true;
}



void SettingScene::musicToggleCallBack(Ref* pSender) {
	//������Ч
	SimpleAudioEngine::getInstance()->playEffect("sound-effect/clickItem.wav");
	auto menuItemToggle = static_cast<MenuItemToggle*>(pSender);
	if (menuItemToggle->getSelectedIndex() == 0) {
		//ѭ������
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/Chase.mp3", true);
	}
	else {
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("music/Chase.mp3");
	}
}


//���ز˵�����
void SettingScene::returnCallBack(Ref * pSender) {
	//������Ч
	SimpleAudioEngine::getInstance()->playEffect("sound-effect/clickItem.wav");
	Director::getInstance()->popSceneWithTransition<TransitionFade>(1.0f);
}