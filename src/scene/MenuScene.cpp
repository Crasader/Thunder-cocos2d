#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "AboutScene.h"
#include "GameScene.h"
#include "../layer/ControlLayer.h"
using namespace CocosDenshion;


/*��ʼ���˵���ť*/
bool MenuScene::init(){
	if (!Scene::init()) {
		return false;
	}

	//��Ϸ�����汳��
	auto bgImage = Sprite::create("bgImage/startbg1.jpg");
	bgImage->setAnchorPoint(Vec2::ZERO);
	bgImage->setPosition(Vec2::ZERO);
	//��������
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float scaleX = visibleSize.width / bgImage->getContentSize().width;
	float scaleY = visibleSize.height / bgImage->getContentSize().height;
	bgImage->setScale(scaleX, scaleY);

	this->addChild(bgImage);


	//������Ϸ	
	MenuItemFont* singlePlayer = MenuItemFont::create("single",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	singlePlayer->setTag(SINGLEPLAYER);
	singlePlayer->setColor(Color3B::BLUE);

	//˫�˶�ս	
	MenuItemFont* mulitiPlayer = MenuItemFont::create("mulitiplayer",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	mulitiPlayer->setTag(MULITIPLAYER);
	mulitiPlayer->setColor(Color3B::BLUE);

	//����	
	MenuItemFont* setting = MenuItemFont::create("setting",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	setting->setTag(SETTING);
	setting->setColor(Color3B::BLUE);

	//����	
	MenuItemFont* about = MenuItemFont::create("about",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	about->setTag(ABOUT);
	about->setColor(Color3B::BLUE);


	//�˳�
	MenuItemFont* exit = MenuItemFont::create("exit",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));
	exit->setTag(EXIT);
	exit->setColor(Color3B::BLUE);


	//�˵�	
	Menu* menu = Menu::create(singlePlayer, mulitiPlayer, setting, about,exit, NULL);
	menu->alignItemsVertically();	
	this->addChild(menu);



	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/Chase.mp3");

	return true;
}

void MenuScene::menuItemTouchCallBack(Ref * pSender){
	//������Ч
	SimpleAudioEngine::getInstance()->playEffect("sound-effect/clickItem.wav");
	MenuItem* item = static_cast<MenuItem*>(pSender);
	//������ת��push��	
	switch (item->getTag()) {
	case SINGLEPLAYER:
	{
		auto gameScene = GameScene::create();
		//��ӿ��Ʋ�
		auto controlLayer = ControlLayer::create();
		gameScene->addChild(controlLayer);
		Director::getInstance()->pushScene(TransitionFade::create(1.0f, gameScene));
	}
	break;
	case MULITIPLAYER:
		break;
	case SETTING:
	{
		auto settingScene = SettingScene::create();
		Director::getInstance()->pushScene(TransitionFade::create(1.0f,settingScene));
	}
	break;
	case ABOUT:
	{
		auto aboutScene = AboutScene::create();
		Director::getInstance()->pushScene(TransitionFade::create(1.0f, aboutScene));
	}
		break;

    //�˳�
	case EXIT:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
