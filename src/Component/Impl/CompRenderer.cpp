#include "CompRenderer.h"

CompRenderer::CompRenderer(const std::string& texPath)
{
	_texture.loadFromFile(texPath);
	_sprite.setTexture(_texture);
}

vec2f CompRenderer::GetRenderBound() const
{
	auto texSize = _texture.getSize();
	auto scale = _sprite.getScale();

	return vec2f {
		texSize.x * std::abs(scale.x),
		texSize.y * std::abs(scale.y)
	};
}

sf::Sprite& CompRenderer::GetSprite()
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
