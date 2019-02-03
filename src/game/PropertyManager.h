#pragma once
#include "cocos2d.h"
USING_NS_CC;


typedef enum {
	PLAER_PLANE=1,
	PLAYER_BULLET,
	ENEMY_PLANE,
	ENEMY_BULLET,
	EXPLOSION
}OBJECT_TYPE;

//飞行方向枚举
typedef enum  {
	STOP,
	LEFT,
	UP,
	LEFT_UP,
	RIGHT,
	DOWN,
	RIGHT_UP,
	LEFT_DOWN,
	RIGHT_DOWN
}FLYING_DIRECTION;


//属性
class PropertyManager :public Ref {
public:
	CREATE_FUNC(PropertyManager);
	static PropertyManager* createWithProtobuf() {};
	virtual bool init();

public:
	CC_SYNTHESIZE(int, ID, ID);
	CC_SYNTHESIZE(int, HP, HP);
	CC_SYNTHESIZE(int, maxHP, MaxHP);
	CC_SYNTHESIZE(int, ATK, ATK);

	CC_SYNTHESIZE(Vec2, defaultPosition, DefaultPosition);
	//速度
	CC_SYNTHESIZE(int, velocity, Velocity);
	//加速度
	CC_SYNTHESIZE(int, acceleration, Acceleration);

	//类型
	CC_SYNTHESIZE(OBJECT_TYPE, type, Type);
	//飞行方向
	CC_SYNTHESIZE(FLYING_DIRECTION, flyingDirection, FlyingDirection);

	//攻击间隔 update
	CC_SYNTHESIZE(float, shootingInterval, ShootingInterval);

	//子弹类型
	CC_SYNTHESIZE(int, bulletLevel, BulletLevel);


	//动画帧
	CC_SYNTHESIZE(std::string, ArmatureName, ArmatureName);
	CC_SYNTHESIZE(std::string, DataName, DataName);
};