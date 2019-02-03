#pragma once
#include "cocos2d.h"
USING_NS_CC;


//������ͼ�� ѭ����������
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
	//�����ٶ�
	CC_SYNTHESIZE(float, speed, Speed);

    //�������ٶ�
	CC_SYNTHESIZE(float, acceleration, Acceleration);

	//�Ӵ���
	CC_SYNTHESIZE(Size, rollingRect, RollingRect);
};