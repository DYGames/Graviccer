#pragma once

#include "stdafx.h"

#define PTM_RATIO 32
#define DEGTORAD 0.0174532925199432957f

#define singleton Singleton::getInstance()

class inGame : public Layer
{
private:
	vector<Sprite*>vDefense;

	cocos2d::Size _winSize;

	Texture2D* _ball;
	Texture2D* _wall;

	b2World* _world;

	MyContact* _myContact;

	int _count = 0;

	bool ballexist = false;

	Sprite* ball = nullptr;
	Sprite* goalpoint = nullptr;
	Sprite* gravitypoint = nullptr;

	float _restitution;

	bool _goalin = false;
public:
	~inGame();

	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(inGame);

	virtual bool onTouchBegan(Touch* touch, Event *unused_event);
	virtual void onTouchMoved(Touch* touch, Event *unused_event);
	virtual void onTouchEnded(Touch* touch, Event *unused_event);

	void tick(float dt);
	void MoveDefense(float dt);
	void clearscene(float dt);

	void goal();
	void fail();
	void addAnim();

	void callMenu(Ref* sender);

	void addBall(Vec2 Location);
	void addWall(Vec2 Location, float angle, int data, bool rotation, bool left);
	void addDefense(Vec2 Location);
	void addGoal(Vec2 Location, float angle);
	void addGravityGoal(Vec2 Location, float angle);
	void addWarp(Vec2 Location, bool entrance);
	void addMoveDefense(Vec2 Location);
};