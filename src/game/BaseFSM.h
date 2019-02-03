#pragma once
#include "cocos2d.h"
#include "Player_Plane.h"
#include "../utilis/Rocker.h"
USING_NS_CC;


//ÓÐÏÞ×´Ì¬»ú
class BaseFSM :public Ref {
public:
	static BaseFSM* createFSM(PlayerPlane* baseRole);
	bool init(PlayerPlane* baseRole);


	void switchMoveState(tagDirection direction,float radDirection,float dt);

	void changeToMove(float radDirection,float dt);
	void changeToDefault();
	void changeToAttack();
	void changeToDead();

public:
	PlayerPlane* baseRole;
};