#include "EntityFactory.h"

#include "../Game/Game.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Utility/GuidGenerator.h"
#include "../Component/Impl/CompGuid.h"
#include "../Component/Impl/CompSpine.h"
#include "../Component/Impl/CompSprite.h"
#include "../Component/Impl/CompTransform.h"
#include "../Component/Impl/CompCollider.h"
#include "../Component/Impl/CompName.h"


std::pair<uint, uptr<Entity>> EntityFactory::CreatePlayer(
	const vec2f& initWorldPos, 
	const vec2f& sizeInWorld
	)
{
	ConfigManager* configMgr = Game::GetManager<ConfigManager>();
	uint guid = GuidGenerator::GetNextRuntimeId();
	uptr<Entity> pEntity = std::make_unique<Entity>();

	// comp guid
	auto pGuid = pEntity->AddComponent<CompGuid>();
	pGuid->SetGuid(guid);

	// comp name
	auto pName = pEntity->AddComponent<CompName>();
	pName->SetName("Player");

	// comp transform
	auto pTrans = pEntity->AddComponent<CompTransform>();
	pTrans->SetPosition(initWorldPos);

	// comp spine
	const auto pSpine = pEntity->AddComponent<CompSpine>();
	pSpine->Load(configMgr->GetPlayerSetting().spineName, sizeInWorld.x);

	// comp collider
	auto pCollider = pEntity->AddComponent<CompCollider>();
	pCollider->Init(true, sizeInWorld);

	return { guid, std::move(pEntity) };
}

std::pair<uint, uptr<Entity>> EntityFactory::CreateMonster(
	const vec2f& initWorldPos
	)
{
	uptr<Entity> pEntity = std::make_unique<Entity>();
	uint guid = GuidGenerator::GetNextRuntimeId();

	// comp guid
	const auto pGuid = pEntity->AddComponent<CompGuid>();
	pGuid->SetGuid(guid);

	// comp transform
	auto pTrans = pEntity->AddComponent<CompTransform>();
	pTrans->SetPosition(initWorldPos);

	return { guid, std::move(pEntity) };
}

std::pair<uint, uptr<Entity>> EntityFactory::CreateGadget(
	const std::string& pngPath, 
	const vec2f& initWorldPos, 
	const vec2f& sizeInWorld,
	const std::string& name
	)
{
	ConfigManager* configMgr = Game::GetManager<ConfigManager>();
	uint guid = GuidGenerator::GetNextRuntimeId();
	uptr<Entity> pEntity = std::make_unique<Entity>();

	// comp guid
	auto pGuid = pEntity->AddComponent<CompGuid>();
	pGuid->SetGuid(guid);

	// comp name
	auto pName = pEntity->AddComponent<CompName>();
	pName->SetName(name);

	// comp transform
	auto pTrans = pEntity->AddComponent<CompTransform>();
	pTrans->SetPosition(initWorldPos);

	// comp collider
	auto pCollider = pEntity->AddComponent<CompCollider>();
	pCollider->Init(false, sizeInWorld);

	// comp sprite
	auto pSprite = pEntity->AddComponent<CompSprite>();
	pSprite->Load(pngPath, sizeInWorld);

	return { guid, std::move(pEntity) };
}
