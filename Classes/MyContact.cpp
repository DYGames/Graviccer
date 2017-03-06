#include "stdafx.h"
MyContact::MyContact() {
}

MyContact::~MyContact() {
}

void MyContact::BeginContact(b2Contact *contact)
{
	_Contact _contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	_vContact.push_back(_contact);
}

void MyContact::EndContact(b2Contact *contact)
{
	_Contact _contact = { contact->GetFixtureA(), contact->GetFixtureB() };
	vector<_Contact>::iterator pos;
	pos = find(_vContact.begin(), _vContact.end(), _contact);
	if (pos != _vContact.end()){
		_vContact.erase(pos);
	}
}

void MyContact::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{

}

void MyContact::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	SimpleAudioEngine::getInstance()->playEffect("bounce.wav");

	if ((bodyA->GetType() == b2_staticBody || bodyA->GetType() == b2_kinematicBody) && fixA->GetType() == b2Shape::e_polygon){
		auto a = ((Sprite*)bodyA->GetUserData());
		auto b = ((Sprite*)bodyB->GetUserData());
		if (a != NULL){
			for (int i = 0; i < singleton->_wallcount; i++){
				if (a->getTag() == i + 1){
					singleton->arraystage[singleton->stage][i] = true;
					a->setColor(Color3B::WHITE);
				}
			}
		}

	}
}