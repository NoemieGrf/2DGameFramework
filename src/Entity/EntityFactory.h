#pragma once

#include <string>
#include "../Game/GlobalDefine.h"
#include "Entity.h"

class EntityFactory
{
public:
	EntityFactory() = delete;

public:
	static std::pair<uint, uptr<Entity>> CreatePlayer(const vec2f& initWorldPos);
	static std::pair<uint, uptr<Entity>> CreateMonster(const vec2f& initWorldPos);
	static std::pair<uint, uptr<Entity>> CreateGadget(const std::string& pngPath, const vec2f& initWorldPos);

};