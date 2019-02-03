#pragma once
#include "cocos2d.h"
USING_NS_CC;


//关于场景  滚动播放信息
class AboutScene : public Scene {
public:
	CREATE_FUNC(AboutScene);

	virtual bool init() override;

private:
	//返回菜单场景
	void returnCallBack(Ref * pSender);
};