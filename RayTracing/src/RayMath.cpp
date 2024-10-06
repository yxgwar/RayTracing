#include "RayMath.h"

namespace RayTracing
{
	thread_local std::mt19937 RayMath::gen;
	std::uniform_real_distribution<> RayMath::disv;
	std::uniform_int_distribution<> RayMath::disi;

	int RayMath::clamp(int a, int min, int max)
	{
		if (a < min)
			return min;
		if (a > max)
			return max;
		return a;
	}
}