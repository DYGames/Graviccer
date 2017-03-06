#include "stdafx.h"

Scene* inGame::createScene()
{
	auto scene = Scene::create();

	auto layer = inGame::create();

	scene->addChild(layer);

	return scene;
}

bool inGame::init()
{
	if (!Layer::init())
		return false;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(inGame::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(inGame::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(inGame::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	_winSize = Director::getInstance()->getWinSize();

	Sprite* background = Sprite::create("ingamebg.png");
	background->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	this->addChild(background, 0);

	_ball = Director::getInstance()->getTextureCache()->addImage("ball.png");
	_wall = Director::getInstance()->getTextureCache()->addImage("wall.png");

	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body *groundBody = _world->CreateBody(&groundBodyDef);
	b2Body *underBody = _world->CreateBody(&groundBodyDef);

	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;

	b2EdgeShape groundEdge2;
	b2FixtureDef boxShapeDef2;

	boxShapeDef.shape = &groundEdge;
	boxShapeDef2.shape = &groundEdge2;

	groundEdge2.Set(b2Vec2(0, 0), b2Vec2(_winSize.width / PTM_RATIO, 0));
	underBody->SetUserData((void*)1);
	underBody->CreateFixture(&boxShapeDef2);

	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, _winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, _winSize.height / PTM_RATIO), b2Vec2(_winSize.width / PTM_RATIO, _winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(_winSize.width / PTM_RATIO, _winSize.height / PTM_RATIO), b2Vec2(_winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	Sprite* exam = Sprite::create("ball.png");
	Sprite* info = NULL;
	switch (singleton->stage){
	case 1:
		info = Sprite::create("stageinfo1.png");
		info->setPosition(Vec2(250, 500));
		exam->setPosition(Vec2(331.8f, 776.3f));
		addWall(Vec2(360, 640), 45, 1, false, false);
		addWall(Vec2(120, 240), -45, 2, false, false);
		singleton->_wallcount = 2;
		addGoal(Vec2(240, 120), 0);
		_restitution = 0.5f;
		break;
	case 2:
		info = Sprite::create("stageinfo2.png");
		info->setPosition(Vec2(250, 500));
		exam->setPosition(Vec2(152.14f, 663.56f));
		addWall(Vec2(120, 600), -45, 1, false, false);
		addWall(Vec2(300, 460), 45, 2, false, false);
		addWall(Vec2(120, 220), -45, 3, false, false);
		singleton->_wallcount = 3;
		addGravityGoal(Vec2(320, 120), 0);
		addGoal(Vec2(420, 460), -90);
		_restitution = 0.9f;
		break;
	case 3:
		info = Sprite::create("stageinfo3.png");
		info->setAnchorPoint(Vec2(1, 1));
		info->setPosition(Vec2(480, 800));
		exam->setPosition(Vec2(164.12f, 727.46f));
		addWall(Vec2(150, 600), -35, 1, false, false);
		addWall(Vec2(150, 150), -35, 2, false, false);
		addWall(Vec2(400, 175), 65, 3, false, false);
		singleton->_wallcount = 3;
		addDefense(Vec2(65, _winSize.height / 2));
		addDefense(Vec2(155, _winSize.height / 2));
		addDefense(Vec2(245, _winSize.height / 2));
		addDefense(Vec2(335, _winSize.height / 2));
		addDefense(Vec2(425, _winSize.height / 2));
		addWarp(Vec2(400, 500), true);
		addWarp(Vec2(115, 300), false);
		addGoal(Vec2(265, 80), 0);
		_restitution = 0.9f;
		break;
	case 4:
		info = Sprite::create("stageinfo4.png");
		info->setPosition(Vec2(250, 500));
		addWall(Vec2(120, 600), 0, 1, true, false);
		addWall(Vec2(360, 300), 0, 2, true, true);
		addMoveDefense(Vec2(240, 440));
		singleton->_wallcount = 2;
		addGoal(Vec2(240, 120), 0);
		_restitution = 0.7f;
		break;
	case 5:
		info = Sprite::create("stageinfo5.png");
		info->setPosition(Vec2(250, 250));
		addMoveDefense(Vec2(240, 600));
		addWarp(Vec2(400, 700), false);
		addWarp(Vec2(115, 500), true);
		addWall(Vec2(400, 300), 0, 1, true, true);
		addWall(Vec2(120, 175), 135, 2, true, false);
		addGoal(Vec2(240, 120), 0);
		singleton->_wallcount = 2;
		_restitution = 0.7f;
		break;
	}
	exam->setOpacity(255 * 0.35);
	info->setOpacity(255 * 0.45);
	this->addChild(info);
	this->addChild(exam);

	Sprite* retry = Sprite::create("retry.png");
	Sprite* gomenu = Sprite::create("gomenu.png");
	MenuItemSprite* retrym = MenuItemSprite::create(retry, retry, CC_CALLBACK_1(inGame::callMenu, this));
	retrym->setTag(8001);
	MenuItemSprite* gomenum = MenuItemSprite::create(gomenu, gomenu, CC_CALLBACK_1(inGame::callMenu, this));
	gomenum->setTag(8002);

	Menu* pausemenu = Menu::create(retrym, gomenum, NULL);
	pausemenu->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2));
	pausemenu->alignItemsHorizontallyWithPadding(_winSize.width * 0.25f);
	pausemenu->setOpacity(125);
	this->addChild(pausemenu, 1);

	memset(singleton->arraystage, false, sizeof(singleton->arraystage));

	this->schedule(schedule_selector(inGame::tick));
	this->schedule(schedule_selector(inGame::MoveDefense));

	_myContact = new MyContact();
	_world->SetContactListener((b2ContactListener*)_myContact);

	return true;
}

void inGame::callMenu(Ref* sender)
{
	switch (((MenuItemSprite*)sender)->getTag()){
	case 8001:
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
		Director::getInstance()->replaceScene(TransitionFade::create(0.75f, inGame::createScene()));
		break;
	case 8002:
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
		Director::getInstance()->replaceScene(TransitionFade::create(0.75f, Select::createScene()));
		break;
	}
}

inGame::~inGame()
{
	delete _world;
	_world = NULL;

	delete _myContact;
	_myContact = NULL;
}



void inGame::tick(float dt)
{
	_world->Step(dt, 8, 3);

	bool brek = false;
	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext()){
		if (b->GetUserData() != NULL && b->GetUserData() != (void*)1) {
			Sprite *spriteData = (Sprite *)b->GetUserData();
			if (spriteData->getName() == "ball"){
				for (auto it : vDefense){
					if (this->getChildByName("Entrance") != NULL){
						if (this->getChildByName("Entrance")->getBoundingBox().intersectsRect(spriteData->getBoundingBox())){
							Vec2 bp = this->getChildByName("Exit")->getPosition();
							b->SetTransform(b2Vec2(bp.x / PTM_RATIO, bp.y / PTM_RATIO), b->GetAngle());
						}
					}
					if (spriteData->getBoundingBox().intersectsRect(it->getBoundingBox())){

						this->removeChild(spriteData, true);
						ball = nullptr;
						ballexist = false;

						_world->DestroyBody(b);

						brek = true;

						singleton->arraystage[singleton->stage][8] = true;

						break;
					}
				}
			}
		}
		if (brek) break;
	}
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()){
		if (b->GetUserData() != NULL && b->GetUserData() != (void*)1){
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			if (singleton->arraystage[singleton->stage][8]){
				if (b->GetType() == b2_staticBody || b->GetType() == b2_kinematicBody){
					spriteData->setColor(Color3B::GRAY);
					for (int i = 0; i < singleton->_wallcount; i++){
						if (spriteData->getTag() == i + 1){
							singleton->arraystage[singleton->stage][i] = false;
							_count++;
						}
					}
				}
			}
		}
	}
	if (_count == singleton->_wallcount){
		_count = 0;
		singleton->arraystage[singleton->stage][8] = false;
	}
	bool fail = true;
	vector<b2Body*>toDestroy;
	vector<_Contact>::iterator pos;
	for (pos = _myContact->_vContact.begin(); pos != _myContact->_vContact.end(); ++pos){
		_Contact contact = *pos;
		b2Body *bodyA = contact.fixtureA->GetBody();
		b2Body *bodyB = contact.fixtureB->GetBody();

		if (bodyA->GetUserData() == (void*)1) {
			for (int i = 0; i < singleton->_wallcount; i++){
				if (!singleton->arraystage[singleton->stage][i]){
					fail = false;
				}
			}
			if (!fail || !singleton->arraystage[singleton->stage][9]){
				singleton->arraystage[singleton->stage][8] = true;
				if (std::find(toDestroy.begin(), toDestroy.end(), bodyB) == toDestroy.end()) {
					toDestroy.push_back(bodyB);
				}
			}
		}
	}

	vector<b2Body*>::iterator pos2;
	for (pos2 = toDestroy.begin(); pos2 != toDestroy.end(); ++pos2) {
		b2Body *body = *pos2;
		if (body->GetUserData() != NULL) {
			Sprite *sprite = (Sprite *)body->GetUserData();
			this->removeChild(sprite, true);
			ball = nullptr;
			ballexist = false;
		}
		_world->DestroyBody(body);
	}

	bool gravityon = true;
	if (ball != nullptr && ball != NULL && gravitypoint != nullptr && gravitypoint != NULL){
		for (int i = 0; i < singleton->_wallcount; i++){
			if (!singleton->arraystage[singleton->stage][i]){
				gravityon = false;
			}
		}
		if (gravityon){
			if (ball->getBoundingBox().intersectsRect(gravitypoint->getBoundingBox())){
				_world->SetGravity(b2Vec2(0.0f, 30.0f));
			}
		}
	}

	bool goalin = true;
	if (ball != nullptr && ball != NULL){
		if (ball->getBoundingBox().intersectsRect(goalpoint->getBoundingBox())){
			singleton->arraystage[singleton->stage][9] = true;
			for (int i = 0; i < singleton->_wallcount; i++){
				if (!singleton->arraystage[singleton->stage][i]){
					goalin = false;
				}
			}
			if (goalin){
				goal();
			}
			else{
				singleton->arraystage[singleton->stage][9] = false;
			}
		}
	}
}

