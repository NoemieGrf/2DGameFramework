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
	uptr<Component> pCompGuid = std::make_unique<CompGuid>(RuntimeIdManager::GetNextRuntimeId());
	pCamera->AddComponent(std::move(pCompGuid));

	// comp camera
	uptr<Component> pCompCamera = std::make_unique<CompCamera>();
	pCamera->AddComponent(std::move(pCompCamera));

	return pCamera;
}

sptr<Entity> EntityFactory::CreatePlayer()
{
	sptr<Entity> pPlayer = std::make_shared<Entity>();

	// comp guid
	uptr<Component> pCompGuid = std::make_unique<CompGuid>(RuntimeIdManager::GetNextRuntimeId());
	pPlayer->AddComponent(std::move(pCompGuid));

	// comp transform
	uptr<Component> pCompTrans = std::make_unique<CompTransform>();
	pPlayer->AddComponent(std::move(pCompTrans));

	// comp render
	uptr<Component> pCompRender = std::make_unique<CompRenderer>("./assets/player.png");
	pPlayer->AddComponent(std::move(pCompRender));

	return pPlayer;
}

sptr<Entity> EntityFactory::CreateMonster()
{
	sptr<Entity> pMonster = std::make_shared<Entity>();

	// comp guid
	uptr<Component> pCompGuid = std::make_unique<CompGuid>(RuntimeIdManager::GetNextRuntimeId());
	pMonster->AddComponent(std::move(pCompGuid));

	// comp transform
	uptr<Component> pCompTrans = std::make_unique<CompTransform>();
	pMonster->AddComponent(std::move(pCompTrans));

	// comp render
	uptr<Component> pCompRender = std::make_unique<CompRenderer>("./assets/monster0.png");
	pMonster->AddComponent(std::move(pCompRender));

	return pMonster;
}
