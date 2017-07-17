#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace State
{
	class Splash : public GameState
	{
	public:
		explicit Splash(Application& application);
		~Splash();

		void input() override;
		void update(const float dt) override;
		void draw() override;

	private:
		float splashDuration;
		float animationDuration;

		sf::Sprite m_logo;
		sf::Text m_brandText;

		sf::Clock m_animationClock;
		sf::Clock m_splashClock;
	};
}