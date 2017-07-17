#include "UI.h"
#include "../Display.h"

GameObjects::UI::UI(sf::Font const& uiFont) :
	m_uiFont(uiFont)
{
	this->m_scoreDisplay.setFont(this->m_uiFont);
	this->m_scoreDisplay.setFillColor(sf::Color::Yellow);
	this->m_scoreDisplay.setCharacterSize(25);
	this->m_scoreDisplay.setPosition(5.f, 5.f);
}

GameObjects::UI::~UI()
{
}

void GameObjects::UI::update(int playerScore, int playerHp, const float dt)
{
	std::string uiString("HP: " + std::to_string(playerHp) + "    SCORE: " + std::to_string(playerScore));
	this->m_scoreDisplay.setString(uiString);
}

void GameObjects::UI::draw() const
{
	Display::getWindow().draw(this->m_scoreDisplay);
}
