#pragma once
#include "Hittable.h"

namespace RayTracing
{
	class Material
	{
	public:
		virtual ~Material() = default;

		virtual bool Scatter(Ray& ray, HitData& hitData, glm::vec3& color) = 0;
	};

	class Metal :public Material
	{
	public:
		Metal(const glm::vec3& albedo) :m_Albedo(albedo) {}
		~Metal() = default;

		bool Scatter(Ray& ray, HitData& hitData, glm::vec3& color) override;
	private:
		glm::vec3 m_Albedo;
	};

	class Lambertian :public Material
	{
	public:
		Lambertian(const glm::vec3& albedo) :m_Albedo(albedo) {}
		~Lambertian() = default;

		bool Scatter(Ray& ray, HitData& hitData, glm::vec3& color) override;
	private:
		glm::vec3 m_Albedo;
	};
}