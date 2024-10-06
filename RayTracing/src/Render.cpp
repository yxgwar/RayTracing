#include "Render.h"
#include "RayMath.h"
#include <thread>

namespace RayTracing
{
	void Render::StartRendering(Scene& scene, Camera& camera, Image& image, int width, int height, int channels)
	{
		glm::vec3 rayOrigin = camera.GetOrigin();
		int samplers = 100;
#if 1
		std::size_t num_threads = std::thread::hardware_concurrency();
		std::vector<std::thread> threads;
		int step = height / num_threads;
		for (int th = 0; th < num_threads; th++)
		{
			threads.emplace_back([&, th]()
				{
					Ray ray;
					ray.origin = rayOrigin;
					int start = th * step;
					int end = (th == num_threads - 1) ? height : (th + 1) * step;
					for (int j = start; j < end; j++) {
						for (int i = 0; i < width; i++) {
							glm::vec4 colorS(0.0f);
							for (int s = 0; s < samplers; s++)
							{
								int x = RayMath::clamp(i + RayMath::RandomI(), 0, width - 1);
								int y = RayMath::clamp(j + RayMath::RandomI(), 0, height - 1);
								ray.direction = camera.GetRayDirections()[x + y * width];
								colorS += perPixel(scene, ray);
							}

							glm::vec4 color = colorS / float(samplers);
							color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));//将颜色限制在0~255
							image.SetPixelData(color, i + j * width);
						}
					}
				});
		}

		for (auto& thread : threads)
			thread.join();
#else
		Ray ray;
		ray.origin = rayOrigin;

		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {
				glm::vec4 colorS(0.0f);
				for (int s = 0; s < samplers; s++)
				{
					int x = RayMath::clamp(i + RayMath::RandomI(), 0, width - 1);
					int y = RayMath::clamp(j + RayMath::RandomI(), 0, height - 1);
					ray.direction = camera.GetRayDirections()[x + y * width];
					colorS += perPixel(scene, ray);
				}

				glm::vec4 color = colorS / float(samplers);
				color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));//将颜色限制在0~255
				image.SetPixelData(color, i + j * width);
			}
		}
#endif
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
				glm::vec3 dir = glm::normalize(traceRay.direction);
				float a = (dir.y + 1.0f) * 0.5f;
				color += ((1.0f - a) * glm::vec3(1.0f) + a * glm::vec3(0.3f, 0.5f, 1.0f)) * multiplier;
				break;
			}
		}
		return { color, 1.0f };
	}
}