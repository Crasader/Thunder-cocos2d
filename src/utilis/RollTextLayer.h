#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


/*滚动字幕*/
class RollTextLayer : public Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate {
public:
	static RollTextLayer* createWithJsonFile(const char* fileName, Vec2 position,Size size, float rollingSpeed=50.0f);
	bool init(const char* fileName, Vec2 position, Size size, float rollingSpeed);

	virtual void update(float dt) override;

	//table view
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)override {};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)override {}
	virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)override;
	virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
	virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)override;
	virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table)override;

private:
	bool loadJsonFile(const char* fileName);


private:
	//需要播放的文字
	std::vector<std::string> text;

	//滚动速度
	float rollingSpeed = 50;

	//TableView
	TableView* tableView;

	//total height
	float totalHeight = 0.0f;
};