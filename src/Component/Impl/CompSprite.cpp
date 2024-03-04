#include "CompSprite.h"

#include "../../Game/Game.h"
#include "../../Manager/Impl/ResourceManager.h"

void CompSprite::Load(const std::string& texPath, const vec2f& sizeInScreen)
{
    ResourceManager* resMgr = Game::GetManager<ResourceManager>();
    _pSprite = resMgr->CreateSpriteDrawable(texPath);

    // calculate scale
    vec2f textureSize = VecConvert<unsigned int, float>(_pSprite->getTexture()->getSize());
    vec2f scale = vec2f {
        sizeInScreen.x == 0 ? 1 : textureSize.x / sizeInScreen.x,
        sizeInScreen.y == 0 ? 1 : textureSize.y / sizeInScreen.y,
    };

    _pSprite->setScale(scale);
}

sf::Sprite* CompSprite::GetSprite()
{
    return _pSprite.get();
}

vec2f CompSprite::GetRenderSizeInScreenCoordinate()
{
    vec2f textureSize = VecConvert<unsigned int, float>(_pSprite->getTexture()->getSize());
    vec2f scale = _pSprite->getScale();

    return vec2f { 
        textureSize.x * abs(scale.x), 
        textureSize.y * abs(scale.y) 
        };
}