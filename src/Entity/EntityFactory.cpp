#include "EntityFactory.h"
#include "../Game/Game.h"
#include "../Game/RuntimeIdManager.h"
#include "../Component/Impl/CompGuid.h"
#include "../Component/Impl/CompRenderer.h"
#include "../Component/Impl/CompTransform.h"
#include "../Component/Impl/CompAi.h"
#include "../AI/TacticDirectChasing.h"
#include <memory>


sptr<Entity> EntityFactory::CreatePlayer()
{
	sptr<Entity> pPlayer = std::make_shared<Entity>();

	// comp guid
	pPlayer->AddComponent(std::make_unique<CompGuid>(RuntimeIdManager::GetNextRuntimeId()));

	// comp transform
	pPlayer->AddComponent(std::make_unique<CompTransform>());

	// comp render
	pPlayer->AddComponent(std::make_unique<CompRenderer>("./assets/player.png"));

	return pPlayer;
}

sptr<Entity> EntityFactory::CreateMonster()
{
	sptr<Entity> pMonster = std::make_shared<Entity>();

	// comp guid
	pMonster->AddComponent(std::make_unique<CompGuid>(RuntimeIdManager::GetNextRuntimeId()));

	// comp transform
	pMonster->AddComponent(std::make_unique<CompTransform>());

	// comp render
	pMonster->AddComponent(std::make_unique<CompRenderer>("./assets/monster0.png"));

	// comp ai
	uptr<TacticDirectChasing> pChasingTactic = std::make_unique<TacticDirectChasing>();
	pChasingTactic->SetChasingTarget(Game::GetInstance()->GetPlayerEntity());
	pMonster->AddComponent(std::make_unique<CompAi>(std::move(pChasingTactic)));

	return pMonster;
}
