#include "Hittable.h"

namespace RayTracing
{
	Sphere::Sphere(glm::vec3 position, float radius, glm::vec4 albedo)
		:m_Position(position), m_Radius(radius), m_Albedo(albedo)
	{
	}

	bool Sphere::IsHit(const Ray& ray, HitData& hitData)
	{
		glm::vec3 oc = ray.origin - m_Position;

		/*
		* (x - P.x)^2 + (y - P.y)^2 + (z - P.z)^2 = r^2
		* (HitPosition - m_Position)^2 = r^2
		* HitPosition = rayOrigin + rayDirection * t
		* a = rDrD
		* b = 2rD(rO - P)
		* c = (rO - P)(rO - P) - r^2
		*/

		float a = glm::dot(ray.direction, ray.direction);
		float b2 = glm::dot(oc, ray.direction);
		float c = glm::dot(oc, oc) - m_Radius * m_Radius;

		float discriminant = b2 * b2 - a * c;

		if (discriminant < 0)
			return false;
		else
		{
			float t = (-b2 - glm::sqrt(discriminant)) / a;
			glm::vec3 hitPosition = ray.origin + ray.direction * t;
			glm::vec3 normal = glm::normalize(hitPosition - m_Position);

			hitData.hitPosition = hitPosition;
			hitData.normal = normal;
			hitData.t = t;
			hitData.albedo = m_Albedo;
			return true;
		}
	}
}