void inGame::goal()
{
	if (!_goalin){
		_goalin = true;
		SimpleAudioEngine::getInstance()->playEffect("clap.wav");
		addAnim();
		scheduleOnce(schedule_selector(inGame::clearscene), 3.f);
	}
}

void inGame::clearscene(float dt)
{
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Director::getInstance()->replaceScene(TransitionFade::create(0.75f, Clear::createScene()));
}

void inGame::addAnim()
{
	Sprite *sprite = Sprite::create("clear1.png");
	sprite->setPosition(Vec2(_winSize.width / 2, _winSize.height / 2 + 100));

	Animation * animation = Animation::create();
	animation->setDelayPerUnit(0.07f);
	animation->addSpriteFrameWithFileName("clear1.png");
	animation->addSpriteFrameWithFileName("clear2.png");
	animation->addSpriteFrameWithFileName("clear3.png");
	animation->addSpriteFrameWithFileName("clear4.png");
	animation->addSpriteFrameWithFileName("clear5.png");
	animation->addSpriteFrameWithFileName("clear6.png");
	animation->addSpriteFrameWithFileName("clear7.png");
	animation->addSpriteFrameWithFileName("clear8.png");

	sprite->runAction(Animate::create(animation));
	this->addChild(sprite);
}

bool inGame::onTouchBegan(Touch* touch, Event* unused_event)
{
	auto Location = touch->getLocation();

	if (ballexist == false){
		addBall(Location);
		ballexist = true;
	}

	return true;
}

