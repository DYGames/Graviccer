#include "stdafx.h"

Scene* Intro::createScene()
{
	auto scene = Scene::create();

	auto layer = Intro::create();

	scene->addChild(layer);

	return scene;
}

bool Intro::init()
{
	if (!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Intro::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bmusic.wav");

	SimpleAudioEngine::getInstance()->preloadEffect("bounce.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("click.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("clap.wav");

	SimpleAudioEngine::getInstance()->playBackgroundMusic("bmusic.wav", true);

	Sprite* background = Sprite::create("main.png");
	background->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(background);

	return true;
}

bool Intro::onTouchBegan(Touch* touch, Event* _event)
{
	SimpleAudioEngine::getInstance()->playEffect("click.mp3");
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,Select::createScene()));

	return true;
}