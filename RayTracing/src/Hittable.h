#pragma once
#include "Ray.h"

namespace RayTracing
{
	struct HitData
	{
		glm::vec3 hitPosition;
		glm::vec3 normal;
		float t;
		glm::vec4 albedo;
	};

	class Hittable
	{
	public:
		virtual ~Hittable() = default;
		virtual bool IsHit(const Ray& ray, HitData& hitData) = 0;
	};

	class Sphere :public Hittable
	{
	public:
		Sphere(glm::vec3 position, float radius, glm::vec4 albedo);
		~Sphere() = default;

		bool IsHit(const Ray& ray, HitData& hitData) override;
	private:
		glm::vec3 m_Position{ 0.0f };
		float m_Radius = 0.5f;
		glm::vec4 m_Albedo{ 1.0f };
	};
}