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
			std::random_device rd; // ����豸
			std::mt19937 gen(rd()); // Mersenne Twister �������
			std::uniform_real_distribution<> dis(0.0f, 0.5f); // ���ȷֲ��� [0, 0.5] ��Χ�ڵĸ�����
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