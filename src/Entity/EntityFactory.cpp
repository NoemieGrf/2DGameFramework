#include "EntityFactory.h"

#include "../Game/Game.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Utility/GuidGenerator.h"
#include "../Component/Impl/CompGuid.h"
#include "../Component/Impl/CompSpine.h"
#include "../Component/Impl/CompSprite.h"
#include "../Component/Impl/CompTransform.h"
#include "../Component/Impl/CompCollider.h"


std::pair<uint, uptr<Entity>> EntityFactory::CreatePlayer(const vec2f& initWorldPos)
{
	ConfigManager* configMgr = Game::GetManager<ConfigManager>();
	uint guid = GuidGenerator::GetNextRuntimeId();
	uptr<Entity> pEntity = std::make_unique<Entity>();

	// comp guid
	const auto pGuid = pEntity->AddComponent<CompGuid>();
	pGuid->SetGuid(guid);

	// comp transform
	auto pTrans = pEntity->AddComponent<CompTransform>();
	pTrans->SetPosition(initWorldPos);

	// comp render
	const auto pRender = pEntity->AddComponent<CompSpine>();
	pRender->Load(configMgr->GetPlayerSetting().spineName);

	return { guid, std::move(pEntity) };
}

std::pair<uint, uptr<Entity>> EntityFactory::CreateMonster(const vec2f& initWorldPos)
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

std::pair<uint, uptr<Entity>> EntityFactory::CreateGadget(const std::string& pngPath, const vec2f& initWorldPos)
{
	uptr<Entity> pEntity = std::make_unique<Entity>();
	uint guid = GuidGenerator::GetNextRuntimeId();

	// comp guid
	auto pGuid = pEntity->AddComponent<CompGuid>();
	pGuid->SetGuid(guid);

	// comp transform
	auto pTrans = pEntity->AddComponent<CompTransform>();
	pTrans->SetPosition(initWorldPos);

	// comp collider
	auto pCollider = pEntity->AddComponent<CompCollider>();
	pCollider->Init(false, vec2f {1, 1});

	return { guid, std::move(pEntity) };
}
