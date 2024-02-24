#pragma once

#include <string>
#include "../Game/GlobalDefine.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = delete;

public:
	static sptr<Entity> CreatePlayer();
	static sptr<Entity> CreateMonster();
	static sptr<Entity> CreateGadget(const std::string& pngPath);

};