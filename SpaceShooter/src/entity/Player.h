#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <deque>
#include <queue>
#include "../Shared.h"
#include "../utils/Random.h"
#include "../Resources.h"
#include "Bullet.h"
#include "../utils/Animation.h"

namespace GameObjects
{
	class Player
	{
	public:
		explicit Player(sf::Texture const& texture, Utils::Resources const& resourceManager);
		~Player();

		void HandleInput(sf::Vector2u const& windowBounds);
		void Update(float const& dt, sf::Vector2u const& windowBounds);
		void Draw(sf::RenderTarget &target);
		void TakeDamage(int amount);
		void Destroy();

		//Member accessors
		std::deque<Bullet>& getBullets() { return this->m_bullets; }
		sf::Vector2f const& getPosition() const { return this->m_sprite.getPosition(); }
		sf::FloatRect getBoundingBox() const { return this->m_sprite.getGlobalBounds(); }

		//Scalar value accessors
		int getScore() const { return this->score; }
		int getCurrentHp() const { return this->hp; }
		int getTotalHp() const { return this->hpMax; }
		int getDamage() { return this->rng.getInt(this->damageMin, this->damageMax); }

		//level from xp formula: static_cast<int>(this->expConst * std::sqrt(this->exp))
		int getCurrentLevel() const { return this->level; }

		double getCurrentXp() const { return this->exp; }
		double getNextXp() const { return std::pow(static_cast<double>(this->level + 1), this->expConst); }

		//Returns true if player explosion sound is NOT playing.
		bool isDestoryComplete() const { return this->m_playerDeathSound.getStatus() == sf::Sound::Stopped; }
		bool isDestroyed() const { return this->hp <= 0; }

		//Modifiers
		void SetPosition(sf::Vector2f const& position) { this->m_sprite.setPosition(position); }
		void AddScore(int modifier);

	private:
		double exp;
		const double expConst;

		int score;
		int level;

		int hpMax;
		int hp;

		int damageMin;
		int damageMax;

		float shootTimerMax, shootTimer;
		float scaleX, scaleY;
		float dt;

		sf::Vector2f currentVelocity;
		sf::Vector2f direction;
		float maxVelocity;
		float acceleration;
		float stabilizerForce;

		Utils::RandomNumberGenerator rng;
		Utils::Resources const& m_resources;
		Utils::Animation m_idleAnimation;
		Utils::Animation m_explosionAnimation;

		sf::Sprite m_sprite;
		sf::RectangleShape m_healthBar;
		sf::Text m_levelDisplay;
		sf::Texture const& m_texture;
		sf::Sound m_playerDeathSound;

		std::deque<Bullet> m_bullets;
		std::queue<sf::Sound> m_bulletSounds;

		void InitAnimationSprites();
		void SpawnBullet(); //daha sonra bulletType parametresi eklenerek ozellestirilebilir.
		void LevelUp();
	};
}
