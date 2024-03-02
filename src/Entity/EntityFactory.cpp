#include "EntityFactory.h"
#include "../Game/Game.h"
#include "../Utility/GuidGenerator.h"
#include "../Component/Impl/CompGuid.h"
#include "../Component/Impl/CompRenderer.h"
#include "../Component/Impl/CompTransform.h"
#include <memory>


sptr<Entity> EntityFactory::CreatePlayer()
{
	sptr<Entity> pPlayer = std::make_shared<Entity>();

	// comp guid
	const auto pGuid = pPlayer->AddComponent<CompGuid>();
	pGuid->SetGuid(GuidGenerator::GetNextRuntimeId());

	// comp transform
	pPlayer->AddComponent<CompTransform>();

	// comp render
	const auto pRender = pPlayer->AddComponent<CompRenderer>();
	pRender->LoadTexture("./assets/player.png");

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

	// comp render
	const auto pRender = pMonster->AddComponent<CompRenderer>();
	pRender->LoadTexture("./assets/monster0.png");

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

	// comp render
	const auto pRender = pGadget->AddComponent<CompRenderer>();
	pRender->LoadTexture(pngPath);

	return pGadget;
}
