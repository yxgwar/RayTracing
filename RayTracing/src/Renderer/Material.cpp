#include "Material.h"
#include "RayMath.h"

namespace RayTracing
{
	bool Metal::Scatter(Ray& ray, HitData& hitData, glm::vec3& color)
	{
		//OUT = IN - 2*(IN*N)*N
		ray.direction = glm::reflect(glm::normalize(ray.direction), hitData.normal);
		ray.origin = hitData.hitPosition + ray.direction * 0.00001f;
		color = m_Albedo;
		return true;
	}

	bool Lambertian::Scatter(Ray& ray, HitData& hitData, glm::vec3& color)
	{
		glm::vec3 diffuse = hitData.normal + RayMath::RandomVec();
		diffuse = glm::length(diffuse) < 1e-6 ? hitData.normal : diffuse;
		ray.direction = glm::normalize(diffuse);
		ray.origin = hitData.hitPosition + diffuse * 0.00001f;
		color = m_Albedo;
		return true;
	}
}