#pragma once
#include <string>
#include <SFML/Graphics.hpp>

#define DEBUG_ON

namespace Display
{
	void init();
	void clear();
	void display();

	void checkWindowEvents();

	bool isOpen();

	sf::RenderWindow& getWindow();

	const std::string TITLE = "Space Shooter";

#ifdef DEBUG_ON
	constexpr int WIDTH = 1024;
	constexpr int HEIGHT = 768;
#endif
}
