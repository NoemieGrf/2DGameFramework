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

vec2f CompSprite::GetRenderSizeInScreenCoordinate() const
{
    vec2f textureSize = VecConvert<unsigned int, float>(_pSprite->getTexture()->getSize());
    vec2f scale = _pSprite->getScale();

    return vec2f { 
        textureSize.x * abs(scale.x), 
        textureSize.y * abs(scale.y) 
        };
}

sf::Drawable* CompSprite::GetSfmlDrawable() const
{
    return _pSprite.get();
}

void CompSprite::SetSfmlDrawableScreenCoordinate(const vec2f& coord)
{
    _pSprite->setPosition(coord);
}