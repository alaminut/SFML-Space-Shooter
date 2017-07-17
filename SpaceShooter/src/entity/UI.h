#pragma once
#include <SFML/Graphics.hpp>

namespace GameObjects
{
	class UI
	{
	public:
		explicit UI(sf::Font const& uiFont);
		~UI();

		void update(int playerScore, int playerHp, const float dt);
		void draw() const;

	private:
		sf::Font m_uiFont;
		sf::Text m_scoreDisplay;
	};
}