#include "Player.h"

Player::Player(const std::string& pngPath)
{
	_playerTex.loadFromFile(pngPath);
	_playerSprite.setTexture(_playerTex);

	auto [texX, texY] = _playerTex.getSize();
	_playerSprite.setOrigin(0.5f * texX, 0.5f * texY);
}

auto Player::SetSize(float widthSize, float heightSize) -> void
{
	float widthScale = widthSize / _playerTex.getSize().x;
	float heightScale = heightSize / _playerTex.getSize().y;
	_playerSprite.setScale(widthScale, heightScale);
}

auto Player::GetSize() const -> sf::Vector2f
{
	auto [scaleX, scaleY] = _playerSprite.getScale();
	auto [sizeX, sizeY] = _playerTex.getSize();
	return { std::abs(scaleX) * sizeX, scaleY * sizeY };
}

auto Player::SetPosition(const sf::Vector2f& newPos) -> void
{
	_playerSprite.setPosition(newPos);
}

auto Player::GetPosition() const -> const sf::Vector2f&
{
	return _playerSprite.getPosition();
}

auto Player::SetFlip(bool doFlip) -> void
{
	auto [scaleX, scaleY] = _playerSprite.getScale();
	if ((doFlip && scaleX >= 0) || (!doFlip && scaleX <= 0))
		scaleX *= -1;

	_playerSprite.setScale(scaleX, scaleY);
}

auto Player::Render(sf::RenderWindow& rdWindow) -> void
{
	rdWindow.draw(_playerSprite);
}
