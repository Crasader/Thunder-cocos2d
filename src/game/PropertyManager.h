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

//���з���ö��
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


//����
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
	//�ٶ�
	CC_SYNTHESIZE(int, velocity, Velocity);
	//���ٶ�
	CC_SYNTHESIZE(int, acceleration, Acceleration);

	//����
	CC_SYNTHESIZE(OBJECT_TYPE, type, Type);
	//���з���
	CC_SYNTHESIZE(FLYING_DIRECTION, flyingDirection, FlyingDirection);

	//������� update
	CC_SYNTHESIZE(float, shootingInterval, ShootingInterval);

	//�ӵ�����
	CC_SYNTHESIZE(int, bulletLevel, BulletLevel);


	//����֡
	CC_SYNTHESIZE(std::string, ArmatureName, ArmatureName);
	CC_SYNTHESIZE(std::string, DataName, DataName);
};