#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Resources.h"

class Application;

namespace State
{
	class GameState
	{
	public:
		explicit GameState(Application& application);
		virtual ~GameState();

		virtual void input() = 0;
		virtual void update(const float dt) = 0;
		virtual void draw() = 0;

	protected:
		Application* m_p_application;
		sf::Sound m_sceneAudio;

		sf::Texture const& getTexture(const Shared::TextureId textureId) const;
		sf::Font const& getFont(const Shared::FontId fontId) const;
		sf::SoundBuffer const& getAudio(const Shared::SoundId soundId) const;

		Utils::Resources const& getResourceManager() const;
	};
}
