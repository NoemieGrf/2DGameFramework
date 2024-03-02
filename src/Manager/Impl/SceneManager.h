#pragma once

#include "../GameManagerTypeGetter.h"
#include "../../Entity/Entity.h"
#include "../../Map/Map.h"

class SceneManager: public GameManagerTypeGetter<GameManagerType::Scene>
{
public:
    auto InitLevel() -> void;

public:
    auto GetEntity(uint guid) const -> Entity*;
    auto GetPlayerEntity() const -> Entity*;

private:
    auto InitMap() -> void;

private:
    // level mao
    Map _levelMap;

    // all entities in scene
	umap<uint, uptr<Entity>> _allEntitiesMap = {};

    // fast access cache
    uint _playerGuid;
};