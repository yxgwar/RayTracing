#pragma once
#include "Hittable.h"

#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace RayTracing
{
	class Scene 
	{
	public:
		Scene() = default;
		~Scene();

		void AddObjects(std::shared_ptr<Sphere> sphere) { m_Objects.push_back(sphere); }
		//inline const std::vector<std::shared_ptr<Hittable>>& GetObjects() const { return m_Objects; }

		bool IsHit(const Ray& ray, HitData& hitData);
	private:
		std::vector<std::shared_ptr<Hittable>> m_Objects;
	};
}