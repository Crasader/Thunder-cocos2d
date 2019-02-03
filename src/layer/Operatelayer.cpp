#include "OperateLayer.h"


bool Operatelayer::init() {

	if (!Layer::init()) {
		return false;
	}

	//������ť
	Button* button = Button::create();
	button->loadTextureNormal("rocker/attack_100.png");

	//50*50g
	//float scale = 100.0f / button->getContentSize().width;
	//button->setScale(scale);


	//��Ļ�ұ�
	button->setPosition(Vec2(420, 70));
	//�����ص��¼�
	button->addClickEventListener(CC_CALLBACK_1(Operatelayer::attackClickCallBack, this));

	this->addChild(button);


	return true;
}

void Operatelayer::attackClickCallBack(Ref * pSender) {
	log("attack");
	//TODO �ӵ�
}
