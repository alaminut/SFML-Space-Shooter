#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/Random.h"
#include "../entity/Player.h"
#include "GameState.h"

namespace State
{
	class Menu : public GameState
	{
	public:
		explicit Menu(Application& application);
		~Menu();

		void input() override;
		void update(const float dt) override;
		void draw() override;

	private:
		unsigned maxStars;

		sf::Text m_menuText;

		Utils::RandomNumberGenerator rng;

		GameObjects::Player* m_p_player;

		sf::Clock animationClock;

		std::vector<sf::CircleShape> stars;

		void FillBackground();
		void ClearObjects();
	};
}