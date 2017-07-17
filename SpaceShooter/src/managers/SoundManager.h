#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.h"
#include "../Shared.h"

namespace Utils
{
	class SoundManager : public ResourceManager<Shared::SoundId, sf::SoundBuffer>
	{
	public:
		SoundManager();

	};
}