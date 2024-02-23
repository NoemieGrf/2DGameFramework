#pragma once

#include "GlobalDefine.h"
#include "Entity.h"

// Entity��װ�������������е�Entity�������������
class EntityFactory
{
public:
	EntityFactory() = delete;

public:
	static sptr<Entity> CreateCamera();
	static sptr<Entity> CreatePlayer();
	static sptr<Entity> CreateMonster();

};