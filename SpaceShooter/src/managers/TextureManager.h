#pragma once
#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.h"
#include "../Shared.h"

namespace Utils
{
	class TextureManager : public ResourceManager<Shared::TextureId, sf::Texture>
	{
	public:
		TextureManager();
	};
}