#include "EntityFactory.h"
#include "../Game/Game.h"
#include "../Manager/Impl/ConfigManager.h"
#include "../Utility/GuidGenerator.h"
#include "../Component/Impl/CompGuid.h"
#include "../Component/Impl/CompSpine.h"
#include "../Component/Impl/CompSprite.h"
#include "../Component/Impl/CompTransform.h"
#include <memory>


sptr<Entity> EntityFactory::CreatePlayer()
{
	ConfigManager* configMgr = Game::GetManager<ConfigManager>();
	sptr<Entity> pPlayer = std::make_shared<Entity>();

	// comp guid
	const auto pGuid = pPlayer->AddComponent<CompGuid>();
	pGuid->SetGuid(GuidGenerator::GetNextRuntimeId());

	// comp transform
	pPlayer->AddComponent<CompTransform>();

	// comp render
	const auto pRender = pPlayer->AddComponent<CompSpine>();
	pRender->Load(configMgr->GetPlayerSetting().spineName);

	return pPlayer;
}

sptr<Entity> EntityFactory::CreateMonster()
{
	sptr<Entity> pMonster = std::make_shared<Entity>();

	// comp guid
	const auto pGuid = pMonster->AddComponent<CompGuid>();
	pGuid->SetGuid(GuidGenerator::GetNextRuntimeId());

	// comp transform
	pMonster->AddComponent<CompTransform>();

	return pMonster;
}

sptr<Entity> EntityFactory::CreateGadget(const std::string& pngPath)
{
	sptr<Entity> pGadget = std::make_shared<Entity>();

	// comp guid
	const auto pGuid = pGadget->AddComponent<CompGuid>();
	pGuid->SetGuid(GuidGenerator::GetNextRuntimeId());

	// comp transform
	pGadget->AddComponent<CompTransform>();

	return pGadget;
}
