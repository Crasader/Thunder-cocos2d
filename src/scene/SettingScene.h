#pragma once
#include "cocos2d.h"
USING_NS_CC;

//���ó���
class SettingScene : public Scene {
public:
	CREATE_FUNC(SettingScene);
	virtual bool init()override;

private:
	void musicToggleCallBack(Ref* pSender);
	void returnCallBack(Ref* pSender);
};