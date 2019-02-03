#include "BloodBar.h"
#include <exception>

BloodBar * BloodBar::createWithFile(const char* csbFile, Vec2 position,int hp){
	BloodBar* bloodBar = new BloodBar();
	if (bloodBar && bloodBar->init(csbFile,position,hp)) {
		bloodBar->autorelease();
		return bloodBar;
	}
	else {
		CC_SAFE_DELETE(bloodBar);
	}
	return nullptr;
}

bool BloodBar::init(const char* csbFile, Vec2 position,int hp){
	try {
		auto bloodBar = CSLoader::createNode(csbFile);
		this->addChild(bloodBar);
		bloodBar->setPosition(position);

		//±³¾° bg
		this->bg = static_cast<Sprite*>(bloodBar->getChildByTag(9));

		//bar
		this->bar = static_cast<Sprite*>(bloodBar->getChildByTag(10));

		//×ÖÌå
		this->hp = hp;
		this->HpText = static_cast<ui::TextAtlas*>(bloodBar->getChildByTag(12));
		
		this->HpText->setString(StringUtils::format("%d/%d",this->hp,this->hp));

		return true;
	}
	catch (std::exception& ex) {
		log("%s", ex.what());
		return false;
	}
}

void BloodBar::setPercent(float value){
	int curHP = this->hp*value;
	this->bar->setScaleX(value);
	this->HpText->setString(StringUtils::format("%d/%d", curHP, this->hp));
}
