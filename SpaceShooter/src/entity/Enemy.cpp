#include "Enemy.h"

GameObjects::Enemy::Enemy(int level, sf::Texture const *texture, Utils::Resources const *resourceManager, sf::Vector2f position, float speed) :
	level(level),
	maxHp(level * 50),
	hp(maxHp),
	dmgMin(level * 10),
	dmgMax(level * 25),
	speed(speed),
	exploding(false),
	direction(sf::Vector2f(-1.f, 0.f)),
	m_p_Texture(texture),
	m_resourceManager(resourceManager)
{
	this->m_sprite.setTexture(*this->m_p_Texture);
	this->m_sprite.setScale(.16f, .16f);
	this->m_sprite.setPosition(position);

	this->m_BoundingBox.setFillColor(sf::Color::Transparent);
	this->m_BoundingBox.setOutlineColor(sf::Color::Red);
	this->m_BoundingBox.setOutlineThickness(1.f);

	this->m_healthBar.setSize(sf::Vector2f(200.f * .16f, 2.f));
	this->m_healthBar.setFillColor(sf::Color::Red);

	this->m_enemyDestorySound.setBuffer(this->m_resourceManager->audio.getResource(Shared::SoundId::S_ENEMY_DEATH));
	this->m_enemyDestorySound.setVolume(Shared::EFFECT_VOLUME);
	this->m_enemyDestorySound.setLoop(false);

	this->initAnimationFrames();
}

GameObjects::Enemy::~Enemy()
{
}

void GameObjects::Enemy::Update(float const& dt)
{
	auto animationFrame = this->exploding ?
		this->m_deathAnimation.getFrame() :
		this->m_moveAnimation.getFrame();

	this->m_sprite.setTextureRect(animationFrame);

	sf::Vector2f pos(this->direction.x * this->speed * dt * 60.f, this->direction.y * this->speed * dt * 60.f);
	this->m_sprite.move(pos);

	this->m_BoundingBox.setSize(sf::Vector2f(this->getBoundingBox().width, this->getBoundingBox().height));
	this->m_BoundingBox.setPosition(this->m_sprite.getPosition().x, this->m_sprite.getPosition().y);

	this->m_healthBar.setPosition(this->m_sprite.getPosition().x, this->m_sprite.getPosition().y - 2.f);
}

void GameObjects::Enemy::Draw(sf::RenderTarget& target) const
{
	target.draw(this->m_healthBar);
	target.draw(this->m_sprite);

	//target.draw(this->m_BoundingBox);
}

void GameObjects::Enemy::TakeDamage(int amount)
{
	if (this->exploding) return;

	this->hp -= amount;

	if (this->hp < 0)
		this->hp = 0;

	float hpPercent = std::max<float>(0.f, (static_cast<float>(this->hp) / static_cast<float>(this->maxHp)) * 200.f * .16f);
	this->m_healthBar.setSize(sf::Vector2f(hpPercent, 2.f));

	if (this->hp == 0)
		this->Explode();
}

void GameObjects::Enemy::Explode()
{
	this->m_enemyDestorySound.play();
	this->exploding = true;
}


void GameObjects::Enemy::initAnimationFrames()
{
	//move animation forward
	this->m_moveAnimation.addFrame(sf::IntRect(0, 0, 1000, 550), .1f);
	this->m_moveAnimation.addFrame(sf::IntRect(1000, 0, 1000, 550), .1f);
	this->m_moveAnimation.addFrame(sf::IntRect(2000, 0, 1000, 550), .1f);
	this->m_moveAnimation.addFrame(sf::IntRect(3000, 0, 1000, 550), .1f);
	this->m_moveAnimation.addFrame(sf::IntRect(4000, 0, 1000, 550), .1f);

	//move animation backward
	this->m_moveAnimation.addFrame(sf::IntRect(3000, 0, 1000, 550), .1f);
	this->m_moveAnimation.addFrame(sf::IntRect(2000, 0, 1000, 550), .1f);
	this->m_moveAnimation.addFrame(sf::IntRect(1000, 0, 1000, 550), .1f);

	//death animation
	this->m_deathAnimation.addFrame(sf::IntRect(0, 600, 1000, 550), .2f);
	this->m_deathAnimation.addFrame(sf::IntRect(1000, 600, 1000, 550), .2f);
	this->m_deathAnimation.addFrame(sf::IntRect(2000, 600, 1000, 550), .2f);
	this->m_deathAnimation.addFrame(sf::IntRect(3000, 600, 1000, 550), .2f);
	this->m_deathAnimation.addFrame(sf::IntRect(4000, 600, 1000, 550), .2f);
	this->m_deathAnimation.addFrame(sf::IntRect(0, 0, 0, 0), 0.f);
}
