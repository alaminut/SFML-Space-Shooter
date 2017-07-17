#pragma once
#include <SFML/Graphics.hpp>

namespace GameObjects
{
	class Bullet
	{
	public:
		explicit Bullet(
			sf::Texture const *texture,
			sf::Vector2f position,
			sf::Vector2f direction,
			sf::Vector2f initialVelocity = sf::Vector2f(0, 0),
			float speed = 15.f,
			float acceleration = 0.f);

		~Bullet();

		void Update(float const& dt);
		void Draw(sf::RenderTarget &target) const;

		//Accessors
		sf::FloatRect getBoundingBox() const { return this->m_sprite.getGlobalBounds(); }
		sf::Vector2f const& getPosition() const { return this->m_sprite.getPosition(); }

	protected:
		float speed;
		float acceleration;

		sf::Vector2f direction;
		sf::Vector2f currentVelocity;
		
		sf::Texture const *m_p_texture;
		sf::Sprite m_sprite;
	};
}
