#include "Player.h"

GameObjects::Player::Player(sf::Texture const& texture, Utils::Resources const& resourceManager) :
	exp(0.0),
	expConst(0.04),
	score(0),
	level(1),
	hpMax(level * 100),
	hp(hpMax),
	damageMin(level * 5),
	damageMax(level * 15),
	shootTimerMax(8.f),
	shootTimer(shootTimerMax),
	scaleX(0.15f),
	scaleY(0.15f),
	dt(0.f),
	maxVelocity(10.f),
	acceleration(0.8f),
	stabilizerForce(0.4f),
	m_resources(resourceManager),
	m_texture(texture)
{
	//player icin verilen texture'i uygula
	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setScale(this->scaleX, this->scaleY);

	//Player hp bar
	this->m_healthBar.setSize(sf::Vector2f(this->m_sprite.getGlobalBounds().width, 2.f));
	this->m_healthBar.setFillColor(sf::Color::Red);

	//Player level display
	this->m_levelDisplay.setFont(this->m_resources.fonts.getResource(Shared::FontId::F_UI));
	this->m_levelDisplay.setFillColor(sf::Color::Yellow);
	this->m_levelDisplay.setCharacterSize(16);

	//player death sound
	this->m_playerDeathSound.setBuffer(this->m_resources.audio.getResource(Shared::SoundId::S_PLAYER_DEATH));
	this->m_playerDeathSound.setVolume(Shared::EFFECT_VOLUME);
	this->m_playerDeathSound.setLoop(false);
}

GameObjects::Player::~Player()
{

}

void GameObjects::Player::HandleInput(sf::Vector2u const& windowBounds)
{
	//UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->direction.x = 0.f;
		this->direction.y = -1.f;

		if (this->currentVelocity.y > -this->maxVelocity && this->direction.y < 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}

	//DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		this->direction.x = 0.f;
		this->direction.y = 1.f;

		if (this->currentVelocity.y < this->maxVelocity && this->direction.y > 0)
			this->currentVelocity.y += this->direction.y * this->acceleration;
	}

	//LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		this->direction.x = -1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x > -this->maxVelocity && this->direction.x < 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	//RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		this->direction.x = 1.f;
		this->direction.y = 0.f;

		if (this->currentVelocity.x < this->maxVelocity && this->direction.x > 0)
			this->currentVelocity.x += this->direction.x * this->acceleration;
	}

	//SHOOT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->shootTimer >= this->shootTimerMax)
	{
		this->SpawnBullet();
		this->shootTimer = 0.f;
	}

	//STABILIZER
	if (this->currentVelocity.x > 0.f)
	{
		this->currentVelocity.x -= this->stabilizerForce;

		if (this->currentVelocity.x < 0.f)
			this->currentVelocity.x = 0.f;

	}
	else if (this->currentVelocity.x < 0.f)
	{
		this->currentVelocity.x += this->stabilizerForce;
	}

	if (this->currentVelocity.y > 0.f)
	{
		this->currentVelocity.y -= this->stabilizerForce;

		if (this->currentVelocity.y < 0.f)
			this->currentVelocity.y = 0.f;

	}
	else if (this->currentVelocity.y < 0.f)
	{
		this->currentVelocity.y += this->stabilizerForce;
	}

	//WINDOW BOUNDARY CHECK
	sf::Vector2f currentPosition = this->m_sprite.getPosition() + this->currentVelocity;
	float maxX = static_cast<float>(windowBounds.x) - this->getBoundingBox().width;
	float maxY = static_cast<float>(windowBounds.y) - this->getBoundingBox().height;

	if (currentPosition.x < 0.f)
		this->currentVelocity.x = 0.f;

	if (currentPosition.x > maxX)
		this->currentVelocity.x = 0.f;

	if (currentPosition.y < 50.f)
		this->currentVelocity.y = 0.f;

	if (currentPosition.y > maxY)
		this->currentVelocity.y = 0.f;

	//Apply movement
	this->m_sprite.move(this->currentVelocity * this->dt * 60.f);
}

void GameObjects::Player::Update(float const& dt, sf::Vector2u const& windowBounds)
{
	this->dt = dt;

	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer += 1.f * this->dt * 60.f;

	//Set health bar position
	this->m_healthBar.setPosition(this->m_sprite.getPosition().x, this->m_sprite.getPosition().y);

	//Set level display position
	this->m_levelDisplay.setPosition(
		this->m_healthBar.getPosition().x,
		this->m_healthBar.getPosition().y - (this->m_levelDisplay.getGlobalBounds().height + this->m_healthBar.getGlobalBounds().height) - 5.f);

	this->m_levelDisplay.setString("Level: " + std::to_string(this->level));

	//Update bullets
	for (auto it = this->m_bullets.begin(); it != this->m_bullets.end(); ++it)
	{
		(*it).Update(this->dt);
	}

	//Clear bullet audio
	if (!this->m_bulletSounds.empty())
	{
		if (this->m_bulletSounds.front().getStatus() == sf::Sound::Stopped)
		{
			this->m_bulletSounds.pop();
		}
	}
}

void GameObjects::Player::Draw(sf::RenderTarget &target)
{
	//Draw bullets
	if (!this->m_bullets.empty())
	{
		for (auto it = this->m_bullets.begin(); it != this->m_bullets.end(); ++it)
		{
			(*it).Draw(target);
		}
	}

	target.draw(this->m_sprite);
	target.draw(this->m_healthBar);
	target.draw(this->m_levelDisplay);
}

void GameObjects::Player::TakeDamage(int amount)
{
	this->hp -= amount;

	if (this->hp < 0)
		this->hp = 0;

	float hpSize = (static_cast<float>(this->hp) / static_cast<float>(this->hpMax)) * this->m_sprite.getGlobalBounds().width;
	this->m_healthBar.setSize(sf::Vector2f(hpSize, 2.f));
}

void GameObjects::Player::Destroy()
{
	this->m_playerDeathSound.play();
}

void GameObjects::Player::AddScore(int modifier)
{
	this->score += modifier;
	if (this->level < Shared::LEVEL_CAP)
	{
		double enemyXp = std::pow(static_cast<double>(modifier), this->expConst);
		double gainXp = enemyXp / static_cast<double>(modifier);

		this->exp = this->exp + gainXp;
		if (this->exp >= this->getNextXp())
			this->LevelUp();
	}
}


void GameObjects::Player::SpawnBullet()
{
	sf::FloatRect boundingBox = this->m_sprite.getGlobalBounds();
	sf::Vector2f center = sf::Vector2f(
		boundingBox.left + boundingBox.width,
		boundingBox.top + boundingBox.height / 2);

	this->m_bullets.emplace_front(&this->m_resources.textures.getResource(Shared::TextureId::TX_LASER), center, sf::Vector2f(1.f, 0), sf::Vector2f(0, 0), 5.f);
	this->m_bulletSounds.emplace(this->m_resources.audio.getResource(Shared::SoundId::S_LASER));

	this->m_bulletSounds.front().setLoop(false);
	this->m_bulletSounds.front().setVolume(Shared::EFFECT_VOLUME);
	this->m_bulletSounds.front().play();
}

void GameObjects::Player::LevelUp()
{
	this->level++;
	this->exp = 0.0;
	
	//update hp
	this->hpMax = this->level * 100;
	this->hp = this->hpMax;
	
	//update damage
	this->damageMin = this->level * 5;
	this->damageMax = this->level * 15;
}

