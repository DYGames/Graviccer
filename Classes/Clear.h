#pragma once

#include "stdafx.h"

class Clear : public Layer
{
private:

public:
	static Scene* createScene();

	virtual bool init();

	void callMenu(Ref* sender);

	CREATE_FUNC(Clear);
};