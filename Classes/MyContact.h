#pragma once

#include "stdafx.h"

struct _Contact{
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	bool operator == (const _Contact& other)const
	{
		return (fixtureA == other.fixtureA) && (fixtureB == other.fixtureB);
	}
};

class MyContact : public b2ContactListener{
public:
	vector<_Contact> _vContact;

	MyContact();
	~MyContact();

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
	
};