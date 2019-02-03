#pragma once
#include "cocos2d.h"
#include "PropertyManager.h"
#include"cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

typedef enum {
	ROLE_DEFAULT = 1,
	ROLE_ATTACK,
	ROLE_MOVE,
	ROLE_DEAD
}ROLE_STATE;


//前向申明
class BaseFSM;

class PlayerPlane : public Node{
public:
	static PlayerPlane* createWithProperty(PropertyManager* _property);
	virtual bool init(PropertyManager* _property);

	void shooting(float dt);

public:
	PropertyManager* property;
	CC_SYNTHESIZE(Armature*, armature, Armature);
	//角色状态
	CC_SYNTHESIZE(ROLE_STATE, state, State);
	//FSM
	CC_SYNTHESIZE(BaseFSM*, baseFSM, BaseFSM);
};