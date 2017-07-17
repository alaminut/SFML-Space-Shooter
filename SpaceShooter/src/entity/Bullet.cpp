#include "Bullet.h"

GameObjects::Bullet::Bullet(sf::Texture const *texture,
	sf::Vector2f position, sf::Vector2f direction,
	sf::Vector2f initialVelocity, float speed, float acceleration) :
	speed(speed),
	acceleration(acceleration),
	direction(direction),
	currentVelocity(initialVelocity),
	m_p_texture(texture)
{
	this->m_sprite.setTexture(*this->m_p_texture);

	auto textureCenterH = static_cast<float>(this->m_p_texture->getSize().x) / 2.f;
	auto textureCenterV = static_cast<float>(this->m_p_texture->getSize().y) / 2.f;

	this->m_sprite.setOrigin(textureCenterH, textureCenterV);
	this->m_sprite.setPosition(position);
}

GameObjects::Bullet::~Bullet()
{
}

void GameObjects::Bullet::Update(float const& dt)
{
	this->currentVelocity.x += this->direction.x * (this->speed + this->acceleration) * dt * 60.f;
	this->currentVelocity.y += this->direction.y * (this->speed + this->acceleration) * dt * 60.f;

	this->m_sprite.move(this->currentVelocity);
}

void GameObjects::Bullet::Draw(sf::RenderTarget& target) const
{
	target.draw(this->m_sprite);
}