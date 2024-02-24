#include "Player.h"

Player::Player(const std::string& pngPath)
{
	_playerTex.loadFromFile(pngPath);
	_playerSprite.setTexture(_playerTex);

	// put the origin point at the central of the player
	auto [texX, texY] = _playerTex.getSize();
	_playerSprite.setOrigin(0.5f * texX, 0.5f * texY);

	// entity properties
	_position = _playerSprite.getPosition();
	_size = _playerTex.getSize();
	_speed = 0;

}

auto Player::SetPosition(const sf::Vector2f& newPos) -> void
{
	_playerSprite.setPosition(newPos);

	// entity properties
	_position = newPos;
}

auto Player::GetPosition() const -> const sf::Vector2f& 
{ 
	return _position; 
}

auto Player::SetSize(const sf::Vector2u& size) -> void
{
	float widthScale = (float)size.x / _playerTex.getSize().x;
	float heightScale = (float)size.y / _playerTex.getSize().y;
	_playerSprite.setScale(widthScale, heightScale);

	// entity properties
	_size = size;
}

auto Player::GetSize() const -> const sf::Vector2u&
{
	return _size;
}

auto Player::SetFlip(bool doFlip) -> void
{
	auto [scaleX, scaleY] = _playerSprite.getScale();
	if ((doFlip && scaleX >= 0) || (!doFlip && scaleX <= 0))
		scaleX *= -1;

	_playerSprite.setScale(scaleX, scaleY);
}

auto Player::SetSpeed(float speed) -> void
{
	_speed = speed;
}

auto Player::GetSpeed() const -> float
{
	return _speed;
}

auto Player::GetDrawable() const -> const sf::Sprite&
{
	return _playerSprite;
}
