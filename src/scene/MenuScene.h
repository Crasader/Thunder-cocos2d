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






//�˵�����
class MenuScene : public Scene {
public:
	CREATE_FUNC(MenuScene);
	virtual bool init()override;

private:
	//�˵�ѡ��ص�����
	void menuItemTouchCallBack(Ref *pSender);
};