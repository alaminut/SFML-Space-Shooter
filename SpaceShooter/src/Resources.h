#pragma once
#include "managers/TextureManager.h"
#include "managers/FontManager.h"
#include "managers/SoundManager.h"

namespace Utils
{
	struct Resources
	{
		TextureManager textures;
		FontManager fonts;
		SoundManager audio;
	};
}
