#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocostudio;

//血条实现
class BloodBar : public Node {
public:
	static BloodBar* createWithFile(const char* csbFile, Vec2 position,int hp);
	bool init(const char* csbFile, Vec2 position,int hp);

	void setPercent(float value);

private:
	//血条
	Sprite* bar;

	//血条背景
	Sprite* bg;

	//
	ui::TextAtlas* HpText;

	//血量百分比
	float percent;

	int hp;
};