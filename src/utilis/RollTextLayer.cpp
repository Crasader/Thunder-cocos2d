#include "RollTextLayer.h"
#include "json/rapidjson.h"
#include "json/document.h"
using namespace rapidjson;
USING_NS_CC_EXT;

RollTextLayer * RollTextLayer::createWithJsonFile(const char * fileName, Vec2 position, Size size, float rollingSpeed){
	RollTextLayer* rollTextLayer = new RollTextLayer();
	if (rollTextLayer && rollTextLayer->init(fileName, position,size, rollingSpeed)) {
		rollTextLayer->autorelease();
	}
	else {
		CC_SAFE_DELETE(rollTextLayer);
	}
	return rollTextLayer;
}

bool RollTextLayer::init(const char * fileName, Vec2 position, Size size, float rollingSpeed){
	//载入滚动json文件
	if (!loadJsonFile(fileName)) {
		return false;
	}
	//设置tableview
	tableView = TableView::create(this, size);
	//垂直滚动
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setAnchorPoint(Vec2::ZERO);
	tableView->setPosition(position);
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView);
	tableView->reloadData();


	this->rollingSpeed = rollingSpeed;
	this->scheduleUpdate();
	return true;
}



//点击cell
void RollTextLayer::tableCellTouched(TableView* table, TableViewCell* cell){
	CCLOG("cell touched at index: %ld", static_cast<long>(cell->getIdx()));
}


//cell大小
Size RollTextLayer::tableCellSizeForIndex(TableView *table, ssize_t idx){
	return Size(60, 50);
}

TableViewCell* RollTextLayer::tableCellAtIndex(TableView *table, ssize_t idx){
	TableViewCell *cell = table->dequeueCell();
	//首次初始化
	if (!cell) {
		cell = new (std::nothrow) TableViewCell();
		cell->autorelease();

		float fontSize = 20.0f;
		auto label = Label::createWithSystemFont(text[idx], "Helvetica",fontSize);
		label->setAlignment(CCTextAlignment::CENTER);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	}
	//重新计算
	else{
		auto label = (Label*)cell->getChildByTag(123);
		label->setString(text[idx]);
	}
	return cell;
}


//cell数量
ssize_t RollTextLayer::numberOfCellsInTableView(TableView *table){
	//返回字幕
	return text.size();
}


//读取json 字幕文件 并保存至vector中
bool RollTextLayer::loadJsonFile(const char * fileName){
	auto content = FileUtils::getInstance()->getStringFromFile(fileName);
	Document doc;
	doc.Parse<0>(content.c_str(), content.size());

	//解析错误
	if (doc.HasParseError()) {
		log("ParseError");
		return false;
	}
	else {
		log("Parse correct");
	}

	text.clear();
	if (!doc.HasMember("contents")) {
		log("json格式不正确");
		return false;
	}
	else {
		rapidjson::Value& res = doc["contents"];
		if (res.IsArray()) {
			for (SizeType i = 0; i < res.Size(); i++) {
				rapidjson::Value& d = res[i];
				if (d.HasMember("title") && d.HasMember("text")) {
					text.push_back(d["title"].GetString());
					text.push_back(d["text"].GetString());
					log("%s %s", d["title"].GetString(), d["text"].GetString());
				}
			}
		}
	}
	return true;
}

//滚动
void RollTextLayer::update(float dt){
	tableView->setContentOffset(tableView->getContentOffset() + Vec2(0, rollingSpeed*dt));
	if (tableView->getContentOffset().y>numberOfCellsInTableView(tableView)*tableCellSizeForIndex(tableView, text.size() - 1).height) {
		log("over");
		tableView->reloadData();
	}
}
