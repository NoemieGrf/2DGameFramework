#pragma once

#include "../Game/GlobalDefine.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = delete;

public:
	static sptr<Entity> CreateCamera();
	static sptr<Entity> CreatePlayer();
	static sptr<Entity> CreateMonster();

};