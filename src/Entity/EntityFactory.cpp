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
#include "Config/AnimationSetting.h"


std::pair<uint, uptr<Entity>> EntityFactory::CreatePlayer(
	const vec2f& initWorldPos, 
	const vec2f& sizeInWorld,
	const PhysicsFixture& fixture
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
	const std::string& playerAnimatorName = configMgr->GetPlayerSetting().animatorName;
	const AnimatorConfig* pAnimatorConfig = configMgr->GetAnimationSetting().GetAnimatorConfig(playerAnimatorName);
	auto pSpine = pEntity->AddComponent<CompSpine>();
	pSpine->Load(configMgr->GetPlayerSetting().spineName, sizeInWorld.x, pAnimatorConfig);

	pSpine->Load(configMgr->GetPlayerSetting().spineName, sizeInWorld.x, pAnimatorConfig);

	// comp collider
	auto pCollider = pEntity->AddComponent<CompCollider>();
	vec2f aabbBox = vec2f {
		sizeInWorld.x * 0.7f,	// 角色的碰撞稍微小一点
		sizeInWorld.y
	};
	pCollider->Init(true, aabbBox, fixture);

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
	const std::string& name,
	const PhysicsFixture& fixture
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
	pCollider->Init(false, sizeInWorld, fixture);

	// comp sprite
	auto pSprite = pEntity->AddComponent<CompSprite>();
	pSprite->Load(pngPath, sizeInWorld);

	return { guid, std::move(pEntity) };
}
