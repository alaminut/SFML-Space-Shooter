#include "Display.h"
#include <memory>

namespace Display
{

	std::unique_ptr<sf::RenderWindow> window;

	void init()
	{

#ifdef DEBUG_ON
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH, HEIGHT), TITLE, sf::Style::Close);
#else
		window = std::make_unique<sf::RenderWindow>(sf::VideoMode::getDesktopMode(), TITLE, sf::Style::Fullscreen);
#endif

		window->setFramerateLimit(60);
		window->setMouseCursorVisible(false);
	}

	void clear()
	{
		window->clear();
	}

	void display()
	{
		window->display();
	}

	void checkWindowEvents()
	{
		sf::Event e;
		while(window->pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window->close();

			if(e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Key::Escape)
					window->close();
			}
		}
	}

	bool isOpen()
	{
		return window->isOpen();
	}

	sf::RenderWindow& getWindow()
	{
		return *window;
	}
}
