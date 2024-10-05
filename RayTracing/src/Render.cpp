#include "Render.h"
#include "RayMath.h"
#include <iostream>

namespace RayTracing
{
	void Render::StartRendering(Scene& scene, Camera& camera, Image& image, int width, int height, int channels)
	{
		glm::vec3 rayOrigin = camera.GetOrigin();
		Ray ray;
		ray.origin = rayOrigin;

		int index = 0;
		for (int j = 0; j < height; j++) {
#ifdef _DEBUG
			std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
#endif // _DEBUG
			for (int i = 0; i < width; i++) {
				ray.direction = camera.GetRayDirections()[i + j * width];

				glm::vec4 color = perPixel(scene, ray);
				color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));//将颜色限制在0~255
				image.SetPixelData(color, index);
			}
		}
#ifdef _DEBUG
		std::clog << "\rDone.                 \n";
#endif // _DEBUG
	}

	glm::vec4 Render::perPixel(Scene& scene, Ray& ray)
	{
		glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f));
		HitData hitData;
		Ray traceRay(ray);

		glm::vec3 color(0.0f);
		float multiplier = 1.0f;
		int bounces = 3;
		for (size_t i = 0; i < bounces; i++)
		{
			if (scene.IsHit(traceRay, hitData))
			{
				float d = glm::max(glm::dot(hitData.normal, -lightDirection), 0.0f);
				//color += glm::vec3(hitData.albedo) * d * multiplier;
				multiplier *= 0.5f;

				glm::vec3 diffuse = hitData.normal + RayMath::RandomVec();
				//diffuse = glm::dot(diffuse, hitData.normal) > 0 ? diffuse : -diffuse;
				traceRay.origin = hitData.hitPosition + diffuse * 0.00001f;
				traceRay.direction = diffuse;
				//OUT = IN - 2*(IN*N)*N
				//traceRay.direction = glm::reflect(traceRay.direction, diffuse);
			}
			else
			{
				glm::vec3 dir = glm::normalize(ray.direction);
				float a = (dir.y + 1.0f) * 0.5f;
				color += ((1.0f - a) * glm::vec3(1.0f) + a * glm::vec3(0.5f, 0.7f, 1.0f)) * multiplier;
				break;
			}
		}
		return { color, 1.0f };
	}
}