#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;

//Ѫ��ʵ��
class BloodBar : public Node {
public:
	static BloodBar* createWithFile(const char* csbFile, Vec2 position,int hp);
	bool init(const char* csbFile, Vec2 position,int hp);

	void setPercent(float value);

private:
	//Ѫ��
	Sprite* bar;

	//Ѫ������
	Sprite* bg;

	//
	ui::TextAtlas* HpText;

	//Ѫ���ٷֱ�
	float percent;

	int hp;
};