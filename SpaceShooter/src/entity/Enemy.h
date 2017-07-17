#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../utils/Animation.h"
#include "../Resources.h"

namespace GameObjects
{
	class Enemy
	{
	public:
		explicit Enemy(
			sf::Texture const *texture,
			Utils::Resources const *resourceManager,
			sf::Vector2f position, float speed = 15.f);
		
		~Enemy();

		void Update(float const& dt);
		void Draw(sf::RenderTarget& target) const;

		//Accessors
		sf::Vector2f const& getPosition() const { return this->m_sprite.getPosition(); }
		sf::FloatRect getBoundingBox() const { return this->m_sprite.getGlobalBounds(); }

		int getCurrentHp() const { return this->hp; }
		int getTotalHp() const { return this->maxHp; }
		bool isDestroyed() const { return this->m_enemyDestorySound.getStatus() == sf::Sound::Stopped && this->exploding; }
		bool isDestroying() const { return this->exploding; }

		//Modifiers
		void TakeDamage(int amount);

	private:
		int hp;
		int maxHp;

		int dmgMin;
		int dmgMax;

		float speed;
		bool exploding;

		sf::Vector2f direction;
		sf::Sprite m_sprite;
		sf::RectangleShape m_healthBar;
		sf::Texture const *m_p_Texture;
		sf::Sound m_enemyDestorySound;

		Utils::Resources const *m_resourceManager;
		Utils::Animation m_moveAnimation;
		Utils::Animation m_deathAnimation;

		void Explode();
		void initAnimationFrames();
	};
}