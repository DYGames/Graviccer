#pragma once

#include "stdafx.h"

class Singleton
{
private:
	static Singleton* m_uInstance;
public:
	Singleton(){}
	~Singleton(){delete m_uInstance;}
	static Singleton* getInstance();

public:
	bool arraystage[6][10];

	int stage = 2;

	int _wallcount;
};