#include "CompSprite.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ResourceManager.h"

void CompSprite::Load(const std::string& texPath)
{
    ResourceManager* resMgr = Game::GetManager<ResourceManager>();
    _pSprite = resMgr->CreateSpriteDrawable(texPath);
}

sf::Sprite* CompSprite::GetSprite()
{
    return _pSprite.get();
}