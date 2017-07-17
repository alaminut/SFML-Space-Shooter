#pragma once
#include <SFML/Graphics.hpp>

namespace Utils
{
	class Animation
	{
		struct Frame
		{
			Frame(sf::IntRect const& boundaries, float duration) :
				boundaries(boundaries),
				duration(duration)
			{}

			sf::IntRect boundaries;
			float duration;
		};

	public:
		Animation();
		~Animation();

		void addFrame(sf::IntRect const& boundaries, float duration);
		sf::IntRect getFrame();

	private:
		std::vector<Frame> m_Frames;
		sf::Clock m_AnimationTimer;
		int m_CurrentFrame;

	};
}