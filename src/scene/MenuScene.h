#pragma once
#include "cocos2d.h"
USING_NS_CC;

typedef enum {
	SINGLEPLAYER=1,
	MULITIPLAYER,
	SETTING,
	ABOUT,
	EXIT
}MENU_ITEM;






//菜单场景
class MenuScene : public Scene {
public:
	CREATE_FUNC(MenuScene);
	virtual bool init()override;

private:
	//菜单选项回调函数
	void menuItemTouchCallBack(Ref *pSender);
};