#pragma once
#include "cocos2d.h"
USING_NS_CC;

//…Ë÷√≥°æ∞
class SettingScene : public Scene {
public:
	CREATE_FUNC(SettingScene);
	virtual bool init()override;

private:
	void musicToggleCallBack(Ref* pSender);
	void returnCallBack(Ref* pSender);
};