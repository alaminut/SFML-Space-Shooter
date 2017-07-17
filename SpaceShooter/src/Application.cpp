#include "Application.h"
#include "Display.h"

#ifdef DEBUG_ON
#include "states/Menu.h"
#else
#include "states/Splash.h"
#endif

Application::Application()
{
	Display::init();

#ifdef DEBUG_ON
	this->pushState(std::make_unique<State::Menu>(*this));
#else
	//Game starts with splash screen.
	this->pushState(std::make_unique<State::Splash>(*this));
#endif
}

Application::~Application()
{
}

void Application::runGameLoop()
{
	const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	sf::Time lastUpdate = sf::Time::Zero;
	sf::Clock frameClock;

	while (Display::isOpen())
	{
		Display::checkWindowEvents();

		Display::clear();

		this->m_states.top()->input();

		lastUpdate += frameClock.restart();
		while (lastUpdate > timePerFrame)
		{
			lastUpdate -= timePerFrame;
			this->m_states.top()->update(timePerFrame.asSeconds());
		}

		this->m_states.top()->draw();

		Display::display();
	}
}

void Application::pushState(std::unique_ptr<State::GameState> state)
{
	this->m_states.push(std::move(state));
}

void Application::popState()
{
	this->m_states.pop();
}

void Application::changeState(std::unique_ptr<State::GameState> state)
{
	this->popState();
	this->pushState(std::move(state));
}
