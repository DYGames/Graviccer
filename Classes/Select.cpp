#include "stdafx.h"

Scene* Select::createScene()
{
	auto scene = Scene::create();

	auto layer = Select::create();

	scene->addChild(layer);

	return scene;
}

bool Select::init()
{
	if (!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Select::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	MenuItemImage* right = MenuItemImage::create("right.png", "right.png", CC_CALLBACK_1(Select::menuSelect, this));
	right->setTag(2000);
	right->setPosition(Point(170, 100));

	MenuItemImage* left = MenuItemImage::create("left.png", "left.png", CC_CALLBACK_1(Select::menuSelect, this));
	left->setTag(2001);
	left->setPosition(Point(-160, 100));

	Menu* menu = Menu::create(right, left, NULL);
	this->addChild(menu, 88);

	Singleton::getInstance()->stage = 1;

	Sprite* selectImage = Sprite::create("stagebg.png");
	selectImage->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(selectImage);
	stageNumber = Sprite::create("1.png");
	stageNumber->setPosition(Point(250, 755));
	this->addChild(stageNumber, 1);

	stageImage = Sprite::create("stage1.png");
	stageImage->setPosition(Point(250, 480));
	stageImage->setScale(0.45f);
	this->addChild(stageImage, 1);

	Sprite* start = Sprite::create("start.png");
	start->setPosition(Vec2(240, 175));
	start->setTag(123);
	this->addChild(start);

	return true;
}

void Select::menuSelect(Ref* sender)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	switch (((MenuItemImage*)sender)->getTag())
	{
	case 2000:
		if (Singleton::getInstance()->stage < 5)
			Singleton::getInstance()->stage++;
		break;
	case 2001:
		if (Singleton::getInstance()->stage > 1)
			Singleton::getInstance()->stage--;
		break;
	}
	Change();
}

void Select::Change()
{
	this->removeChild(stageNumber);
	this->removeChild(stageImage);

	char str[256];
	sprintf(str, "%d.png", Singleton::getInstance()->stage);
	stageNumber = Sprite::create(str);
	stageNumber->setPosition(Point(250, 755));
	this->addChild(stageNumber, 1);

	sprintf(str, "stage%d.png", Singleton::getInstance()->stage);
	stageImage = Sprite::create(str);
	stageImage->setPosition(Point(250, 480));
	stageImage->setScale(0.45f);
	this->addChild(stageImage, 1);
}

bool Select::onTouchBegan(Touch* touch, Event* _event)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	if (this->getChildByTag(123)->getBoundingBox().containsPoint(touch->getLocation())){
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
		Director::getInstance()->replaceScene(TransitionFade::create(0.75f, inGame::createScene()));
	}
	return true;
}