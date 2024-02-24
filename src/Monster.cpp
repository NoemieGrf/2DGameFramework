#include "Monster.h"

Monster::Monster(const std::string& pngPath, uint id) : _id(id)
{
	_monsterTex.loadFromFile(pngPath);
	_monsterSprite.setTexture(_monsterTex);

	// put the origin point at the central of the monster
	auto [texX, texY] = _monsterTex.getSize();
	_monsterSprite.setOrigin(0.5f * texX, 0.5f * texY);

	// entity properties
	_position = _monsterSprite.getPosition();
	_size = _monsterTex.getSize();
	_speed = 0;

}

auto Monster::GetId() const -> uint
{
	return _id;
}

auto Monster::SetPosition(const sf::Vector2f& newPos) -> void
{
	_monsterSprite.setPosition(newPos);

	// entity properties
	_position = newPos;
}

auto Monster::GetPosition() const -> const sf::Vector2f&
{
	return _position;
}

auto Monster::SetSize(const sf::Vector2u& size) -> void
{
	float widthScale = (float)size.x / _monsterTex.getSize().x;
	float heightScale = (float)size.y / _monsterTex.getSize().y;
	_monsterSprite.setScale(widthScale, heightScale);

	// entity properties
	_size = size;
}

auto Monster::GetSize() const -> const sf::Vector2u&
{
	return _size;
}

auto Monster::SetFlip(bool doFlip) -> void
{
	auto [scaleX, scaleY] = _monsterSprite.getScale();
	if ((doFlip && scaleX >= 0) || (!doFlip && scaleX <= 0))
		scaleX *= -1;

	_monsterSprite.setScale(scaleX, scaleY);
}

auto Monster::SetSpeed(float speed) -> void
{
	_speed = speed;
}

auto Monster::GetSpeed() const -> float
{
	return _speed;
}

auto Monster::GetDrawable() const -> const sf::Sprite&
{
	return _monsterSprite;
}
