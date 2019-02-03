#pragma once
#include "cocos2d.h"
#include "../utilis/Rocker.h"
#include "../utilis/BloodBar.h"
#include "../game/Player_Plane.h"
USING_NS_CC;


class ControlLayer : public Layer {
public:
	CREATE_FUNC(ControlLayer);
	virtual bool init()override;
	void update(float dt)override;
private:
	PlayerPlane* playerPlane;
	//Ò¡¸Ë
	Rocker* rocker;

	//ÑªÌõ
	BloodBar* bloodBar;
};