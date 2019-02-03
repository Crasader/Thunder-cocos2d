#pragma once
#include "cocos2d.h"
USING_NS_CC;


typedef enum {
	tag_rocker,
	tag_rockerBG
}tagForRocker;

typedef enum {
	rocker_stay = 0,
	rocker_right = 1,
	rocker_up,
	rocker_left,
	rocker_down,
}tagDirection;


class Rocker :public Layer {
public:


	static Rocker* createRocker(const char* rockerImage, const char*rockerBGImage, Vec2 position, Rect _limitZone);
	CREATE_FUNC(Rocker);

	void startRocker(bool _isStopOther);
	void stopRocker();


	float radDirection;
	tagDirection rockerDirection;
	bool rockerRun;

private:
	void rockerInit(const char* rockerImage, const char*rockerBGImage, Vec2 position, Rect _limitZone);
	//获取两个点之间的角度
	float getRad(Vec2 pos1, Vec2 pos2);
	bool onTouchBegan(Touch* touch, Event* unused_event)override;
	void onTouchMoved(Touch* touch, Event* unused_event)override;
	void onTouchEnded(Touch* touch, Event* unused_event)override;
	Vec2 getAnglePosition(float r, float angle);


	Rect limitZone;
	Vec2 rockerBGPosition;
	float rockerBGRadius;
	bool isCanMove;
};