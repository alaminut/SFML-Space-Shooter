#include "Menu.h"
#include "Playing.h"
#include "../Display.h"
#include "../Application.h"

State::Menu::Menu(Application& application) :
	GameState(application),
	maxStars(200)
{
	//Create player
	this->m_p_player = new GameObjects::Player(this->getTexture(Shared::TextureId::TX_PLAYER), this->getResourceManager());
	this->m_p_player->SetPosition(sf::Vector2f(0.f, 50.f));

	//Create background
	this->FillBackground();

	//Create text
	sf::Color textColor = sf::Color::Yellow;
	textColor.a = 0;

	this->m_menuText.setFont(this->getFont(Shared::FontId::F_UI));
	this->m_menuText.setFillColor(textColor);
	this->m_menuText.setString("PRESS 'spacebar' TO START");
	this->m_menuText.setPosition(Display::getWindow().getSize().x / 2.f - this->m_menuText.getGlobalBounds().width / 2.f, Display::getWindow().getSize().y / 2.f - 50.f);

	this->animationClock.restart();
}

State::Menu::~Menu()
{
	delete this->m_p_player;
}

void State::Menu::input()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		this->m_p_application->changeState(std::make_unique<Playing>(*this->m_p_application));
	}
}

void State::Menu::update(const float dt)
{
	//Update background objects
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		float x = this->rng.getFloat(0.f, 2.f);
		(*it).move(-1.f * x * dt * 60.f, 0.f);
	}

	//Update player
	this->m_p_player->Update(dt, Display::getWindow().getSize());

	//Animate text
	if(this->animationClock.getElapsedTime().asSeconds() >= .1f)
	{
		auto color = this->m_menuText.getFillColor();
		color.a += 35;

		this->m_menuText.setFillColor(color);
		this->animationClock.restart();
	}

	this->ClearObjects();
}

void State::Menu::draw()
{
	//Draw background objects
	sf::RenderStates renderOptions(sf::BlendAlpha);
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		Display::getWindow().draw((*it), renderOptions);
	}

	this->m_p_player->Draw(Display::getWindow());

	Display::getWindow().draw(this->m_menuText);
}

void State::Menu::FillBackground()
{
	float maxX = static_cast<float>(Display::getWindow().getSize().x);
	float maxY = static_cast<float>(Display::getWindow().getSize().y);

	for (unsigned i = this->stars.size(); i < this->maxStars; i++)
	{
		sf::CircleShape star(this->rng.getFloat(0.3f, 1.5f));
		star.setFillColor(sf::Color::White);

		star.setPosition(this->rng.getFloat(0.f, maxX), this->rng.getFloat(0.f, maxY));
		this->stars.push_back(star);
	}
}

void State::Menu::ClearObjects()
{
	//Background objects GC
	for (auto it = this->stars.begin(); it != this->stars.end(); ++it)
	{
		if ((*it).getPosition().x < -10.f)
		{
			this->stars.erase(it);
			this->FillBackground();
			break;
		}
	}
}