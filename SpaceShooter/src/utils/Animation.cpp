#include "Animation.h"

Utils::Animation::Animation() : m_CurrentFrame(0)
{
}

Utils::Animation::~Animation()
{
}

void Utils::Animation::addFrame(sf::IntRect const& boundaries, float duration)
{
	this->m_Frames.emplace_back(boundaries, duration);
}

sf::IntRect Utils::Animation::getFrame()
{
	if (this->m_AnimationTimer.getElapsedTime().asSeconds() >= this->m_Frames.at(this->m_CurrentFrame).duration &&
		this->m_Frames.at(this->m_CurrentFrame).duration > 0.f)
	{
		this->m_CurrentFrame++;
		this->m_AnimationTimer.restart();

		if (this->m_CurrentFrame == this->m_Frames.size())
			this->m_CurrentFrame = 0;

	}

	return this->m_Frames.at(this->m_CurrentFrame).boundaries;
}
