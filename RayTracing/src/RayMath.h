#pragma once
#include <glm/glm.hpp>
#include <random>

namespace RayTracing
{
	class RayMath
	{
	public:
		static void Init()
		{
			std::random_device rd; // 随机设备
			std::mt19937 gen(rd()); // Mersenne Twister 随机引擎
			std::uniform_real_distribution<> dis(0.0f, 0.5f); // 均匀分布在 [0, 0.5] 范围内的浮点数
		}

		static glm::vec3 RandomVec()
		{
			return { dis(gen), dis(gen), dis(gen) };
		}

	private:
		static std::mt19937 gen;
		static std::uniform_real_distribution<> dis;
	};
}