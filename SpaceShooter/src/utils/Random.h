#pragma once
#include <random>

namespace Utils
{
	struct RandomNumberGenerator
	{
		std::random_device rd;
		std::mt19937 mt;

		RandomNumberGenerator() :
			rd(),
			mt(rd())
		{}

		int getInt(int min = 0, int max = 1)
		{
			std::uniform_int_distribution<int> range(min, max);
			return range(mt);
		}

		float getFloat(float min = 0.f, float max = 1.f)
		{
			std::uniform_real_distribution<float> range(min, max);
			return range(mt);
		}
	};
}
