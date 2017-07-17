#pragma once
#include <SFML/Graphics/Font.hpp>
#include "ResourceManager.h"
#include "../Shared.h"

namespace Utils
{
	class FontManager : public ResourceManager<Shared::FontId, sf::Font>
	{
	public:
		FontManager();
	};
}