void inGame::onTouchMoved(Touch* touch, Event* unused_event)
{

}

void inGame::onTouchEnded(Touch* touch, Event* unused_event)
{

}

void inGame::addBall(Vec2 Location)
{
	ball = Sprite::createWithTexture(_ball, Rect(0, 0, 37, 37));
	ball->setPosition(Location);
	ball->setTag(0);
	ball->setName("ball");
	this->addChild(ball);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(Location.x / PTM_RATIO, Location.y / PTM_RATIO);
	bodyDef.userData = ball;

	b2Body* body = _world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 0.55f;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixtureDef.restitution = _restitution;

	body->CreateFixture(&fixtureDef);
}

void inGame::addWall(Vec2 Location, float angle, int data, bool rotation, bool left)
{
	Sprite* pSprite = Sprite::createWithTexture(_wall, Rect(0, 0, 98, 11));
	pSprite->setTag(data);
	pSprite->setColor(Color3B::GRAY);
	//pSprite->setColor(Color3B::GREEN);
	this->addChild(pSprite);

	b2BodyDef bodyDef;
	if (rotation)	bodyDef.type = b2_kinematicBody;
	else			bodyDef.type = b2_staticBody;
	bodyDef.position.Set(Location.x / PTM_RATIO, Location.y / PTM_RATIO);
	bodyDef.userData = pSprite;


	b2Body* body = _world->CreateBody(&bodyDef);

	b2PolygonShape wall;
	wall.SetAsBox((pSprite->getContentSize().width / 2) / PTM_RATIO, (pSprite->getContentSize().height / 2) / PTM_RATIO);

	//b2CircleShape circle;
	//circle.m_radius = 0.55f;

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &wall;
	fixtureDef.density = 1.0f;

	if (rotation){
		if (left)
			body->SetAngularVelocity(3.6);
		else
			body->SetAngularVelocity(-3.4);
	}

	body->SetTransform(b2Vec2(Location.x / PTM_RATIO, Location.y / PTM_RATIO), angle * DEGTORAD);
	body->CreateFixture(&fixtureDef);
}

