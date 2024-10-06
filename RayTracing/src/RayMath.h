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
			gen = std::mt19937(rd());
			disv = std::uniform_real_distribution<>(-1.0, 1.0);// 均匀分布在 [-1.0, 1.0] 范围内的双浮点数
			disi = std::uniform_int_distribution<>(-1, 1); // 均匀分布在 [-1, 1] 范围内的整数
		}

		static glm::vec3 RandomVec();

		//返回-1~1的整数
		static int RandomI() { return disi(gen); }

		static int clamp(int a, int min, int max);

	private:
		static thread_local std::mt19937 gen;
		static std::uniform_real_distribution<> disv;
		static std::uniform_int_distribution<> disi;
	};
}