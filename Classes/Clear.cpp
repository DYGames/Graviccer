#include "stdafx.h"

Scene* Clear::createScene()
{
	auto scene = Scene::create();

	auto layer = Clear::create();

	scene->addChild(layer);

	return scene;
}

bool Clear::init()
{
	if (!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	Sprite* clearbg = Sprite::create("clearbg.png");
	clearbg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(clearbg);

	char str[256];
	sprintf(str, "%d.png", Singleton::getInstance()->stage);

	Sprite* stage = Sprite::create(str);
	stage->setPosition(Vec2((winSize.width / 2) + 20, 750));
	this->addChild(stage);

	MenuItemImage* retry = MenuItemImage::create("retry.png", "retry.png", CC_CALLBACK_1(Clear::callMenu, this));
	retry->setScale(2.5f);
	retry->setTag(7000);

	MenuItemImage* next = MenuItemImage::create("next.png", "next.png", CC_CALLBACK_1(Clear::callMenu, this));
	next->setScale(2.5f);
	next->setTag(7001);

	MenuItemImage* gomenu = MenuItemImage::create("gomenu.png", "gomenu.png", CC_CALLBACK_1(Clear::callMenu, this));
	gomenu->setScale(2.5f);
	gomenu->setTag(7002);

	Menu* menu = Menu::create(retry, next, gomenu, NULL);
	menu->alignItemsHorizontallyWithPadding(winSize.width * 0.03f);
	menu->setPosition(Vec2(winSize.width / 2, 240));
	this->addChild(menu, 88);

	return true;
}

void Clear::callMenu(Ref* sender)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	switch (((MenuItemImage*)sender)->getTag())
	{
	case 7000:
		Director::getInstance()->replaceScene(TransitionFade::create(0.75f, inGame::createScene()));
		break;
	case 7001:
		if (Singleton::getInstance()->stage != 5){
			Singleton::getInstance()->stage += 1;
			Director::getInstance()->replaceScene(TransitionFade::create(0.75f, inGame::createScene()));
		}
		break;
	case 7002:
		Director::getInstance()->replaceScene(TransitionFade::create(0.75f, Select::createScene()));
		break;
	}
}