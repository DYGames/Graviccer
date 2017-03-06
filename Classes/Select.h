#pragma once

#include "stdafx.h"

class Select : public Layer
{
private:

	Sprite* stageNumber;
	Sprite* stageImage;
public:
	static Scene* createScene();

	virtual bool init();

	void menuSelect(Ref* sender);
	void Change();

	virtual bool onTouchBegan(Touch* touch, Event* _event);

	CREATE_FUNC(Select);
};