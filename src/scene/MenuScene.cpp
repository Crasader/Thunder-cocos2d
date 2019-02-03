#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "AboutScene.h"
#include "GameScene.h"
#include "../layer/ControlLayer.h"
using namespace CocosDenshion;


/*初始化菜单按钮*/
bool MenuScene::init(){
	if (!Scene::init()) {
		return false;
	}

	//游戏主界面背景
	auto bgImage = Sprite::create("bgImage/startbg1.jpg");
	bgImage->setAnchorPoint(Vec2::ZERO);
	bgImage->setPosition(Vec2::ZERO);
	//设置缩放
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float scaleX = visibleSize.width / bgImage->getContentSize().width;
	float scaleY = visibleSize.height / bgImage->getContentSize().height;
	bgImage->setScale(scaleX, scaleY);

	this->addChild(bgImage);


	//单人游戏	
	MenuItemFont* singlePlayer = MenuItemFont::create("single",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	singlePlayer->setTag(SINGLEPLAYER);
	singlePlayer->setColor(Color3B::BLUE);

	//双人对战	
	MenuItemFont* mulitiPlayer = MenuItemFont::create("mulitiplayer",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	mulitiPlayer->setTag(MULITIPLAYER);
	mulitiPlayer->setColor(Color3B::BLUE);

	//设置	
	MenuItemFont* setting = MenuItemFont::create("setting",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	setting->setTag(SETTING);
	setting->setColor(Color3B::BLUE);

	//关于	
	MenuItemFont* about = MenuItemFont::create("about",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));	
	about->setTag(ABOUT);
	about->setColor(Color3B::BLUE);


	//退出
	MenuItemFont* exit = MenuItemFont::create("exit",
		CC_CALLBACK_1(MenuScene::menuItemTouchCallBack, this));
	exit->setTag(EXIT);
	exit->setColor(Color3B::BLUE);


	//菜单	
	Menu* menu = Menu::create(singlePlayer, mulitiPlayer, setting, about,exit, NULL);
	menu->alignItemsVertically();	
	this->addChild(menu);



	//播放背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("music/Chase.mp3");

	return true;
}

void MenuScene::menuItemTouchCallBack(Ref * pSender){
	//播放音效
	SimpleAudioEngine::getInstance()->playEffect("sound-effect/clickItem.wav");
	MenuItem* item = static_cast<MenuItem*>(pSender);
	//场景跳转（push）	
	switch (item->getTag()) {
	case SINGLEPLAYER:
	{
		auto gameScene = GameScene::create();
		//添加控制层
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

    //退出
	case EXIT:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
