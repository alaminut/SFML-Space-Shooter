#include "GameState.h"
#include "../Application.h"

State::GameState::GameState(Application& application) :
	m_p_application(&application)
{
}

State::GameState::~GameState()
{
	if(this->m_sceneAudio.getStatus() == sf::Sound::Playing)
	{
		this->m_sceneAudio.stop();
	}
}

sf::Texture const& State::GameState::getTexture(const Shared::TextureId textureId) const
{
	return this->m_p_application->getResources().textures.getResource(textureId);
}

sf::Font const& State::GameState::getFont(const Shared::FontId fontId) const
{
	return this->m_p_application->getResources().fonts.getResource(fontId);
}

sf::SoundBuffer const& State::GameState::getAudio(const Shared::SoundId soundId) const
{
	return this->m_p_application->getResources().audio.getResource(soundId);
}

Utils::Resources const& State::GameState::getResourceManager() const
{
	return this->m_p_application->getResources();
}
