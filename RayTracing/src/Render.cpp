#include "Render.h"
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
		if (scene.IsHit(ray, hitData))
		{
			float d = glm::max(glm::dot(hitData.normal, -lightDirection), 0.0f);
			return { glm::vec3(hitData.albedo) * d, 1.0f };
		}
		else
			return { 0.0f, 0.0f, 0.0f, 1.0f };
	}
}