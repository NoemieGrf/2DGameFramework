#include "CompRenderer.h"

CompRenderer::CompRenderer(const std::string& texPath)
{
	_texture.loadFromFile(texPath);
	_sprite.setTexture(_texture);
}

const sf::Sprite& CompRenderer::GetSprite() const
{
	return _sprite;
}

void CompRenderer::SetFlip(bool doFlip)
{
	auto [scaleX, scaleY] = _sprite.getScale();
	if ((doFlip && scaleX >= 0) || (!doFlip && scaleX <= 0))
		scaleX *= -1;

	_sprite.setScale(scaleX, scaleY);
}
