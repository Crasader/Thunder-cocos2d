#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

class Operatelayer : public Layer {
public:
	CREATE_FUNC(Operatelayer);
	virtual bool init()override;
private:

	//������ť�ص��¼�
	void attackClickCallBack(Ref* pSender);

};