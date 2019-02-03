#pragma once
#include "cocos2d.h"
USING_NS_CC;


//背景地图层 循环滚动播放
class MapLayer : public Layer {
public:
	static MapLayer* createWithFile(const char* fileName);
	bool init(const char* fileName);

	virtual void update(float dt);

	void startRolling();
	void stopRolling();
private:
	Sprite* bg1;
	Sprite* bg2;

	float peakPositionY;

protected:
	//滚动速度
	CC_SYNTHESIZE(float, speed, Speed);

    //滚动加速度
	CC_SYNTHESIZE(float, acceleration, Acceleration);

	//视窗口
	CC_SYNTHESIZE(Size, rollingRect, RollingRect);
};