#pragma once

#include "GlobalDefine.h"
#include "Entity.h"

// Entity组装工厂：集中所有的Entity创建，方便管理
class EntityFactory
{
public:
	EntityFactory() = delete;

public:
	static sptr<Entity> CreateCamera();
	static sptr<Entity> CreatePlayer();
	static sptr<Entity> CreateMonster();

};