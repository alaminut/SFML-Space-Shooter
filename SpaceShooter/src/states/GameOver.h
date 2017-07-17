#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace State
{
	class GameOver : public GameState
	{
	public:
		explicit GameOver(Application& application, int playerScore);
		~GameOver();

		void input() override;
		void update(const float dt) override;
		void draw() override;

	private:
		int m_playerScore;

		sf::Text m_gameOverText;
		sf::Text m_playerScoreText;
		sf::Text m_newGameText;
	};
}
