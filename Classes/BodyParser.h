#pragma once

#include "stdafx.h"

#define PTM_RATIO 32

class BodyParser {
	BodyParser(){}
	rapidjson::Document doc;
public:
	static BodyParser* getInstance();
	bool parseJsonFile(const std::string& pFile);
	bool parse(unsigned char* buffer, long length);
	void clearCache();
	PhysicsBody* physicsBodyJson(Node* pNode, const std::string& name, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
	void b2BodyJson(Node* pNode, const std::string& name, b2Body* body);
};