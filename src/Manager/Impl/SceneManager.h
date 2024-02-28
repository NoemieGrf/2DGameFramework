#pragma once

#include "../GameManagerTypeGetter.h"
#include "../../Entity/Entity.h"

class SceneManager: public GameManagerTypeGetter<GameManagerType::Scene>
{
public:
    auto InitLevel() -> void;

public:
    auto GetEntity(uint guid) const -> Entity*;
    auto GetPlayerEntity() const -> Entity*;

private:
    // all entities in scene
	umap<uint, uptr<Entity>> _allEntitiesMap = {};

    // fast access cache
    uint _playerGuid;
};