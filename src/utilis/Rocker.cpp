#include "Rocker.h"
#define PI 3.1415926

Rocker * Rocker::createRocker(const char * rockerImage, const char * rockerBGImage, Vec2 position, Rect _limitZone) {

	Rocker* layer = Rocker::create();
	if (layer) {
		layer->rockerInit(rockerImage, rockerBGImage, position, _limitZone);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}



void Rocker::rockerInit(const char * rockerImage, const char * rockerBGImage, Vec2 position, Rect _limitZone) {
	//摇杆背景
	auto rockerBG = Sprite::create(rockerBGImage);
	rockerBG->setPosition(position);
	rockerBG->setVisible(false);
	this->addChild(rockerBG, 0, tag_rockerBG);

	//摇杆实体
	auto rocker = Sprite::create(rockerImage);
	rocker->setPosition(position);
	rocker->setVisible(false);
	this->addChild(rocker, 0, tag_rocker);

	//200*200
	float scaleBG = 100.0f / rockerBG->getContentSize().width;
	//100*100
	float scale = 50.0f / rocker->getContentSize().width;
	rockerBG->setScale(scaleBG);
	rocker->setScale(scale);



	//摇杆限制区域
	limitZone = _limitZone;
	rockerBGPosition = position;
	rockerBGRadius = rockerBG->getBoundingBox().size.width / 2;
	//log("%f", rockerBGRadius);
	rockerDirection = rocker_stay;
	isCanMove = false;
}




//开始监听
void Rocker::startRocker(bool _isStopOther) {


	//创建监听器
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(false);
	touchListener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}


//取消监听
void Rocker::stopRocker() {
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	rocker->setVisible(false);

	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);

	//移除监听器
	_eventDispatcher->removeEventListenersForTarget(this);
}





//开始触摸
bool Rocker::onTouchBegan(Touch * touch, Event * unused_event) {

	//显示rocker
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);

	//获取触摸点坐标
	Vec2 point = touch->getLocation();
	//是否在屏幕左半边区域内 右半边需要点击其他按钮
	//if (rocker->getBoundingBox().containsPoint(point)) {
	//	isCanMove = true;
	//	log("begin");
	//}
	if (limitZone.containsPoint(point)) {
		isCanMove = true;
		rockerBGPosition = point;

		rocker->setPosition(point);
		rocker->setVisible(true);
		rockerBG->setPosition(point);
		rockerBG->setVisible(true);
	}
	return true;
}



void Rocker::onTouchMoved(Touch * touch, Event * unused_event) {
	if (!isCanMove) {
		return;
	}
	Vec2 point = touch->getLocation();
	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);

	//角度
	float angle = getRad(rockerBGPosition, point);
	this->radDirection = angle;

	//超出rocker范围 画在背景半径内
	if (sqrt(pow(rockerBGPosition.x - point.x, 2) + pow(rockerBGPosition.y - point.y, 2)) >= rockerBGRadius) {
		rocker->setPosition(getAnglePosition(rockerBGRadius, angle) + rockerBGPosition);
	}
	else {
		rocker->setPosition(point);
	}

	//角度
	if (angle >= -PI / 4 && angle < PI / 4) {
		rockerDirection = rocker_right;
	}
	else if (angle >= PI / 4 && angle < 3 * PI / 4) {
		rockerDirection = rocker_up;
	}
	else if (angle >= 3 * PI / 4 && angle < 5 * PI / 4) {
		rockerDirection = rocker_left;
	}
	else {
		rockerDirection = rocker_down;
	}
}


Vec2 Rocker::getAnglePosition(float r, float angle) {
	return Vec2(r*cos(angle), r*sin(angle));
}


//恢复到原来的位置  隐藏
void Rocker::onTouchEnded(Touch * touch, Event * unused_event) {
	if (!isCanMove) {
		return;
	}

	auto rocker = (Sprite*)this->getChildByTag(tag_rocker);
	auto rockerBG = (Sprite*)this->getChildByTag(tag_rockerBG);

	rocker->stopAllActions();
	rocker->runAction(MoveTo::create(0.08f, rockerBGPosition));
	rocker->setVisible(false);
	rockerBG->setVisible(false);

	isCanMove = false;
	rockerDirection = rocker_stay;
}


//获取弧度
float Rocker::getRad(Vec2 pos1, Vec2 pos2) {
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;

	float dx = px2 - px1;
	float dy = py2 - py1;

	float dia = sqrt(pow(dx, 2) + pow(dy, 2));
	float cosAngle(dx / dia);
	float rad = acos(cosAngle);

	if (py2 < py1) {
		rad = -rad;
	}
	return rad;
}