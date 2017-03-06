#pragma once

#include "stdafx.h"

using namespace CocosDenshion;

class Intro : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();

	virtual bool onTouchBegan(Touch* touch, Event* _event);

	CREATE_FUNC(Intro);
};