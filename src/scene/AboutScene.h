#pragma once
#include "cocos2d.h"
USING_NS_CC;


//���ڳ���  ����������Ϣ
class AboutScene : public Scene {
public:
	CREATE_FUNC(AboutScene);

	virtual bool init() override;

private:
	//���ز˵�����
	void returnCallBack(Ref * pSender);
};