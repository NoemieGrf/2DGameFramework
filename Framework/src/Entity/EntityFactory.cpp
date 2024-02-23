#include "EntityFactory.h"
#include "RuntimeIdManager.h"
#include "CompGuid.h"
#include "CompCamera.h"
#include "CompRenderer.h"
#include "CompTransform.h"


sptr<Entity> EntityFactory::CreateCamera()
{
	sptr<Entity> pCamera = std::make_shared<Entity>();

	// comp guid
	pCamera->AddComponent(std::make_unique<CompGuid>(RuntimeIdManager::GetNextRuntimeId()));

	// comp camera
	pCamera->AddComponent(std::make_unique<CompCamera>());

	return pCamera;
}

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

	return pMonster;
}
