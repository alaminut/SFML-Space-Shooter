#include "Splash.h"
#include "Menu.h"
#include "../Display.h"
#include "../Application.h"

State::Splash::Splash(Application& application) :
	GameState(application),
	splashDuration(5.f),
	animationDuration(.1f)
{
	float windowCenterH = Display::getWindow().getSize().x / 2.f;
	float windowCenterV = Display::getWindow().getSize().y / 2.f;

	this->m_logo.setTexture(this->getTexture(Shared::TextureId::TX_SPLASH_LOGO));
	this->m_logo.setColor(sf::Color(255, 255, 255, 0));
	this->m_logo.setPosition(windowCenterH - this->m_logo.getGlobalBounds().width / 2.f, windowCenterV - this->m_logo.getGlobalBounds().height / .5f);


	sf::Color yellow = sf::Color::Yellow;
	yellow.a = 0;

	this->m_brandText.setFont(this->getFont(Shared::FontId::F_UI));
	this->m_brandText.setFillColor(yellow);
	this->m_brandText.setCharacterSize(30);
	this->m_brandText.setString("CORE Interactive Games Presents");
	this->m_brandText.setPosition(windowCenterH - this->m_brandText.getGlobalBounds().width / 2, this->m_logo.getGlobalBounds().top + 100.f);

	this->m_splashClock.restart();
	this->m_animationClock.restart();
}

State::Splash::~Splash()
{
}

void State::Splash::input()
{
}

void State::Splash::update(const float dt)
{
	auto logoColor = this->m_logo.getColor();
	auto brandColor = this->m_brandText.getFillColor();

	if (this->m_animationClock.getElapsedTime().asSeconds() >= this->animationDuration && logoColor.a < 255)
	{
		logoColor.a += 15;
		brandColor.a += 15;

		this->m_logo.setColor(logoColor);
		this->m_brandText.setFillColor(brandColor);
		this->m_animationClock.restart();
	}

	if (this->m_splashClock.getElapsedTime().asSeconds() >= this->splashDuration)
	{
		this->m_p_application->changeState(std::make_unique<Menu>(*this->m_p_application));
	}
}

void State::Splash::draw()
{
	Display::getWindow().draw(this->m_logo);
	Display::getWindow().draw(this->m_brandText);
}