void inGame::addDefense(Vec2 Location)
{
	auto defense = Sprite::create("defense.png");
	defense->setPosition(Vec2(Location.x, Location.y));
	this->addChild(defense);
	vDefense.push_back(defense);
}

void inGame::addWarp(Vec2 Location, bool entrance)
{
	auto warp = Sprite::create("warp.png");
	warp->setPosition(Vec2(Location.x, Location.y));
	if (entrance)	warp->setName("Entrance");
	else if (!entrance)	{
		warp->setName("Exit");
		warp->setFlipY(true);
	}
	this->addChild(warp);
}

void inGame::addGoal(Vec2 Location, float angle)
{
	auto polygon = Sprite::create("goal.png");
	polygon->setPosition(Vec2(Location.x, Location.y));
	polygon->setTag(49);
	polygon->setRotation(angle);
	this->addChild(polygon);
	goalpoint = Sprite::create("goalcol.png");
	goalpoint->setPosition(Vec2(polygon->getPosition().x, polygon->getPosition().y + 5));
	goalpoint->setTag(50);
	goalpoint->setRotation(angle);
	this->addChild(goalpoint);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(Location.x / PTM_RATIO, Location.y / PTM_RATIO);

	bodyDef.userData = nullptr;

	// 월드에 바디데프의 정보로 바디를 만든다.
	b2Body* body = _world->CreateBody(&bodyDef);
	body->SetTransform(b2Vec2(Location.x / PTM_RATIO, Location.y / PTM_RATIO), -(angle* DEGTORAD));

	BodyParser::getInstance()->parseJsonFile("goal.json");
	BodyParser::getInstance()->b2BodyJson(polygon, "Goal", body);
}

void inGame::addGravityGoal(Vec2 Location, float angle)
{
	auto polygon = Sprite::create("goal.png");
	polygon->setPosition(Vec2(Location.x, Location.y));
	polygon->setTag(49);
	polygon->setRotation(angle);
	this->addChild(polygon);
	gravitypoint = Sprite::create("goalcol.png");
	gravitypoint->setPosition(Vec2(polygon->getPosition().x, polygon->getPosition().y));
	gravitypoint->setTag(50);
	gravitypoint->setRotation(angle);
	this->addChild(gravitypoint);

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(Location.x / PTM_RATIO, Location.y / PTM_RATIO);

	bodyDef.userData = nullptr;

	// 월드에 바디데프의 정보로 바디를 만든다.
	b2Body* body = _world->CreateBody(&bodyDef);
	body->SetTransform(b2Vec2(Location.x / PTM_RATIO, Location.y / PTM_RATIO), angle * DEGTORAD);

	BodyParser::getInstance()->parseJsonFile("goal.json");
	BodyParser::getInstance()->b2BodyJson(polygon, "Goal", body);
}

void inGame::addMoveDefense(Vec2 Location)
{
	auto defense = Sprite::create("defense.png");
	defense->setPosition(Vec2(Location.x, Location.y));
	defense->setTag(7000);
	this->addChild(defense);
	vDefense.push_back(defense);
}

void inGame::MoveDefense(float dt)
{
	for (auto it : vDefense){
		if (it->getTag() == 7000 || it->getTag() == 7001){
			if (it->getTag() == 7000){
				it->setPosition(Vec2(it->getPosition().x - 5, it->getPosition().y));
				if (it->getPosition().x - (it->getContentSize().width / 2) <= 0){
					it->setTag(7001);
				}
			}
			else if (it->getTag() == 7001){
				it->setPosition(Vec2(it->getPosition().x + 5, it->getPosition().y));
				if (it->getPosition().x + (it->getContentSize().width / 2) >= 480){
					it->setTag(7000);
				}
			}
		}
	}
}